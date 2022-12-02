#ifndef __AST_H__
#define __AST_H__

#include <fstream>
#include "SymbolTable.h"
//class SymbolEntry;

class Node
{
private:
    static int counter;
    int seq;
    Node *next;//用于标识符列表的处理
public:
    Node();
    int getSeq() const {return seq;};
    virtual void output(int level) = 0;
    Node* getnext(){return next;}
    void setnext(Node *node);
};


class ExprNode : public Node
{
protected:
    SymbolEntry *symbolEntry;
public:
    ExprNode(SymbolEntry *symbolEntry) : symbolEntry(symbolEntry){};
    virtual int getValue() {return 0;}//获取存储的值
    void output(int level);//输出一下
    SymbolEntry *getentry(){return symbolEntry;}
    Type* getType() {return symbolEntry->getType();}
};

//双目运算符
class BinaryExpr : public ExprNode
{
private:
    int op;
    ExprNode *expr1, *expr2;
public:
    enum {ADD,
    SUB,
    AND,
    OR,
    LESS,
    MUL, 
    DIV, 
    GREATER, 
    EXCLA, 
    GEQUAL, 
    LEQUAL,
    EQUAL,
    NOTEQUAL, 
    MOD , 
    MLEFT,
    MRIGHT ,
    ANDAND ,
    OROR,
    ASSIGN, 
    ASSIGNADD, 
    ASSIGNSUB,
    ASSIGNDIV,
    ASSIGNSTAR
    };//在此处需要新增很多运算
    //
    BinaryExpr(SymbolEntry *se, int op, ExprNode*expr1, ExprNode*expr2) : ExprNode(se), op(op), expr1(expr1), expr2(expr2){};
    void output(int level);
    int getValue();
};
//单目运算符的实现
class OneOpExpr : public ExprNode
{
private:
    int op;
    ExprNode *expr;
public:
    enum {SUB, TILDE};
    OneOpExpr(SymbolEntry *se, int op, ExprNode* expr): ExprNode(se), op(op), expr(expr){};
    void output(int level);
    int getValue();
};

//node转符号表项
class Constant : public ExprNode
{
public:
    Constant(SymbolEntry *se) : ExprNode(se){};
    void output(int level);
    int getValue();//重写此方法
};

//Id继承了ExprNode
//私有成员只有一个symbolentry
class Id : public ExprNode
{
public:
    Id(SymbolEntry *se) : ExprNode(se){};
    void output(int level);
    SymbolEntry* getSymbolEntry() {return symbolEntry;}
};

//建立这个class的作用是为了把stmt类型转化为node
//因此能够打印成节点
class StmtNode : public Node
{};
//复合语句
class CompoundStmt : public StmtNode
{
private:
    StmtNode *stmt;
public:
    CompoundStmt(StmtNode *stmt = nullptr) : stmt(stmt) {};
    void output(int level);
};

class SeqNode : public StmtNode
{
private:
    StmtNode *stmt1, *stmt2;
public:
    SeqNode(StmtNode *stmt1, StmtNode *stmt2) : stmt1(stmt1), stmt2(stmt2){};
    void output(int level);
};

class DeclStmt : public StmtNode
{
private:
    Id *id;
    StmtNode *stmt1;
public:
    DeclStmt(Id* id, StmtNode *stmt=nullptr) :id(id), stmt1(stmt){};
    void output(int level);
};

//写明常量声明语句块
class ConstDef : public StmtNode
{
private:
    Id *id;
    //是不是需要新加initval的东西？
public:
    ConstDef(Id *id) : id(id){};
    void output(int level);
};
//变量声明
class VarDef : public StmtNode
{
private:
    Id *id;
    //是不是需要新加initval的东西？
public:
    VarDef(Id *id) : id(id){};
    void output(int level);
};
//常量s声明
class ConstDefs : public StmtNode
{
private:
    ConstDef* constdef;
public:
    ConstDefs(ConstDef* constdef) : constdef(constdef){};
    void output(int level);
};

//变量s声明
class VarDefs : public StmtNode
{
private:
    VarDef* vardef;
public:
    VarDefs(VarDef* vardef) : vardef(vardef){}
    void output(int level);
};
//常量声明语句
class ConstDeclStmt : public StmtNode
{
private:
    ConstDefs* constdefs;
public:
    ConstDeclStmt(ConstDefs* constdefs) : constdefs(constdefs){};
    void output(int level);
};
//变量声明语句
class VarDeclStmt : public StmtNode
{
private:
    VarDefs* vardefs;
public:
    VarDeclStmt(VarDefs* vardefs) : vardefs(vardefs){}
    void output(int level);
};
//if语句
class IfStmt : public StmtNode
{
private:
    ExprNode *cond;//条件，一般是一个表达式
    StmtNode *thenStmt;//具体的动作
public:
    IfStmt(ExprNode *cond, StmtNode *thenStmt) : cond(cond), thenStmt(thenStmt){};
    void output(int level);
};
//if else语句
class IfElseStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *thenStmt;
    StmtNode *elseStmt;
public:
    IfElseStmt(ExprNode *cond, StmtNode *thenStmt, StmtNode *elseStmt) : cond(cond), thenStmt(thenStmt), elseStmt(elseStmt) {};
    void output(int level);
};

//撰写while语句块
class WhileStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *stmt;
public:
    WhileStmt(ExprNode *cond,StmtNode *stmt) : cond(cond), stmt(stmt){};
    void output(int level);
};

//do while语句块
class DoWhileStmt : public StmtNode
{
private:
    StmtNode *stmt;
    ExprNode *cond;
public:
    DoWhileStmt(StmtNode *stmt,ExprNode *cond) : stmt(stmt), cond(cond){};
    void output(int level);
};

//switch语句块
class SwitchStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *stmt;
public:
    SwitchStmt(ExprNode *cond,StmtNode *stmt) : cond(cond), stmt(stmt){};
    void output(int level);
};
//for语句
class ForStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *stmt;
public:
    ForStmt(ExprNode *cond,StmtNode *stmt) : cond(cond), stmt(stmt){};
    void output(int level);
};
//return语句
class ReturnStmt : public StmtNode
{
private:
    ExprNode *retValue;
public:
    ReturnStmt(ExprNode*retValue = nullptr) : retValue(retValue) {};
    void output(int level);
};
//赋值语句
class AssignStmt : public StmtNode
{
private:
    ExprNode *lval;//id继承自exprnode
    ExprNode *expr;
public:
    AssignStmt(ExprNode *lval, ExprNode *expr);
    void output(int level);
};


//新建一个class用来传函数形参的。用于将Id转化为StmtNode类型
class SingleFuncParamNode : public StmtNode
{
private:
    Id* id;
public:
    SingleFuncParamNode(Id* id):id(id) {};
    Id* getId() {return id;}
    void output(int level);
};


//函数定义参数列表
class FuncDefParamsNode : public StmtNode
{
private:
    std::vector<Id*> paramsList;
public:
    FuncDefParamsNode() {};
    void addNext(Id* next);
    std::vector<Type*> getParamsType();
    void output(int level);
};
//函数定义/声明
class FunctionDef : public StmtNode
{
private:
    SymbolEntry *se;
    FuncDefParamsNode *params;
    StmtNode *stmt;
public:
    FunctionDef(SymbolEntry *se, FuncDefParamsNode *params, StmtNode *stmt) : se(se), params(params), stmt(stmt){};
    void output(int level);
};

//新建一个class用来记录函数参数节点
//这样在打印的时候好显示
class FuncParamsNode : public StmtNode
{
private:
    std::vector<ExprNode*> paramsList;
public:
    FuncParamsNode(){};
    void addNext(ExprNode* next);
    void output(int level);
};

//函数调用节点
class FuncCallNode : public ExprNode
{
private:
    Id* funcId;
    FuncParamsNode* params;//调用的参数
public:
    FuncCallNode(SymbolEntry *se, Id* id, FuncParamsNode* params) : ExprNode(se), funcId(id), params(params){};
    void output(int level);
};

//单独表达式语句也需要一个class
class ExprStmtNode : public StmtNode
{
private:
    std::vector<ExprNode*> exprList;
public:
    ExprStmtNode(){};
    void addNext(ExprNode* next);
    void output(int level);
};

//空语句也建一个吧。
class EmptyStmt : public StmtNode
{
public:
    EmptyStmt(){};
    void output(int level);
};

class Ast
{
private:
    Node* root;
public:
    Ast() {root = nullptr;}
    void setRoot(Node*n) {root = n;}
    void output();
};

#endif
