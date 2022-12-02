%code top{
    #include <iostream>
    #include <assert.h>
    #include "parser.h"
    #include <cstring>
    #include <stack>
    extern Ast ast;
    int yylex();
    int yyerror( char const * );
}

%code requires {
    //文件要求包含头文件
    #include "Ast.h"
    #include "SymbolTable.h"
    #include "Type.h"
}

%union {
    //union是只能存在一个
    //也就是说yylval只能为以下中的一个
    int itype;//记录得到的数字的内容
    char* strtype;//用来存储ID名字
    StmtNode* stmttype;
    ExprNode* exprtype;
    Type* type;//记录类型，调用Type.h中的class
    SymbolEntry *se;//符号表项时
}

%start Program
%token <strtype> ID 
%token <itype> INTEGER
%token IF ELSE  
%token INT VOID 
%token EOL WHITE LINECOMMENT
%token LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE SEMICOLON
%token TILDE MOD EXCLA COMMA SHA COLON
%token GEQUAL LEQUAL EQUAL SUBONE ADDONE NOTEQUAL
%token ANDAND OROR ASSIGNDIV ASSIGNMOD ASSIGNSTAR ASSIGNADD ASSIGNSUB
%token ADD SUB DIV MUL OR AND GREATER LESS ASSIGN
%token MLEFT MRIGHT
%token RETURN
%token DO WHILE SWITCH CASE DEFAULT CONST SIZEOF CONTINUE BREAK FOR SCANF PRINTF
%nterm <stmttype> Stmts Stmt AssignStmt BlockStmt IfStmt ReturnStmt DeclStmt FuncDef 
%nterm <stmttype> WhileStmt DoWhileStmt SwitchStmt ForStmt 
%nterm <stmttype> VarDeclStmt VarDefs VarDef ConstDeclStmt ConstDefs ConstDef
%nterm <stmttype> FuncFormalParams SingleFuncFormalParam FuncActualParams ExpStmt
%nterm <exprtype> Exp Cond PrimaryExp LVal
%nterm <exprtype> SeventhExp SixthExp FifthExp FourthExp ThirdExp SecondExp FirstExp 
%nterm <type> Type 


%precedence THEN
%precedence ELSE
%%
Program
    : Stmts {
        //Stmt作为根节点
        ast.setRoot($1);
    }
    ;
Stmts
    : Stmt {$$=$1;}
    | Stmts Stmt{
        //两个及以上的语句
        $$ = new SeqNode($1, $2);
    }
    ;
Stmt
    : AssignStmt {$$=$1;}
    | BlockStmt {$$=$1;}
    | IfStmt {$$=$1;}
    | ReturnStmt {$$=$1;}
    | DeclStmt {$$=$1;}
    | FuncDef {$$=$1;}
    | DoWhileStmt {$$=$1;}
    | WhileStmt {$$=$1;}
    | SwitchStmt {$$=$1;}
    | ForStmt {$$=$1;}
    | ExpStmt SEMICOLON {
        //不能直接用Exp SEMICOLON 会说类型不匹配
        $$=$1;}
    |   SEMICOLON {
        //空语句
        $$ = new EmptyStmt();}
    ;
//左值表达式
LVal
    : ID {
        SymbolEntry *se;
        se = identifiers->lookup($1);
        //没有找到当前的ID
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            //违反这个断言，报错
            assert(se != nullptr);
        }
        //新建一个ID
        $$ = new Id(se);
        delete []$1;
    }
    ;
//赋值语句
AssignStmt
    :
    LVal ASSIGN Exp SEMICOLON {
        $$ = new AssignStmt($1, $3);
    }
    ;
// 单个/多个表达式语句，主要用处是把stmt转化为expr
ExpStmt
    :   ExpStmt COMMA Exp {
            ExprStmtNode* node = (ExprStmtNode*)$1;
            node->addNext($3);
            $$ = node;
        }
    |   Exp {
            ExprStmtNode* node = new ExprStmtNode();
            node->addNext($1);
            $$ = node;
        }
    ;
//语句块
BlockStmt
    :   LBRACE 
        {
            //新建作用域
            identifiers = new SymbolTable(identifiers);
        } 
        Stmts RBRACE 
        {
            //为什么是$3？——{}也算一个$
            $$ = new CompoundStmt($3);
            //}之后应该回到之前的作用域
            SymbolTable *top = identifiers;
            identifiers = identifiers->getPrev();
            delete top;
        }
        | 
        LBRACE RBRACE {
        //增加一个为空情况，不加报错
        $$ = new CompoundStmt();
    }
    ;
    ;
//if else语句——已给出
IfStmt
    : IF LPAREN Cond RPAREN Stmt %prec THEN {
        $$ = new IfStmt($3, $5);
    }
    | IF LPAREN Cond RPAREN Stmt ELSE Stmt {
        $$ = new IfElseStmt($3, $5, $7);
    }
    ;
//return语句——已给出
ReturnStmt
    :
    RETURN Exp SEMICOLON{
        $$ = new ReturnStmt($2);
    }
    |
    RETURN SEMICOLON
    {
        //新增一个return;语句
        $$ = new ReturnStmt(nullptr);
    }
    ;
//新增do while语句——暂时用不到
DoWhileStmt
    :
    DO LBRACE Stmt RBRACE WHILE LPAREN Cond RPAREN {
        $$=new DoWhileStmt($3,$7);
    }
    ;
//新增while语句
WhileStmt
    :
    WHILE LPAREN Cond RPAREN Stmt{
        //对应代码形如：while(条件){}或者while(条件);
        //因此$5为stmt
        $$=new WhileStmt($3,$5);
    }
    ;
//新增switch语句——暂时用不到
SwitchStmt
    :
    SWITCH LPAREN Cond RPAREN LBRACE Stmt RBRACE {
        $$=new SwitchStmt($3,$6);
    }
    ;
//新增for语句——暂时用不到
ForStmt
    :
    FOR LPAREN Cond RPAREN LBRACE Stmt RBRACE {
        $$=new ForStmt($3,$6);
    }
    ;
//表达式，类别为exprnode
Exp
    :
    SeventhExp 
    {
        //从最低优先级开始
        $$ = $1;
    }
    ;
//条件语句——已给出
Cond
    :
    SeventhExp {$$ = $1;}
    ;
//最低级 或 
//按照c++十四级运算符优先级定义的话是第九级
//但是再加就报错了也不知道为什么：）
SeventhExp
    :
    SixthExp {$$ = $1;}
    |
    SeventhExp OROR SixthExp
    {
        //表达式都为临时符号表项
        // ||
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::OROR, $1, $3);
    }
    ;
//&&
SixthExp
    :
    FifthExp {$$ = $1;}
    |
    SixthExp ANDAND FifthExp
    {
        //&&
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::ANDAND, $1, $3);
    }
    ;
//大于 小于 大于等于 小于等于 等于 不等于
FifthExp
    :
    FourthExp {$$ = $1;}
    |
    FifthExp LESS FourthExp
    {   //<
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LESS, $1, $3);
    }
    |
    FifthExp GREATER FourthExp
    {
        // >
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::GREATER, $1, $3);
    }
    |
    FifthExp GEQUAL FourthExp
    {
        //>=
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::GEQUAL, $1, $3);
    }
    |
    FifthExp LEQUAL FourthExp
    {
        //<=
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LEQUAL, $1, $3);
    }
    |
    FifthExp EQUAL FourthExp
    {
        //==
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::EQUAL, $1, $3);
    }
    |
    FifthExp NOTEQUAL FourthExp
    {
        //!=
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::NOTEQUAL, $1, $3);
    }
    ;
//左移 右移
FourthExp
    :
    ThirdExp {$$ = $1;}
    |
    FourthExp MLEFT ThirdExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::MLEFT, $1, $3);
    }
    |
    FourthExp MRIGHT ThirdExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::MRIGHT, $1, $3);
    }
    ;
//加减
ThirdExp
    :
    SecondExp {$$ = $1;}
    |
    ThirdExp ADD SecondExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::ADD, $1, $3);
    }
    |
    ThirdExp SUB SecondExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::SUB, $1, $3);
    }
    ;
//乘除取模
SecondExp
    :
    FirstExp {$$ = $1;}
    |
    SecondExp MUL FirstExp
    {
        //比加法高一级的应该是乘除法
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::MUL, $1, $3);
    }
    |
    SecondExp DIV FirstExp
    {
        //除法
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::DIV, $1, $3);
    }
    |
    SecondExp MOD FirstExp
    {
        // %
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::MOD, $1, $3);
    }
    ;
//单目运算符 正负非
FirstExp
    :
    PrimaryExp {$$=$1;}
    |
    TILDE FirstExp
    {
        //这里一定要是FirstExp
        //因为程序中有!!!!!!a这种东西……
        // !
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new OneOpExpr(se, OneOpExpr::TILDE, $2);
    }
    | SUB FirstExp
    {
        //此处为负号
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new OneOpExpr(se, OneOpExpr::SUB, $2);
    }
    | ADD FirstExp 
    {
        //此处意为“正”，对原数字没有影响，直接相等即可。
        $$=$2;
    }
    ;
//整数 左值表达式 函数值
PrimaryExp
    :
    LVal {
        $$ = $1;
    }
    |
    INTEGER 
    {
        //把这个整数的value一并传进去
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, $1);
        $$ = new Constant(se);
    }
    |
    LPAREN Exp RPAREN {
        //要跳回最低优先级
        $$=$2;
    }
    |   ID LPAREN FuncActualParams RPAREN {
        //调用函数的优先级也属于此优先级
        //是函数表达式 调用实参
            SymbolEntry *se;
            se = identifiers->lookup($1);
            //要先判定是不是已经有的函数
            //找不到的话说明是未出现过的ID，不可能是函数，报错
            if(se == nullptr)
            {
                fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
                delete [](char*)$1;
                assert(se != nullptr);
            }
            SymbolEntry *tmp = new TemporarySymbolEntry(se->getType(), SymbolTable::getLabel());
            //这里属于函数调用，所以也打印一下
            $$ = new FuncCallNode(tmp, new Id(se), (FuncParamsNode*)$3);
        }
    ;
//类型识别，之后需要新增float
Type
    : INT {
        $$ = TypeSystem::intType;
    }
    | VOID {
        $$ = TypeSystem::voidType;
    }
    ;
//修改，分为常量声明和变量声明
DeclStmt
    :
    VarDeclStmt {$$=$1;}
    |
    ConstDeclStmt {$$=$1;}
    ;
//常量声明语句 const int a,b,c,d;
ConstDeclStmt
    :
    CONST Type ConstDefs SEMICOLON {$$=$3; }
    ;
//多个常量共同定义
ConstDefs
    :
    ConstDef {$$=$1;}
    |
    ConstDefs COMMA ConstDef {
        //常量标识符列表
        $$=$1;
        $1->setnext($3);
    }
    ;
//单个常量
ConstDef
    :
    ID ASSIGN Exp {
        //赋值语句
        SymbolEntry *se;
        //新建符号表项
        se = new IdentifierSymbolEntry(TypeSystem::intType, $1, identifiers->getLevel());
        identifiers->install($1, se);
        //设置值
        ((IdentifierSymbolEntry*)se)->setValue($3->getValue());
        $$ = new ConstDef(new Id(se));
        delete []$1;
    }
    ;
//变量声明语句
VarDeclStmt
    :
    Type VarDefs SEMICOLON {
        //变量声明语句
        $$=$2;
    }
    ;
//多个变量
VarDefs
    :
    VarDef {
        $$=$1;
    }
    |
    VarDefs COMMA VarDef{
        $$=$1;
        $1->setnext($3);
    }
    ;
//单个变量 原理与常量相同，但表项类别为identifier
VarDef
    :
    ID {
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(TypeSystem::intType, $1, identifiers->getLevel());
        identifiers->install($1, se);
        $$ = new VarDef(new Id(se));
        delete []$1;
    }
    |
    ID ASSIGN Exp {
        //赋值语句
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(TypeSystem::intType, $1, identifiers->getLevel());
        identifiers->install($1, se);
        ((IdentifierSymbolEntry*)se)->setValue($3->getValue());
        $$ = new VarDef(new Id(se));
        delete []$1;
    }
    ;
//函数定义
FuncDef
    :
    Type ID {
        //类型为函数
        Type *funcType;
        //返回值类型为Type，
        funcType = new FunctionType($1,{});
        //新建符号表项，type，name，scope
        SymbolEntry *se = new IdentifierSymbolEntry(funcType, $2, identifiers->getLevel());
        //放入当前符号表内
        identifiers->install($2, se);
        //进入这个函数的符号表范围
        identifiers = new SymbolTable(identifiers);
    }
    LPAREN FuncFormalParams {
            SymbolEntry *se;
            se = identifiers->lookup($2);
            //这个断言的作用是检查之前是否正确把ID放入符号表
            assert(se != nullptr);
            //如果形参不为空，则放入参数列表
            if($5!=nullptr){
                //将函数参数类型写入符号表
                //将$5（函数参数）的的Type给这个函数的各个参数
                //(FunctionType*)(se->getType())就是上个代码的funcType
                ((FunctionType*)(se->getType()))->setparamsType(((FuncDefParamsNode*)$5)->getParamsType());
            }
            //至此完成了给这个符号表项设置完参数
    }
    RPAREN
    BlockStmt
    {
        SymbolEntry *se;
        se = identifiers->lookup($2);//$2是ID
        //设置$$，因为得返回这个$$
        $$ = new FunctionDef(se, (FuncDefParamsNode*)$5, $8);
    }
    ;
// 函数形参列表
FuncFormalParams
    :   FuncFormalParams COMMA SingleFuncFormalParam {
            FuncDefParamsNode* node = (FuncDefParamsNode*)$1;
            node->addNext(((SingleFuncParamNode*)$3)->getId());
            //node->addNext($3);
            $$ = node;
        }
    |   SingleFuncFormalParam {
            FuncDefParamsNode* node = new FuncDefParamsNode();
            node->addNext(((SingleFuncParamNode*)$1)->getId());
            $$ = node;
        }
    |   %empty {
            $$ = nullptr;
        }
    ;
// 函数形参
SingleFuncFormalParam
    :   Type ID {
            SymbolEntry *se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel());
            identifiers->install($2, se);
            $$=new SingleFuncParamNode(new Id(se));
        }
    ;
//调用函数所用的实参表
FuncActualParams
    :   FuncActualParams COMMA Exp {
            FuncParamsNode* node = (FuncParamsNode*) $1;
            node->addNext($3);
            $$ = node;
        }
    |   Exp {
            FuncParamsNode* node = new FuncParamsNode();
            node->addNext($1);
            $$ = node;
        }
    |   %empty {
        //无参
            $$ = nullptr;
        }
    ;
%%

int yyerror(char const* message)
{
    std::cerr<<message<<std::endl;
    return -1;
}