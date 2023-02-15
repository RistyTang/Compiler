#include "SymbolTable.h"
#include <string>
#include "Type.h"
#include "Ast.h"

extern FILE *yyout;
int Node::counter = 0;

Node::Node()
{
    seq = counter++;
}
//IntegerLiteral
void Node::setnext(Node* node) 
{
    Node* n = this;
    while (n->getnext()) {
        n = n->getnext();
    }
    if (n == this) {
        this->next = node;
    } else {
        n->setnext(node);
    }
}

void Ast::output()
{
    fprintf(yyout, "program\n");
    if(root != nullptr)
        root->output(4);
}

void SingleFuncParamNode::output(int level)
{
    fprintf(yyout, "%*cSingleFuncFormalParam\n", level, ' ');
    id->output(level+4);
}

void ExprNode::output(int level) 
{
    std::string type, value;
    type = symbolEntry->getType()->toStr();
    value = symbolEntry->toStr();
    fprintf(yyout, "%*cconst string\tvalue: %s\ttype: %s\n", level, ' ',
            value.c_str(), type.c_str());
}

void BinaryExpr::output(int level)
{
    std::string op_str;
    //int results=0;
    switch(op)
    {
        case ADD:
            op_str = "add";
            break;
        case SUB:
            op_str = "sub";
            break;
        case AND:
            op_str = "and";
            break;
        case OR:
            op_str = "or";
            break;
        case LESS:
            op_str = "less";
            break;
        case MUL:
            op_str = "mul";
            break;
        case DIV:
            op_str = "div";
            break;
        case GREATER:
            op_str = "greater";
            break;
        case EXCLA:
            op_str = "excla";//!
            break;
        case GEQUAL:
            op_str = "gequal";//>=
            break;
        case LEQUAL:
            op_str = "lequal";//<=
            break;
        case EQUAL:
            op_str = "equal";//==
            break;
        case NOTEQUAL:
            op_str = "notequal";
            break;//!=
        case MOD:
            op_str = "mod";
            break;
        case MLEFT:
            op_str = "mleft";//左移
            break;
        case MRIGHT:
            op_str="mright";//右移
            break;
        case ANDAND:
            op_str="andand";//&&
            break;
        case OROR:
            op_str="oror";//||
            break;
        case ASSIGN:
            op_str="assign";//=
            break;
        case ASSIGNADD:
            op_str="assignadd";//+=
            break;
        case ASSIGNSUB:
            op_str="assignsub";//-=
            break;
        case ASSIGNDIV:
            op_str="assigndiv";///=
            break;
        case ASSIGNSTAR:
            op_str="assignstar";// *=
            break;
    }
    //results=this->getValue();
    //fprintf(yyout, "%*cBinaryExpr\top: %s\t\tresults: %d\n", level, ' ', op_str.c_str(),results);
    fprintf(yyout, "%*cBinaryExpr\top: %s\t\n", level, ' ', op_str.c_str());
    expr1->output(level + 4);
    if(expr2)
    {    
        expr2->output(level + 4);
    }
}

int BinaryExpr::getValue()
{
    int result=0;
    switch(op)
    {
        case ADD:
            if(expr2)
            {
                //result=dynamic_cast<IdentifierSymbolEntry*>(expr1->getentry())->getValue()+dynamic_cast<IdentifierSymbolEntry*>(expr2->getentry())->getValue();
                result = expr1->getValue() + expr2->getValue();
            }
            break;
        case SUB:
            result = expr1->getValue() - expr2->getValue();
            break;
        case LESS:
            if(expr2)
            {
                result = expr1->getValue() < expr2->getValue();}
            break;
        case MUL:
            if(expr2)
            {
                result = expr1->getValue() * expr2->getValue();
            }
            break;
        case DIV:
        if(expr2->getValue()!=0)
            {
                result =(int) (expr1->getValue() / expr2->getValue());
            }
            break;
        case GREATER:
        if(expr2)
            {result = expr1->getValue() > expr2->getValue();}
            break;
        case GEQUAL:
        if(expr2)
            {result = expr1->getValue() >= expr2->getValue();}
            break;
        case LEQUAL:
        if(expr2)
            {result = expr1->getValue()<= expr2->getValue();}
            break;
        case EQUAL:
        if(expr2)
            {result = expr1->getValue()==expr2->getValue();}
            break;
        case NOTEQUAL:
        if(expr2)
            {result = expr1->getValue()!=expr2->getValue();}
            break;//!=
        case MOD:
        if(expr2->getValue()!=0)
            {
                result =(int) (expr1->getValue() % expr2->getValue());
            }
            break;//%
        case MLEFT:
        if(expr2)
            {result = expr1->getValue() << expr2->getValue();}
            break;
        case MRIGHT:
        if(expr2)
            {result = (expr1->getValue()) >> (expr2->getValue());}
            break;
        case ANDAND:
        if(expr2)
            {result = expr1->getValue() && expr2->getValue();}
            break;
        case OROR:
        if(expr2)
            {result = expr1->getValue() || expr2->getValue();}
            break;
    }
    return result;
}

int OneOpExpr::getValue()
{
    int result;
    switch (op) 
    {
        case TILDE:
            result = ! (expr->getValue());
            break;
        case SUB:
            result = - (expr->getValue());
            break;
    }
    return result;
}
void OneOpExpr::output(int level) 
{
    std::string op_str;
    switch (op) 
    {
        case TILDE:
            op_str = "not";
            break;
        case SUB:
            op_str = "minus";
            break;
    }
    fprintf(yyout, "%*cOneOpExpr\top: %s\t\n", level, ' ', op_str.c_str());
    expr->output(level + 4);
}

int Constant::getValue()
{
    return ((ConstantSymbolEntry*)symbolEntry)->getValue();
}

void Constant::output(int level)
{
    std::string type, value;
    type = symbolEntry->getType()->toStr();
    value = symbolEntry->toStr();
    //是整数

    fprintf(yyout, "%*cIntegerLiteral\tvalue: %s\ttype: %s\n", level, ' ',
            value.c_str(), type.c_str());
}

void Id::output(int level)
{
    std::string name, type;
    int scope;
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();
    scope = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getScope();
    int value;
    value = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getValue();
    fprintf(yyout, "%*cId\tname: %s\tscope: %d\ttype: %s\tvalue:%d\n", level, ' ',
        name.c_str(), scope, type.c_str(),value);
    
}

void CompoundStmt::output(int level)
{
    fprintf(yyout, "%*cCompoundStmt\n", level, ' ');
    if(stmt)
        stmt->output(level + 4);
}

void SeqNode::output(int level)
{
    fprintf(yyout, "%*cSequence\n", level, ' ');
    stmt1->output(level + 4);
    stmt2->output(level + 4);
}

void DeclStmt::output(int level)
{
    //fprintf(yyout, "%*cDeclStmt\n", level, ' ');
    id->output(level + 4);
}

void ConstDeclStmt::output(int level)
{
    fprintf(yyout, "%*cConstDeclStmt\n", level, ' ');
    constdefs->output(level+4);
}

void ConstDefs::output(int level)
{
    fprintf(yyout, "%*cConstDefs\n", level, ' ');
    constdef->output(level+4);
}

void IfStmt::output(int level)
{
    fprintf(yyout, "%*cIfStmt\n", level, ' ');
    cond->output(level + 4);
    thenStmt->output(level + 4);
}

void IfElseStmt::output(int level)
{
    fprintf(yyout, "%*cIfElseStmt\n", level, ' ');
    cond->output(level + 4);
    thenStmt->output(level + 4);
    elseStmt->output(level + 4);
}

//while语句块增加
void WhileStmt::output(int level)
{
    fprintf(yyout, "%*cWhileStmt\n", level, ' ');
    cond->output(level + 4);
    stmt->output(level + 4);
}

//do while
void DoWhileStmt::output(int level)
{
    fprintf(yyout, "%*cDoWhileStmt\n", level, ' ');
    stmt->output(level + 4);
    cond->output(level + 4);
}
//switch
void SwitchStmt::output(int level)
{
    fprintf(yyout, "%*cWhileStmt\n", level, ' ');
    cond->output(level + 4);
    stmt->output(level + 4);
}
//for
void ForStmt::output(int level)
{
    fprintf(yyout, "%*cForStmt\n", level, ' ');
    cond->output(level + 4);
    stmt->output(level + 4);
}

void ReturnStmt::output(int level)
{
    fprintf(yyout, "%*cReturnStmt\n", level, ' ');
    retValue->output(level + 4);
}

void AssignStmt::output(int level)
{
    fprintf(yyout, "%*cAssignStmt\n", level, ' ');
    lval->output(level + 4 );
    expr->output(level + 4);
}

void FunctionDef::output(int level)
{
    std::string name, type;
    name = se->toStr();
    type = se->getType()->toStr();
    fprintf(yyout, "%*cFunctionDefine function name: %s, type: %s\n", level, ' ', 
            name.c_str(), type.c_str());
    if(params!=nullptr)
    {
        params->output(level+4);
    }
    else{
        fprintf(yyout, "%*cFuncDefParamsNode NULL\n", level+4, ' ');
    }
    stmt->output(level + 4);
}

void ConstDef::output(int level)
{
    fprintf(yyout, "%*cConstDef\n", level, ' ');
    id->output(level + 4);//输出id
    //可能有很多个。
    if(this->getnext())
    {
        this->getnext()->output(level);
    }
}
void VarDeclStmt::output(int level)
{
    fprintf(yyout, "%*cVarDeclStmt\n", level, ' ');
    vardefs->output(level+4);
}
void VarDefs::output(int level)
{
    fprintf(yyout, "%*cVarDefs\n", level, ' ');
    vardef->output(level+4);
}
void VarDef::output(int level)
{
    fprintf(yyout, "%*cVarDef\n", level, ' ');
    id->output(level + 4);//输出id
    //可能有很多个。
    if(this->getnext())
    {
        this->getnext()->output(level);
    }
}
//重写assignstmt，修改标识符
AssignStmt::AssignStmt(ExprNode *lval, ExprNode *expr) : lval(lval), expr(expr)
{
    int value=expr->getValue();
    //value = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getValue();
    dynamic_cast<IdentifierSymbolEntry*>(lval->getentry())->setValue(value);

}

void FuncDefParamsNode::addNext(Id* next)
{
    paramsList.push_back(next);
}

std::vector<Type*> FuncDefParamsNode::getParamsType()
{
    std::vector<Type*> typeArray;
    for(auto param : paramsList)
    {
        typeArray.push_back(param->getType());
    }
    return typeArray;
}

void FuncDefParamsNode::output(int level)
{
    fprintf(yyout, "%*cFuncDefParamsNode\n", level, ' ');
    for(auto param : paramsList){
        param->output(level+4);
    }
}

void FuncParamsNode::addNext(ExprNode* next)
{
    paramsList.push_back(next);
}

void FuncParamsNode::output(int level)
{
    fprintf(yyout, "%*cFuncParamsNode\n", level, ' ');
    for(auto param : paramsList){
        param->output(level+4);
    }
}

void FuncCallNode::output(int level)
{
    std::string name, type;
    int scope;
    SymbolEntry* funcEntry = funcId->getSymbolEntry();
    name = funcEntry->toStr();
    type = funcEntry->getType()->toStr();
    scope = dynamic_cast<IdentifierSymbolEntry*>(funcEntry)->getScope();
    fprintf(yyout, "%*cFuncCallNode\tfuncName: %s\t funcType: %s\tscope: %d\n", 
            level, ' ', name.c_str(), type.c_str(), scope);
    if(params!=nullptr){
        params->output(level+4);
    }
    else{
        fprintf(yyout, "%*cFuncParamsNode NULL\n", level+4, ' ');
    }
}
void ExprStmtNode::addNext(ExprNode* next)
{
    exprList.push_back(next);
}

void ExprStmtNode::output(int level)
{
    fprintf(yyout, "%*cExprStmtNode\n", level, ' ');
    for(auto expr : exprList)
    {
        expr->output(level+4);
    }
}

void EmptyStmt::output(int level)
{
    fprintf(yyout, "%*cEmptyStmt\n", level, ' ');
}