#ifndef __AST_H__
#define __AST_H__

#include <fstream>
#include <iostream>
#include <stack>
#include "Operand.h"
#include "Type.h"

class SymbolEntry;
class Unit;
class Function;
class BasicBlock;
class Instruction;
class IRBuilder;


class Node {
   private:
    static int counter;
    int seq;
    Node* next; // 用于标识符列表的处理

   protected:
    std::vector<Instruction*> true_list;//跳转为真且跳转地址相同的跳转指令的链表
    std::vector<Instruction*> false_list;//跳转false的跳转指令的链表
    static IRBuilder* builder;
    //回填实现
    void backPatch(std::vector<Instruction*>& list, BasicBlock* bb);
    std::vector<Instruction*> merge(std::vector<Instruction*>& list1,
                                    std::vector<Instruction*>& list2);

   public:
    Node();
    int getSeq() const { return seq; };
    static void setIRBuilder(IRBuilder* ib) { builder = ib; };
    virtual void output(int level) = 0;
    void setNext(Node* node);
    Node* getNext() { return next; }
    //类型检查函数
    //在return时需要判别来自于哪个函数
    virtual void typeCheck( ) = 0;
    //中间代码翻译
    virtual void genCode() = 0;
    std::vector<Instruction*>& trueList() { return true_list; }
    std::vector<Instruction*>& falseList() { return false_list; }
};


class ExprNode : public Node {
   private:
    int kind;

   protected:
    enum { EXPR, INITVALUELISTEXPR, ONEOPEXPR };
    Type* type;
    SymbolEntry* symbolEntry;
    Operand* dst;  // The result of the subtree is stored into dst.
   public:
    ExprNode(SymbolEntry* symbolEntry, int kind = EXPR)
        : kind(kind), symbolEntry(symbolEntry){};
    Operand* getOperand() { return dst; };
    void output(int level);
    virtual int getValue() { return -1; };
    bool isExpr() const { return kind == EXPR; };
    bool isInitValueListExpr() const { return kind == INITVALUELISTEXPR; };
    //是一元运算
    bool isOneOpExpr() const { return kind == ONEOPEXPR; };
    SymbolEntry* getSymPtr() { return symbolEntry; };
    virtual void typeCheck() {  };
    void genCode();
    virtual Type* getType() { return type; };
    Type* getOriginType() { return type; };
    void SetDst(Operand* newdst) { this->dst=newdst; };
};

//二元运算符的实现
class BinaryExpr : public ExprNode {
   private:
    int op;
    ExprNode *expr1, *expr2;

   public:
    enum {
        ADD,
        SUB,
        MUL,
        DIV,
        MOD,
        AND,
        OR,
        LESS,
        LESSEQUAL,
        GREATER,
        GREATEREQUAL,
        EQUAL,
        NOTEQUAL
    };
    BinaryExpr(SymbolEntry* se, int op, ExprNode* expr1, ExprNode* expr2);
    void output(int level);
    int getValue();
    void typeCheck();
    void genCode();
};

//一元运算符的实现
class OneOpExpr : public ExprNode {
   private:
    int op;
    ExprNode* expr;

   public:
    enum { NOT, SUB };
    OneOpExpr(SymbolEntry* se, int op, ExprNode* expr);
    void output(int level);
    int getValue();
    void typeCheck();
    void genCode();
    int getOp() const { return op; };
    void setType(Type* type) { this->type = type; }
};

//函数调用节点
class FuncCallNode : public ExprNode {
   private:
    ExprNode* param;

   public:
    FuncCallNode(SymbolEntry* se, ExprNode* param = nullptr);
    void output(int level);
    void typeCheck();
    void genCode();
};

class Constant : public ExprNode {
   public:
    Constant(SymbolEntry* se) : ExprNode(se) {
        dst = new Operand(se);
        type = TypeSystem::intType;
    };
    void output(int level);
    int getValue();
    void typeCheck();
    void genCode();
};

class Id : public ExprNode {
   private:
    ExprNode* arrIdx;
    bool left = false;

   public:
    Id(SymbolEntry* se, ExprNode* arrIdx = nullptr)
        : ExprNode(se), arrIdx(arrIdx) {
        if (se) {
            type = se->getType();
            if (type->isInt()) {
                SymbolEntry* temp = new TemporarySymbolEntry(
                    TypeSystem::intType, SymbolTable::getLabel());
                dst = new Operand(temp);
            } else if (type->isArray()) {
                SymbolEntry* temp = new TemporarySymbolEntry(
                    new PointerType(((ArrayType*)type)->getElementType()),
                    SymbolTable::getLabel());
                dst = new Operand(temp);
            }
        }
    };
    void output(int level);
    void typeCheck();
    void genCode();
    int getValue();
    ExprNode* getArrIdx() { return arrIdx; };
    Type* getType();
    bool isLeft() const { return left; };
    void setLeft() { left = true; }
};


//数组类型初值
class InitValueListExpr : public ExprNode {
   private:
    ExprNode* expr;
    int childCnt;

   public:
    InitValueListExpr(SymbolEntry* se, ExprNode* expr = nullptr)
        : ExprNode(se, INITVALUELISTEXPR), expr(expr) {
        type = se->getType();
        childCnt = 0;
    };
    void output(int level);
    ExprNode* getExpr() const { return expr; };
    void addExpr(ExprNode* expr);
    bool isEmpty() { return childCnt == 0; };
    bool isFull();
    void typeCheck();
    void genCode();
    void fill();
};

//建立这个class的作用是为了把stmt类型转化为node
//因此能够打印成节点
class StmtNode : public Node {
   private:
    int kind;

   protected:
    enum { IF, IFELSE, WHILE, COMPOUND, RETURN };

   public:
    StmtNode(int kind = -1) : kind(kind){};
    bool isIf() const { return kind == IF; };
    virtual void typeCheck() = 0;
};

//复合语句
class CompoundStmt : public StmtNode {
   private:
    StmtNode* stmt;

   public:
    CompoundStmt(StmtNode* stmt = nullptr) : stmt(stmt){};
    void output(int level);
    void typeCheck();
    void genCode();
};

class SeqNode : public StmtNode {
   private:
    StmtNode *stmt1, *stmt2;

   public:
    SeqNode(StmtNode* stmt1, StmtNode* stmt2) : stmt1(stmt1), stmt2(stmt2){};
    void output(int level);
    void typeCheck();
    void genCode();
};

class DeclStmt : public StmtNode {
   private:
    Id* id;
    ExprNode* expr;

   public:
    DeclStmt(Id* id, ExprNode* expr = nullptr) : id(id) {
        if (expr) {
            this->expr = expr;
            if (expr->isInitValueListExpr())
                ((InitValueListExpr*)(this->expr))->fill();
        }
    };
    void output(int level);
    void typeCheck();
    void genCode();
    Id* getId() { return id; };
};

class EmptyStmt : public StmtNode {
   public:
    EmptyStmt(){};
    void output(int level);
    void typeCheck();
    void genCode();
};

class IfStmt : public StmtNode {
   private:
    ExprNode* cond;
    StmtNode* thenStmt;

   public:
    IfStmt(ExprNode* cond, StmtNode* thenStmt)
        : cond(cond), thenStmt(thenStmt) {
    };
    void output(int level);
    void typeCheck();
    void genCode();
};

class IfElseStmt : public StmtNode {
   private:
    ExprNode* cond;
    StmtNode* thenStmt;
    StmtNode* elseStmt;

   public:
    IfElseStmt(ExprNode* cond, StmtNode* thenStmt, StmtNode* elseStmt)
        : cond(cond), thenStmt(thenStmt), elseStmt(elseStmt) {
    };
    void output(int level);
    void typeCheck();
    void genCode();
};

class WhileStmt : public StmtNode {
   private:
    ExprNode* cond;
    StmtNode* stmt;
    BasicBlock* cond_bb;//每次循环都要验证，因此新做一个bb
    BasicBlock* end_bb;//为break语句设置
   public:
    WhileStmt(ExprNode* cond, StmtNode* stmt=nullptr) : cond(cond), stmt(stmt) {
    };
    void setStmt(StmtNode* stmt){this->stmt = stmt;};
    void output(int level);
    void typeCheck();
    void genCode();
    BasicBlock* get_cond_bb(){return this->cond_bb;};
    BasicBlock* get_end_bb(){return this->end_bb;};
};

class BreakStmt : public StmtNode {
    private:
    StmtNode * whileStmt;
   public:
    BreakStmt(StmtNode* whileStmt){this->whileStmt=whileStmt;};
    void output(int level);
    void typeCheck();
    void genCode();
};

class ContinueStmt : public StmtNode {
    private:
    StmtNode *whileStmt;
   public:
    ContinueStmt(StmtNode* whileStmt){this->whileStmt=whileStmt;};
    void output(int level);
    void typeCheck();
    void genCode();
};

class ReturnStmt : public StmtNode {
   private:
    ExprNode* retValue;

   public:
    ReturnStmt(ExprNode* retValue = nullptr) : retValue(retValue){};
    void output(int level);
    void typeCheck();
    void genCode();
};

class AssignStmt : public StmtNode {
   private:
    ExprNode* lval;
    ExprNode* expr;

   public:
    AssignStmt(ExprNode* lval, ExprNode* expr);
    void output(int level);
    void typeCheck();
    void genCode();
};

class ExprStmt : public StmtNode {
   private:
    ExprNode* expr;

   public:
    ExprStmt(ExprNode* expr) : expr(expr){};
    void output(int level);
    void typeCheck();
    void genCode();
};

//函数定义
class FunctionDef : public StmtNode {
   private:
    SymbolEntry* se; // 对应的符号表现
    DeclStmt* decl;
    StmtNode* stmt; // 动作

   public:
    FunctionDef(SymbolEntry* se, DeclStmt* decl, StmtNode* stmt)
        : se(se), decl(decl), stmt(stmt){};
    void output(int level);
    void typeCheck();
    void genCode();
    SymbolEntry* getSymPtr() { return se; };
};

class Ast {
   private:
    Node* root;
   public:
    Ast() { root = nullptr; }
    void setRoot(Node* n) { root = n; }
    void output();
    void typeCheck();
    void genCode(Unit* unit);
};
#endif
