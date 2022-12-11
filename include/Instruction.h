#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include "Operand.h"
#include <vector>
#include <map>

class BasicBlock;

class Instruction
{
protected:
    unsigned instType;//指令类型
    unsigned opcode;//操作码
    Instruction *prev;//前一个指令
    Instruction *next;//下一个指令
    BasicBlock *parent;//标识当前指令来自于哪一个基本块
    std::vector<Operand*> operands;//操作数
    //LoadInstruction 从内存地址中加载值到中间变量中。
    //StoreInstruction 将值存储到内存地址中。
    //BinaryInstruction 二元运算指令, 包含一个目的操作数和两个源操作数。
    //CmpInstruction 关系运算指令。
    //CondBrInstruction 条件跳转指令，分支为真和为假时分别跳转到基本块 true_branch和 false_branch。
    //UncondBrInstruction 无条件跳转指令，直接跳转到基本块 branch。
    //RetInstruction 函数返回指令。
    //AllocaInstruction 在内存中分配空间。
    enum {BINARY, COND, UNCOND, RET, LOAD, STORE, CMP, ALLOCA};//指令类型
public:
    Instruction(unsigned instType, BasicBlock *insert_bb = nullptr);
    virtual ~Instruction();
    BasicBlock *getParent();
    bool isUncond() const {return instType == UNCOND;};
    bool isCond() const {return instType == COND;};
    bool isRet() const {return instType==RET;};
    void setParent(BasicBlock *);
    void setNext(Instruction *);
    void setPrev(Instruction *);
    Instruction *getNext();
    Instruction *getPrev();
    virtual void output() const = 0;
};

// meaningless instruction, used as the head node of the instruction list.
//无任何意义的指令，用来作为指令列表的头节点
class DummyInstruction : public Instruction
{
public:
    //该指令的类型为-1（无意义），
    DummyInstruction() : Instruction(-1, nullptr) {};
    void output() const {};
};

class AllocaInstruction : public Instruction
{
public:
    AllocaInstruction(Operand *dst, SymbolEntry *se, BasicBlock *insert_bb = nullptr);
    ~AllocaInstruction();
    void output() const;
private:
    SymbolEntry *se;
};

class LoadInstruction : public Instruction
{
public:
    LoadInstruction(Operand *dst, Operand *src_addr, BasicBlock *insert_bb = nullptr);
    ~LoadInstruction();
    void output() const;
};

class StoreInstruction : public Instruction
{
public:
    StoreInstruction(Operand *dst_addr, Operand *src, BasicBlock *insert_bb = nullptr);
    ~StoreInstruction();
    void output() const;
};

class BinaryInstruction : public Instruction
{
public:
    BinaryInstruction(unsigned opcode, Operand *dst, Operand *src1, Operand *src2, BasicBlock *insert_bb = nullptr);
    ~BinaryInstruction();
    void output() const;
    enum {SUB, ADD,MUL,MOD,DIV, AND, OR};
};

class CmpInstruction : public Instruction
{
public:
    CmpInstruction(unsigned opcode, Operand *dst, Operand *src1, Operand *src2, BasicBlock *insert_bb = nullptr);
    ~CmpInstruction();
    void output() const;
    enum {E, NE, L, GE, G, LE};
};

// unconditional branch
class UncondBrInstruction : public Instruction
{
public:
    UncondBrInstruction(BasicBlock*, BasicBlock *insert_bb = nullptr);
    void output() const;
    void setBranch(BasicBlock *);
    BasicBlock *getBranch();
protected:
    BasicBlock *branch;
};

// conditional branch
class CondBrInstruction : public Instruction
{
public:
    CondBrInstruction(BasicBlock*, BasicBlock*, Operand *, BasicBlock *insert_bb = nullptr);
    ~CondBrInstruction();
    void output() const;
    void setTrueBranch(BasicBlock*);
    BasicBlock* getTrueBranch();
    void setFalseBranch(BasicBlock*);
    BasicBlock* getFalseBranch();
protected:
    BasicBlock* true_branch;//条件为真时跳转的块
    BasicBlock* false_branch;//条件为假时跳转的块
};

class RetInstruction : public Instruction
{
public:
    RetInstruction(Operand *src, BasicBlock *insert_bb = nullptr);
    ~RetInstruction();
    void output() const;
};

#endif