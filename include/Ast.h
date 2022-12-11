#ifndef __AST_H__
#define __AST_H__

#include <fstream>
#include "Operand.h"
#include "SymbolTable.h"
#include "Unit.h"
#include "Function.h"
#include "BasicBlock.h"
#include "Instruction.h"
#include "IRBuilder.h"
#include "Type.h"

class Node
{
private:
    static int counter;
    int seq;
    Node *next;//用于标识符列表的处理
//以下protected变量的意义是什么？
protected:
    //两个list用于回填函数的使用
    std::vector<Instruction*> true_list;//跳转为真的跳转指令的列表
    std::vector<Instruction*> false_list;//跳转false的跳转指令的列表
    static IRBuilder *builder;//
    //回填实现
    void backPatch(std::vector<Instruction*> &list, BasicBlock*bb);
    std::vector<Instruction*> merge(std::vector<Instruction*> &list1, std::vector<Instruction*> &list2);

public:
    Node();
    int getSeq() const {return seq;};
    static void setIRBuilder(IRBuilder*ib) {builder = ib;};
    virtual void output(int level) = 0;
    //类型检查函数
    //在return时需要判别来自于哪个函数
    virtual  void typeCheck(Node* fromnode=nullptr)= 0;
    //中间代码翻译
    virtual void genCode() = 0;
    std::vector<Instruction*>& trueList() {return true_list;}
    std::vector<Instruction*>& falseList() {return false_list;}
    //以下为新增函数实现
    Node* getnext(){return next;}
    void setnext(Node *node);
};

class ExprNode : public Node
{
protected:
    SymbolEntry *symbolEntry;
    Operand *dst;   //操作数
    Type * type;
public:
    ExprNode(SymbolEntry *symbolEntry) : symbolEntry(symbolEntry){};
    Operand* getOperand() {return dst;};
    SymbolEntry* getSymPtr() {return symbolEntry;};
    //新增
    virtual int getValue() {return 0;}//获取存储的值
    void output(int level);//输出一下
    SymbolEntry *getentry(){return symbolEntry;}
    Type* getType() {return symbolEntry->getType();}
    void genCode();
    void typeCheck(Node* fromnode);
    
};

class BinaryExpr : public ExprNode
{
private:
    int op;
    ExprNode *expr1, *expr2;
public:
    enum {ADD,//+ BinaryInstruction
    SUB,//- BinaryInstruction
    MUL, //* BinaryInstruction
    MOD , // % BinaryInstruction
    DIV, // / BinaryInstruction
    AND,// &
    OR,// |
    LESS,//< CmpInstruction
    GEQUAL, // >= CmpInstruction
    LEQUAL, //<= CmpInstruction
    EQUAL,// == CmpInstruction
    NOTEQUAL, // != CmpInstruction
    GREATER, // > CmpInstruction
    EXCLA, 
    MLEFT,
    MRIGHT ,
    ANDAND , //回填 √
    OROR, //回填 √
    ASSIGN, 
    ASSIGNADD, 
    ASSIGNSUB,
    ASSIGNDIV,
    ASSIGNSTAR
    };//在此处需要新增很多运算
    //
    BinaryExpr(SymbolEntry *se, int op, ExprNode*expr1, ExprNode*expr2) : ExprNode(se), op(op), expr1(expr1), expr2(expr2){dst = new Operand(se);};
    void output(int level);
    void typeCheck(Node* fromnode);
    void genCode();
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
    OneOpExpr(SymbolEntry *se, int op, ExprNode* expr);
    void output(int level);
    int getValue();
    //lab6需要新增对node中新增函数的实现
    void typeCheck(Node* fromnode);
    void genCode();
    int getOp() const { return op; };
    void setType(Type* type) { this->type = type; }
};

//node转符号表项
class Constant : public ExprNode
{
public:
    Constant(SymbolEntry *se) : ExprNode(se)
    {
        dst = new Operand(se);
        type=TypeSystem::intType;//常数为int类型
    };
    void output(int level);
    void typeCheck(Node* fromnode);
    void genCode();
    //新增
    int getValue();//重写此方法
};

//Id继承了ExprNode
//私有成员只有一个symbolentry
class Id : public ExprNode
{
public:
    Id(SymbolEntry *se) : ExprNode(se)
    {
        type=se->getType();
        SymbolEntry *temp = new TemporarySymbolEntry(se->getType(), SymbolTable::getLabel());
        dst = new Operand(temp);
    };
    void output(int level);
    void typeCheck(Node* fromnode);
    void genCode();
    int getValue();
    Type* getType();
    SymbolEntry* getSymbolEntry() {return symbolEntry;}
};

//建立这个class的作用是为了把stmt类型转化为node
//因此能够打印成节点
class StmtNode : public Node
{
private:
    int kind;

protected:
    enum { IF, IFELSE, WHILE, COMPOUND, RETURN };

public:
    StmtNode(int kind = -1) : kind(kind){};
    bool isIf() const { return kind == IF; };
    virtual void typeCheck(Node* fromnode = nullptr) = 0;
};

//复合语句
class CompoundStmt : public StmtNode
{
private:
    StmtNode *stmt;
public:
    CompoundStmt(StmtNode *stmt = nullptr) : stmt(stmt) {};
    void output(int level);
    void typeCheck(Node* fromnode);
    void genCode();
};

class SeqNode : public StmtNode
{
private:
    StmtNode *stmt1, *stmt2;
public:
    SeqNode(StmtNode *stmt1, StmtNode *stmt2) : stmt1(stmt1), stmt2(stmt2){};
    void output(int level);
    void typeCheck(Node* fromnode);
    void genCode();
};

class DeclStmt : public StmtNode
{
private:
    Id *id;
    StmtNode *stmt1;
public:
    DeclStmt(Id* id, StmtNode *stmt=nullptr) :id(id), stmt1(stmt){};
    void output(int level);
    void typeCheck(Node* fromnode);
    void genCode();
    Id* getId() { return id; };
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
    //lab6需要新增对node中新增函数的实现
    void typeCheck(Node* fromnode) ;
    void genCode();
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
    //lab6需要新增对node中新增函数的实现
    void typeCheck(Node* fromnode);
    void genCode();
};

//if语句
class IfStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *thenStmt;
public:
    IfStmt(ExprNode *cond, StmtNode *thenStmt) : cond(cond), thenStmt(thenStmt){};
    void output(int level);
    void typeCheck(Node* fromnode);
    void genCode();
};

class IfElseStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *thenStmt;
    StmtNode *elseStmt;
public:
    IfElseStmt(ExprNode *cond, StmtNode *thenStmt, StmtNode *elseStmt) : cond(cond), thenStmt(thenStmt), elseStmt(elseStmt) {};
    void output(int level);
    void typeCheck(Node* fromnode);
    void genCode();
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
    //lab6需要新增对node中新增函数的实现
    void typeCheck(Node* fromnode);
    void genCode();
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
    //lab6需要新增对node中新增函数的实现
    void typeCheck(Node* fromnode) {}
    void genCode() {}
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
    //lab6需要新增对node中新增函数的实现
    void typeCheck(Node* fromnode) {}
    void genCode() {}
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
    //lab6需要新增对node中新增函数的实现
    void typeCheck(Node* fromnode);
    void genCode() ;
};

class ReturnStmt : public StmtNode
{
private:
    ExprNode *retValue;
public:
    ReturnStmt(ExprNode*retValue) : retValue(retValue) {};
    void output(int level);
    void typeCheck(Node* fromnode);
    void genCode();
};

class AssignStmt : public StmtNode
{
private:
    ExprNode *lval;
    ExprNode *expr;
public:
    AssignStmt(ExprNode *lval, ExprNode *expr);
    void output(int level);
    void typeCheck(Node* fromnode);
    void genCode();
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
    //lab6需要新增对node中新增函数的实现
    void typeCheck(Node* fromnode);
    void genCode();
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
    //lab6需要新增对node中新增函数的实现
    void typeCheck(Node* fromnode);
    void genCode();
};

//函数定义
class FunctionDef : public StmtNode
{
private:
    SymbolEntry *se;//对应的符号表项
    FuncDefParamsNode *params;//参数
    StmtNode *stmt;//动作
public:
    FunctionDef(SymbolEntry *se, FuncDefParamsNode *params, StmtNode *stmt) : se(se), params(params), stmt(stmt){};
    void output(int level);
    void typeCheck(Node* fromnode);
    void genCode();
    SymbolEntry * getEntry() {return this->se;};
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
    //lab6需要新增对node中新增函数的实现
    void typeCheck(Node* fromnode);
    void genCode();
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
    //lab6需要新增对node中新增函数的实现
    void typeCheck(Node* fromnode);
    void genCode();
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
    //lab6需要新增对node中新增函数的实现
    void typeCheck(Node* fromnode) ;
    void genCode() ;
};

//空语句也建一个吧。
class EmptyStmt : public StmtNode
{
public:
    EmptyStmt(){};
    void output(int level);
    //lab6需要新增对node中新增函数的实现
    void typeCheck(Node* fromnode) ;
    void genCode() ;
};

class Ast
{
private:
    Node* root;
public:
    Ast() {root = nullptr;}
    void setRoot(Node*n) {root = n;}
    void output();
    void typeCheck(Node* fromnode);
    void genCode(Unit *unit);
};

#endif
