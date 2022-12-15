%code top{
    #include <iostream>
    #include <assert.h>
    #include "parser.h"
    #include <cstring>
    #include <stack>
    extern Ast ast;

    int yylex();
    int yyerror(char const*);
    ArrayType* arrayType;
    int idx;
    int* arrayValue;
    std::stack<InitValueListExpr*> stk;
    std::stack<StmtNode*> whileStk;
    InitValueListExpr* top;
    int leftCnt = 0;
    int InWhileStmt = 0;
    bool hasRet=true;//类型检查06：int函数无返回值
    bool IsvoidFunc=false;//类型检查05：void函数有返回值
    bool voidOp=false;//类型检查07：检查两端如果是函数的话是否为void类型
    #include <iostream>
}

%code requires {
    #include "Ast.h"
    #include "SymbolTable.h"
    #include "Type.h"
}

%union {
    int itype;
    char* strtype;
    StmtNode* stmttype;
    ExprNode* exprtype;
    Type* type;
    SymbolEntry* se;
}

%start Program
%token <strtype> ID
%token <itype> INTEGER
%token IF ELSE WHILE
%token INT VOID
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON LBRACKET RBRACKET COMMA  
%token ADD SUB MUL DIV MOD OR AND LESS LESSEQUAL GREATER GREATEREQUAL ASSIGN EQUAL NOTEQUAL NOT
%token CONST
%token RETURN CONTINUE BREAK

%type<stmttype> Stmts Stmt AssignStmt ExprStmt BlockStmt IfStmt WhileStmt BreakStmt ContinueStmt ReturnStmt DeclStmt FuncDef ConstDeclStmt VarDeclStmt ConstDefs VarDef ConstDef VarDefs FuncFParam FuncFParams MaybeFuncFParams EmptyStmt
%type<exprtype> Exp AddExp Cond SeventhExp PrimaryExp LVal FourthExp SixthExp MulExp ConstExp FifthExp UnaryExp InitVal ConstInitVal InitValList ConstInitValList FuncArrayIndices FuncRParams ArrayIndices
%type<type> Type

%precedence THEN
%precedence ELSE
%%
Program
    : Stmts {
        ast.setRoot($1);
    }
    ;
Stmts
    : Stmt {$$=$1;}
    | Stmts Stmt{
        $$ = new SeqNode($1, $2);
    }
    ;
Stmt
    : AssignStmt {
        $$=$1;
    }
    | ExprStmt {$$ = $1;}
    | BlockStmt {$$=$1;}
    | EmptyStmt {$$ = $1;}
    | IfStmt {$$ = $1;}
    | WhileStmt {$$ = $1;}
    | BreakStmt 
    {
        if(!InWhileStmt)
            fprintf(stderr, "非while语句内出现break\n");
        $$=$1;
    }
    | ContinueStmt 
    {
        if(!InWhileStmt)
            fprintf(stderr, "非whie语句内出现continue\n");
        $$=$1;
    }
    | ReturnStmt {$$ = $1;}
    | DeclStmt {$$ = $1;}
    | FuncDef {$$ = $1;}
    ;
LVal
    : ID 
    {
        SymbolEntry* se;
        se = identifiers->lookup($1);
        //类型检查01：常变量使用前未声明
        if(se==nullptr)
        {
            fprintf(stderr, "标识符 \"%s\" 使用前未声明\n", (char*)$1);
            delete [](char*)$1;
            assert(se != nullptr);
        }
        $$ = new Id(se);
        delete []$1;
    }
    | ID ArrayIndices
    {
        SymbolEntry* se;
        se = identifiers->lookup($1);
        //类型检查01：常变量使用前未声明
        if(se == nullptr)
        {
            fprintf(stderr, "标识符 \"%s\" 使用前未声明\n", (char*)$1);
            delete [](char*)$1;
            assert(se != nullptr);
        }
        $$ = new Id(se, $2);
        delete []$1;
    }
    ; 
AssignStmt
    : LVal ASSIGN Exp SEMICOLON 
    {
        $$ = new AssignStmt($1, $3);
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1 = identifiers->lookup($3->getSymbolEntry()->toStr());
        if(se1!=nullptr)
        {
            Type* temptype1=(FunctionType*)se1->getType();
            if(temptype1->isFunc())
            {
                FunctionType* temp1=(FunctionType*)temptype1;
                if(temp1->getRetType()==TypeSystem::voidType )
                {
                    fprintf(stderr,"操作符对象不能为void函数\n");
                }
            }
            
        }
    }
    ;
ExprStmt
    : Exp SEMICOLON {
        $$ = new ExprStmt($1);
    }
    ;
EmptyStmt
    : SEMICOLON {
        $$ = new EmptyStmt();
    }
    ;
BlockStmt
    : LBRACE {
        identifiers = new SymbolTable(identifiers);
    } 
      Stmts RBRACE {
        $$ = new CompoundStmt($3);

        SymbolTable* top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
    }
    | LBRACE RBRACE {
        $$ = new CompoundStmt();
    }
    ;
IfStmt
    : IF LPAREN Cond RPAREN Stmt %prec THEN {
        $$ = new IfStmt($3, $5);
    }
    | IF LPAREN Cond RPAREN Stmt ELSE Stmt {
        $$ = new IfElseStmt($3, $5, $7);
    }
    ;
//新增while语句
WhileStmt
    : WHILE LPAREN Cond RPAREN {
        InWhileStmt++;
        WhileStmt *whileNode = new WhileStmt($3);
        $<stmttype>$ = whileNode;
        whileStk.push(whileNode);
    }
    Stmt {
        StmtNode *whileNode = $<stmttype>5; 
        ((WhileStmt*)whileNode)->setStmt($6);
        $$=whileNode;
        whileStk.pop();
        InWhileStmt--;
    }
    ;
BreakStmt
    : BREAK SEMICOLON {
        $$ = new BreakStmt(whileStk.top());
    }
    ;
ContinueStmt
    : CONTINUE SEMICOLON {
        $$ = new ContinueStmt(whileStk.top());
    }
    ;
ReturnStmt
    : RETURN SEMICOLON 
    {
        $$ = new ReturnStmt();
    }
    | RETURN Exp SEMICOLON 
    {
        //类型检查05：void函数携带返回值
        if(IsvoidFunc)
        {
            fprintf(stderr,"void函数有返回值\n");
            //assert(IsvoidFunc!=true);
            IsvoidFunc=false;//恢复为false
        }
        hasRet=true;
        $$ = new ReturnStmt($2);
    }
    ;
//表达式，类别为exprnode
Exp
    :
    AddExp {$$ = $1;}
    ;
Cond
    :
    SeventhExp 
    {
        
        //类型检查08：int->bool
        if($1->getSymbolEntry()->getType()->toStr()=="i32")
        {
            fprintf(stderr, "条件表达式应为bool值。\n");
        }
        
        $$ = $1;
    }
    ;
PrimaryExp
    : LPAREN Exp RPAREN {
        $$ = $2;
    }
    | LVal {
        $$ = $1;
    }
    | INTEGER {
        SymbolEntry* se = new ConstantSymbolEntry(TypeSystem::intType, $1);
        $$ = new Constant(se);
    }
    ;
UnaryExp 
    : PrimaryExp {$$ = $1;}
    | ID LPAREN FuncRParams RPAREN 
    {
        SymbolEntry* se;
        se = identifiers->lookup($1);
        //类型检查03：函数使用前未声明
        if(se == nullptr)
        {    
            fprintf(stderr, "函数 \"%s\"未定义\n", (char*)$1);
            //assert(1==0);
        }
        //类型检查03：形参实参个数不匹配——04需要区分同名不同参数的函数——如何区分
        //一个设想——删除得到的，再加到最后？
        int realcount=0;//实参个数
        int formcount=0;//调用函数的形参个数
        Node*temp=(Node*)$3;
        while(temp)
        {
            realcount++;//实参个数
            temp=temp->getNext();
        }
        //计算形参个数
        Type* temptype=se->getType();
        std::vector<Type*> params = ((FunctionType*)temptype)->getParamsType();
        formcount=params.size();
        if(formcount!=realcount)
        {
            fprintf(stderr,"所调用函数 \"%s\" 的形参实参个数不匹配\n",(char*)$1);
            //assert(1==0);
        }
        $$ = new FuncCallNode(se, $3);
    }
    | ID LPAREN RPAREN {
        SymbolEntry* se;
        se = identifiers->lookup($1);
        //类型检查03：函数使用前未声明
        if(se == nullptr)
        {    
            fprintf(stderr, "函数 \"%s\" 未定义\n", (char*)$1);
        }
        $$ = new FuncCallNode(se);
    }
    | ADD UnaryExp {
        $$ = $2;
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=$2->getSymbolEntry();
        //fprintf(stderr,"test1\n");
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                //fprintf(stderr,"是函数\n");
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {               
                    fprintf(stderr,"一元操作符对象不能为void函数\n");
                }
            }
        }
        }
    | SUB UnaryExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new OneOpExpr(se, OneOpExpr::SUB, $2);
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=$2->getSymbolEntry();
        //fprintf(stderr,"test1\n");
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                //fprintf(stderr,"是函数\n");
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {               
                    fprintf(stderr,"一元操作符对象不能为void函数\n");
                }
            }
        }
    }
    | NOT UnaryExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new OneOpExpr(se, OneOpExpr::NOT, $2);
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=$2->getSymbolEntry();
        //fprintf(stderr,"test1\n");
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                //fprintf(stderr,"是函数\n");
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {               
                    fprintf(stderr,"一元操作符对象不能为void函数\n");
                }
            }
        }
        
    }
    ;
MulExp
    : UnaryExp 
    {
        //fprintf(stderr,"test\n");
        $$ = $1;}
    | MulExp MUL UnaryExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::MUL, $1, $3);
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=$1->getSymbolEntry();
        SymbolEntry* se2;
        se2=$3->getSymbolEntry();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
    }
    | MulExp DIV UnaryExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::DIV, $1, $3);
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=$1->getSymbolEntry();
        SymbolEntry* se2;
        se2=$3->getSymbolEntry();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
    }
    | MulExp MOD UnaryExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::MOD, $1, $3);
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=$1->getSymbolEntry();
        SymbolEntry* se2;
        se2=$3->getSymbolEntry();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
    }
    ;
AddExp
    : MulExp {$$ = $1;}
    | AddExp ADD MulExp 
    {
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=$1->getSymbolEntry();
        SymbolEntry* se2;
        se2=$3->getSymbolEntry();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
        
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());

        $$ = new BinaryExpr(se, BinaryExpr::ADD, $1, $3);
        
    }
    | AddExp SUB MulExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::SUB, $1, $3);
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=$1->getSymbolEntry();
        SymbolEntry* se2;
        se2=$3->getSymbolEntry();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
    }
    ;
FourthExp
    : AddExp {
        $$ = $1;
    }
    | FourthExp LESS AddExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LESS, $1, $3);
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=$1->getSymbolEntry();
        SymbolEntry* se2;
        se2=$3->getSymbolEntry();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
    }
    | FourthExp LESSEQUAL AddExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LESSEQUAL, $1, $3);
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=$1->getSymbolEntry();
        SymbolEntry* se2;
        se2=$3->getSymbolEntry();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
    }
    | FourthExp GREATER AddExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::GREATER, $1, $3);
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=$1->getSymbolEntry();
        SymbolEntry* se2;
        se2=$3->getSymbolEntry();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
    }
    | FourthExp GREATEREQUAL AddExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::GREATEREQUAL, $1, $3);
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=$1->getSymbolEntry();
        SymbolEntry* se2;
        se2=$3->getSymbolEntry();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
    }
    ;
FifthExp
    : FourthExp {$$ = $1;}
    | FifthExp EQUAL FourthExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::EQUAL, $1, $3);
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=$1->getSymbolEntry();
        SymbolEntry* se2;
        se2=$3->getSymbolEntry();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
    }
    | FifthExp NOTEQUAL FourthExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::NOTEQUAL, $1, $3);
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=$1->getSymbolEntry();
        SymbolEntry* se2;
        se2=$3->getSymbolEntry();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
    }
    ;
SixthExp
    : FifthExp {$$ = $1;}
    | SixthExp AND FifthExp // &&操作符
    {
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=$1->getSymbolEntry();
        SymbolEntry* se2;
        se2=$3->getSymbolEntry();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::AND, $1, $3);
    }
    ;
SeventhExp
    : SixthExp {$$ = $1;}
    | SeventhExp OR SixthExp 
    {
        //表达式都为临时符号表项
        // ||
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::OR, $1, $3);
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=$1->getSymbolEntry();
        SymbolEntry* se2;
        se2=$3->getSymbolEntry();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
    }
    ;
ConstExp
    : AddExp {$$ = $1;}
    ;
FuncRParams 
    : Exp {$$ = $1;}
    | FuncRParams COMMA Exp 
    {
        $$ = $1;
        $$->setNext($3);
    }
//类型识别，之后需要新增float
Type
    : INT {
        $$ = TypeSystem::intType;
    }
    | VOID 
    {
        $$ = TypeSystem::voidType;
        //void只会出现在函数定义中，所以此处无问题
        IsvoidFunc=true;
    }
    ;
//声明语句
DeclStmt
    : VarDeclStmt {$$ = $1;}
    | ConstDeclStmt {$$ = $1;}
    ;
//变量声明语句
VarDeclStmt
    : Type VarDefs SEMICOLON {$$ = $2;}
    ;
//常量声明语句
ConstDeclStmt
    : CONST Type ConstDefs SEMICOLON {
        $$ = $3;
    }
    ;
//多个变量
VarDefs
    : VarDefs COMMA VarDef {
        $$ = $1;
        $1->setNext($3);
    } 
    | VarDef {$$ = $1;}
    ;
//多个常量
ConstDefs
    : ConstDefs COMMA ConstDef {
        $$ = $1;
        $1->setNext($3);
    }
    | ConstDef {$$ = $1;}
    ;
//单个变量 原理与常量相同，但表项类别为identifier
VarDef
    : ID {
        SymbolEntry* se;
        se = new IdentifierSymbolEntry(TypeSystem::intType, $1, identifiers->getLevel());
        //类型检查02：常变量重定义
        if(!identifiers->install($1, se))
        {    
            fprintf(stderr, "常变量名 \"%s\" 重定义\n", (char*)$1);
            assert(1==0);//中断运行
        }
        $$ = new DeclStmt(new Id(se));
        delete []$1;
    }
    | ID ArrayIndices 
    {
        SymbolEntry* se;
        std::vector<int> vec;
        ExprNode* temp = $2;
        while(temp){
            vec.push_back(temp->getValue());
            temp = (ExprNode*)(temp->getNext());
        }
        Type *type = TypeSystem::intType;
        Type* temp1;
        while(!vec.empty()){
            temp1 = new ArrayType(type, vec.back());
            if(type->isArray())
                ((ArrayType*)type)->setArrayType(temp1);
            type = temp1;
            vec.pop_back();
        }
        arrayType = (ArrayType*)type;
        se = new IdentifierSymbolEntry(type, $1, identifiers->getLevel());
        ((IdentifierSymbolEntry*)se)->setAllZero();
        int *p = new int[type->getSize()];
        ((IdentifierSymbolEntry*)se)->setArrayValue(p);
        //类型检查02：常变量重定义
        if(!identifiers->install($1, se))
        {    
            fprintf(stderr, "常变量名 \"%s\" 重定义\n", (char*)$1);
            assert(1==0);//中断运行
        }
        $$ = new DeclStmt(new Id(se));
        delete []$1;
    }
    | ID ASSIGN InitVal {
        SymbolEntry* se;
        se = new IdentifierSymbolEntry(TypeSystem::intType, $1, identifiers->getLevel());
        //类型检查02：常变量重定义
        if(!identifiers->install($1, se))
        {    
            fprintf(stderr, "常变量名 \"%s\" 重定义\n", (char*)$1);
            //assert(1==0);//中断运行
        }
        ((IdentifierSymbolEntry*)se)->setValue($3->getValue());
        $$ = new DeclStmt(new Id(se), $3);
        delete []$1;
    }
    | ID ArrayIndices ASSIGN {
        SymbolEntry* se;
        std::vector<int> vec;
        ExprNode* temp = $2;
        while(temp){
            vec.push_back(temp->getValue());
            temp = (ExprNode*)(temp->getNext());
        }
        Type* type = TypeSystem::intType;
        Type* temp1;
        for(auto it = vec.rbegin(); it != vec.rend(); it++) {
            temp1 = new ArrayType(type, *it);
            if(type->isArray())
                ((ArrayType*)type)->setArrayType(temp1);
            type = temp1;
        }
        arrayType = (ArrayType*)type;
        idx = 0;
        std::stack<InitValueListExpr*>().swap(stk);
        se = new IdentifierSymbolEntry(type, $1, identifiers->getLevel());
        $<se>$ = se;
        arrayValue = new int[arrayType->getSize()];
    }
      InitVal {
        ((IdentifierSymbolEntry*)$<se>4)->setArrayValue(arrayValue);
        if(((InitValueListExpr*)$5)->isEmpty())
            ((IdentifierSymbolEntry*)$<se>4)->setAllZero();
        //类型检查02：常变量重定义
        if(!identifiers->install($1, $<se>4))
        {    
            fprintf(stderr, "常变量名 \"%s\" 重定义\n", (char*)$1);
            assert(1==0);//中断运行
        }
        $$ = new DeclStmt(new Id($<se>4), $5);
        delete []$1;
    }
    ;
//单个常量
ConstDef
    : ID ASSIGN ConstInitVal {
        SymbolEntry* se;
        se = new IdentifierSymbolEntry(TypeSystem::intType, $1, identifiers->getLevel());
        //类型检查02：常变量重定义
        if(!identifiers->install($1, se))
        {    
            fprintf(stderr, "常变量名 \"%s\" 重定义\n", (char*)$1);
            //assert(1==0);//中断运行
        }
        identifiers->install($1, se);
        ((IdentifierSymbolEntry*)se)->setValue($3->getValue());
        $$ = new DeclStmt(new Id(se), $3);
        delete []$1;
    }
    | ID ArrayIndices ASSIGN  {
        SymbolEntry* se;
        std::vector<int> vec;
        ExprNode* temp = $2;
        while(temp){
            vec.push_back(temp->getValue());
            temp = (ExprNode*)(temp->getNext());
        }
        Type* type = TypeSystem::intType;
        Type* temp1;
        for(auto it = vec.rbegin(); it != vec.rend(); it++) {
            temp1 = new ArrayType(type, *it, true);
            if(type->isArray())
                ((ArrayType*)type)->setArrayType(temp1);
            type = temp1;
        }
        arrayType = (ArrayType*)type;
        idx = 0;
        std::stack<InitValueListExpr*>().swap(stk);
        se = new IdentifierSymbolEntry(type, $1, identifiers->getLevel());
        $<se>$ = se;
        arrayValue = new int[arrayType->getSize()];
    }
      ConstInitVal {
        ((IdentifierSymbolEntry*)$<se>4)->setArrayValue(arrayValue);
        //类型检查02：常变量重定义
        if(!identifiers->install($1, $<se>4))
        {    
            fprintf(stderr, "常变量名 \"%s\" 重定义\n", (char*)$1);
            assert(1==0);//中断运行
        }
        identifiers->install($1, $<se>4);
        $$ = new DeclStmt(new Id($<se>4), $5);
        delete []$1;
    } 
    ;
ArrayIndices
    : LBRACKET ConstExp RBRACKET {
        $$ = $2;
    }
    | ArrayIndices LBRACKET ConstExp RBRACKET {
        $$ = $1;
        $1->setNext($3);
    }
    ;
InitVal 
    : AddExp 
    {
        if(!$1->getType()->isInt())
        {
            fprintf(stderr,
                "cannot initialize a variable of type \'int\' with an rvalue "
                "of type \'%s\'\n",
                $1->getType()->toStr().c_str());
        }
        $$ = $1;
        if(!stk.empty())
        {
            arrayValue[idx++] = $1->getValue();
            Type* arrTy = stk.top()->getSymbolEntry()->getType();
            if(arrTy == TypeSystem::intType)
                stk.top()->addExpr($1);
            else
                while(arrTy){
                    if(((ArrayType*)arrTy)->getElementType() != TypeSystem::intType){
                        arrTy = ((ArrayType*)arrTy)->getElementType();
                        SymbolEntry* se = new ConstantSymbolEntry(arrTy);
                        InitValueListExpr* list = new InitValueListExpr(se);
                        stk.top()->addExpr(list);
                        stk.push(list);
                    }else{
                        stk.top()->addExpr($1);
                        while(stk.top()->isFull() && stk.size() != (long unsigned int)leftCnt){
                            arrTy = ((ArrayType*)arrTy)->getArrayType();
                            stk.pop();
                        }
                        break;
                    }
                }
        }
             
    }
    | LBRACE RBRACE {
        SymbolEntry* se;
        ExprNode* list;
        if(stk.empty())
        {
            memset(arrayValue, 0, arrayType->getSize());
            idx += arrayType->getSize() / TypeSystem::intType->getSize();
            se = new ConstantSymbolEntry(arrayType);
            list = new InitValueListExpr(se);
        }
        else
        {
            Type* type = ((ArrayType*)(stk.top()->getSymbolEntry()->getType()))->getElementType();
            int len = type->getSize() / TypeSystem::intType->getSize();
            memset(arrayValue + idx, 0, type->getSize());
            idx += len;
            se = new ConstantSymbolEntry(type);
            list = new InitValueListExpr(se);
            stk.top()->addExpr(list);
            while(stk.top()->isFull() && stk.size() != (long unsigned int)leftCnt){
                stk.pop();
            }
        }
        $$ = list;
    }
    | LBRACE {
        SymbolEntry* se;
        if(!stk.empty())
            arrayType = (ArrayType*)(((ArrayType*)(stk.top()->getSymbolEntry()->getType()))->getElementType());
        se = new ConstantSymbolEntry(arrayType);
        if(arrayType->getElementType() != TypeSystem::intType){
            arrayType = (ArrayType*)(arrayType->getElementType());
        }
        InitValueListExpr* expr = new InitValueListExpr(se);
        if(!stk.empty())
            stk.top()->addExpr(expr);
        stk.push(expr);
        $<exprtype>$ = expr;
        leftCnt++;
    } 
      InitValList RBRACE {
        leftCnt--;
        while(stk.top() != $<exprtype>2 && stk.size() > (long unsigned int)(leftCnt + 1))
            stk.pop();
        if(stk.top() == $<exprtype>2)
            stk.pop();
        $$ = $<exprtype>2;
        if(!stk.empty())
            while(stk.top()->isFull() && stk.size() != (long unsigned int)leftCnt){
                stk.pop();
            }
        int size = ((ArrayType*)($$->getSymbolEntry()->getType()))->getSize()/ TypeSystem::intType->getSize();
        while(idx % size != 0)
            arrayValue[idx++] = 0;
        if(!stk.empty())
            arrayType = (ArrayType*)(((ArrayType*)(stk.top()->getSymbolEntry()->getType()))->getElementType());
    }
    ;

ConstInitVal
    : ConstExp {
        $$ = $1;
        if(!stk.empty()){
            arrayValue[idx++] = $1->getValue();
            Type* arrTy = stk.top()->getSymbolEntry()->getType();
            if(arrTy == TypeSystem::intType)
                stk.top()->addExpr($1);
            else
                while(arrTy){
                    if(((ArrayType*)arrTy)->getElementType() != TypeSystem::intType){
                        arrTy = ((ArrayType*)arrTy)->getElementType();
                        SymbolEntry* se = new ConstantSymbolEntry(arrTy);
                        InitValueListExpr* list = new InitValueListExpr(se);
                        stk.top()->addExpr(list);
                        stk.push(list);
                    }else{
                        stk.top()->addExpr($1);
                        while(stk.top()->isFull() && stk.size() != (long unsigned int)leftCnt){
                            arrTy = ((ArrayType*)arrTy)->getArrayType();
                            stk.pop();
                        }
                        break;
                    }
                }
        }
    }
    | LBRACE RBRACE {
        SymbolEntry* se;
        ExprNode* list;
        if(stk.empty())
        {
            memset(arrayValue, 0, arrayType->getSize());
            idx += arrayType->getSize() / TypeSystem::intType->getSize();
            se = new ConstantSymbolEntry(arrayType);
            list = new InitValueListExpr(se);
        }
        else
        {
            Type* type = ((ArrayType*)(stk.top()->getSymbolEntry()->getType()))->getElementType();
            int len = type->getSize() / TypeSystem::intType->getSize();
            memset(arrayValue + idx, 0, type->getSize());
            idx += len;
            se = new ConstantSymbolEntry(type);
            list = new InitValueListExpr(se);
            stk.top()->addExpr(list);
            while(stk.top()->isFull() && stk.size() != (long unsigned int)leftCnt){
                stk.pop();
            }
        }
        $$ = list;
    }
    | LBRACE {
        SymbolEntry* se;
        if(!stk.empty())
            arrayType = (ArrayType*)(((ArrayType*)(stk.top()->getSymbolEntry()->getType()))->getElementType());
        se = new ConstantSymbolEntry(arrayType);
        if(arrayType->getElementType() != TypeSystem::intType){
            arrayType = (ArrayType*)(arrayType->getElementType());
        }
        InitValueListExpr* expr = new InitValueListExpr(se);
        if(!stk.empty())
            stk.top()->addExpr(expr);
        stk.push(expr);
        $<exprtype>$ = expr;
        leftCnt++;
    } 
      ConstInitValList RBRACE {
        leftCnt--;
        while(stk.top() != $<exprtype>2 && stk.size() > (long unsigned int)(leftCnt + 1))
            stk.pop();
        if(stk.top() == $<exprtype>2)
            stk.pop();
        $$ = $<exprtype>2;
        if(!stk.empty())
            while(stk.top()->isFull() && stk.size() != (long unsigned int)leftCnt){
                stk.pop();
            }
        while(idx % (((ArrayType*)($$->getSymbolEntry()->getType()))->getSize()/ sizeof(int)) !=0 )
            arrayValue[idx++] = 0;
        if(!stk.empty())
            arrayType = (ArrayType*)(((ArrayType*)(stk.top()->getSymbolEntry()->getType()))->getElementType());
    }
    ;
InitValList
    : InitVal {
        $$ = $1;
    }
    | InitValList COMMA InitVal {
        $$ = $1;
    }
    ;
ConstInitValList
    : ConstInitVal {
        $$ = $1;
    }
    | ConstInitValList COMMA ConstInitVal {
        $$ = $1;
    }
    ;
//这个CFG只可能出现在函数声明时
FuncDef
    :
    Type ID 
    {
        identifiers = new SymbolTable(identifiers);
        //函数声明时假设为false
        if($1->isInt())
        {
            hasRet=false;
        }
    }
    LPAREN MaybeFuncFParams RPAREN {
        Type* funcType;
        std::vector<Type*> vec;
        std::vector<SymbolEntry*> vec1;
        DeclStmt* temp = (DeclStmt*)$5;
        while(temp){
            vec.push_back(temp->getId()->getSymbolEntry()->getType());
            vec1.push_back(temp->getId()->getSymbolEntry());
            temp = (DeclStmt*)(temp->getNext());
        }
        funcType = new FunctionType($1, vec, vec1);
        SymbolEntry* se = new IdentifierSymbolEntry(funcType, $2, identifiers->getPrev()->getLevel());
        //类型检查04：函数重定义
        if(!identifiers->getPrev()->install($2, se))
        {
            fprintf(stderr, "函数\'%s\'重定义\n", (char*)$2);
        }
        $<se>$ = se; 
    } 
    BlockStmt 
    {
        $$ = new FunctionDef($<se>7, (DeclStmt*)$5, $8);
        SymbolTable* top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
        delete []$2;
        //翻译完毕后即可检查是否有返回值
        if(hasRet==false)
        {
            fprintf(stderr, "int型函数 \" %s \" 缺少返回值\n",(char*)$2);
            //恢复原值
            hasRet=true;
        }
    }
    ;
MaybeFuncFParams
    : FuncFParams {$$ = $1;}
    | %empty {$$ = nullptr;}
FuncFParams
    : FuncFParams COMMA FuncFParam {
        $$ = $1;
        $$->setNext($3);
    }
    | FuncFParam {
        $$ = $1;
    }
    ;
FuncFParam
    : Type ID {
        SymbolEntry* se;
        se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel());
        identifiers->install($2, se);
        ((IdentifierSymbolEntry*)se)->setLabel();
        ((IdentifierSymbolEntry*)se)->setAddr(new Operand(se));
        $$ = new DeclStmt(new Id(se));
        delete []$2;
    }
    | Type ID FuncArrayIndices {
        // 这里也需要求值
        SymbolEntry* se;
        ExprNode* temp = $3;
        Type* arr = TypeSystem::intType;
        Type* arr1;
        std::stack<ExprNode*> stk;
        while(temp){
            stk.push(temp);
            temp = (ExprNode*)(temp->getNext());
        }
        while(!stk.empty()){
            arr1 = new ArrayType(arr, stk.top()->getValue());
            if(arr->isArray())
                ((ArrayType*)arr)->setArrayType(arr1);
            arr = arr1;
            stk.pop();
        }
        se = new IdentifierSymbolEntry(arr, $2, identifiers->getLevel());
        identifiers->install($2, se);
        ((IdentifierSymbolEntry*)se)->setLabel();
        ((IdentifierSymbolEntry*)se)->setAddr(new Operand(se));
        $$ = new DeclStmt(new Id(se));
        delete []$2;
    }
    ;
FuncArrayIndices 
    : LBRACKET RBRACKET {
        $$ = new ExprNode(nullptr);
    }
    | FuncArrayIndices LBRACKET Exp RBRACKET {
        $$ = $1;
        $$->setNext($3);
    }
%%

int yyerror(char const* message)
{
    std::cerr<<message<<std::endl;
    return -1;
}
