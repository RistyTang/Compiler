#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include <map>
#include <sstream>
#include <vector>
#include "AsmBuilder.h"
#include "Operand.h"

class BasicBlock;

class Instruction {
   public:
    Instruction(unsigned instType, BasicBlock* insert_bb = nullptr);
    virtual ~Instruction();
    BasicBlock* getParent();
    bool isUncond() const { return instType == UNCOND; };
    bool isCond() const { return instType == COND; };
    bool isAlloc() const { return instType == ALLOCA; };
    bool isRet() const { return instType == RET; };
    void setParent(BasicBlock*);
    void setNext(Instruction*);
    void setPrev(Instruction*);
    Instruction* getNext();
    Instruction* getPrev();
    virtual void output() const = 0;
    MachineOperand* genMachineOperand(Operand*);
    MachineOperand* genMachineReg(int reg);
    MachineOperand* genMachineVReg();
    MachineOperand* genMachineImm(int val);
    MachineOperand* genMachineLabel(int block_no);
    virtual void genMachineCode(AsmBuilder*) = 0;
   protected:
    unsigned instType;
    unsigned opcode;
    Instruction* prev;
    Instruction* next;
    BasicBlock* parent;
    std::vector<Operand*> operands;
    enum {
        BINARY,
        COND,
        UNCOND,
        RET,
        LOAD,
        STORE,
        CMP,
        ALLOCA,
        CALL,
        EXTEND,
        XOR,
        GEP
    };
};

// meaningless instruction, used as the head node of the instruction list.
class DummyInstruction : public Instruction {
   public:
    DummyInstruction() : Instruction(-1, nullptr){};
    void output() const {};
    void genMachineCode(AsmBuilder*){};
};

class AllocaInstruction : public Instruction {
   public:
    AllocaInstruction(Operand* dst,
                      SymbolEntry* se,
                      BasicBlock* insert_bb = nullptr);
    ~AllocaInstruction();
    void output() const;
    void genMachineCode(AsmBuilder*);

   private:
    SymbolEntry* se;
};

class LoadInstruction : public Instruction {
   public:
    LoadInstruction(Operand* dst,
                    Operand* src_addr,
                    BasicBlock* insert_bb = nullptr);
    ~LoadInstruction();
    void output() const;
    void genMachineCode(AsmBuilder*);
};

class StoreInstruction : public Instruction {
   public:
    StoreInstruction(Operand* dst_addr,
                     Operand* src,
                     BasicBlock* insert_bb = nullptr);
    ~StoreInstruction();
    void output() const;
    void genMachineCode(AsmBuilder*);
};

class BinaryInstruction : public Instruction {
   public:
    BinaryInstruction(unsigned opcode,
                      Operand* dst,
                      Operand* src1,
                      Operand* src2,
                      BasicBlock* insert_bb = nullptr);
    ~BinaryInstruction();
    void output() const;
    void genMachineCode(AsmBuilder*);
    enum Type { SUB, ADD, AND, OR, MUL, DIV, MOD, NOT };
    static BinaryMInstruction::opType toBinaryMType(BinaryInstruction::Type t);
};

class CmpInstruction : public Instruction {
   public:
    CmpInstruction(unsigned opcode,
                   Operand* dst,
                   Operand* src1,
                   Operand* src2,
                   BasicBlock* insert_bb = nullptr);
    ~CmpInstruction();
    void output() const;
    void genMachineCode(AsmBuilder*);
    enum { E, NE, L, LE, G, GE };
    bool isLessOrGreater(unsigned opcode){
        return opcode == L || opcode == LE || opcode == G || opcode == GE;
    }
};

// unconditional branch
class UncondBrInstruction : public Instruction {
   public:
    UncondBrInstruction(BasicBlock*, BasicBlock* insert_bb = nullptr);
    void output() const;
    void setBranch(BasicBlock*);
    BasicBlock* getBranch();
    void genMachineCode(AsmBuilder*);

   protected:
    BasicBlock* branch;
};

// conditional branch
class CondBrInstruction : public Instruction {
   public:
    CondBrInstruction(BasicBlock*,
                      BasicBlock*,
                      Operand*,
                      BasicBlock* insert_bb = nullptr);
    ~CondBrInstruction();
    void output() const;
    void setTrueBranch(BasicBlock*);
    BasicBlock* getTrueBranch();
    void setFalseBranch(BasicBlock*);
    BasicBlock* getFalseBranch();
    void genMachineCode(AsmBuilder*);

   protected:
    BasicBlock* true_branch;
    BasicBlock* false_branch;
};

class RetInstruction : public Instruction 
{
   public:
    RetInstruction(Operand* src, BasicBlock* insert_bb = nullptr);
    ~RetInstruction();
    void output() const;
    void genMachineCode(AsmBuilder*);
    void insertOperand(AsmBuilder*);
    void insertFunction(AsmBuilder*);
    void insertBx(AsmBuilder*);
};

//函数调用
class CallInstruction : public Instruction {
   private:
    SymbolEntry* func;//函数名称
    Operand* dst;
 
   public:
    CallInstruction(Operand* dst,
                    SymbolEntry* func,
                    std::vector<Operand*> params,
                    BasicBlock* insert_bb = nullptr);
    ~CallInstruction();
    void output() const;
    void genMachineCode(AsmBuilder*);
    void BelowParams(AsmBuilder*);
    void OverParams(AsmBuilder*);
    void BranchRestore(AsmBuilder*);
    void RetValue(AsmBuilder*);
};


//%6 = zext i1 %5 to i32
//将1位的bool扩展到32位
class ExtensionInstruction : public Instruction {
   public:
    ExtensionInstruction(Operand* dst,
                    Operand* src,
                    BasicBlock* insert_bb = nullptr);
    ~ExtensionInstruction();
    void output() const;
    void genMachineCode(AsmBuilder*);
};

//获取聚合数据结构的子元素的地址
class GepInstruction : public Instruction {
   private:
    bool paramFirst;//是函数参数
    bool first;//最低维度数组的第一个元素
    bool last;//最后一个元素
    Operand* init;//上一个最低维度数组的dst
 
   public:
    GepInstruction(Operand* dst,//要进行计算原始指针的类型
                   Operand* arr,//数组首地址指针
                   Operand* idx,//当于offset,指明要操作的是第几个元素
                   BasicBlock* insert_bb = nullptr,
                   bool paramFirst = false);
    ~GepInstruction();
    void output() const;
    void genMachineCode(AsmBuilder*);
    void setFirst() { first = true; };
    void setLast() { last = true; };
    Operand* getInit() const { return init; };
    void setInit(Operand* init) { this->init = init; };
 
    void genInit(AsmBuilder*);
    void insertImm(AsmBuilder*, MachineOperand* &);
    void calcSize(AsmBuilder* builder, int& size);
    void handleFirst(AsmBuilder* builder, MachineOperand*& base);
    void insertMovLoad(AsmBuilder* builder, int v, MachineOperand*&);
    void handleParamFirst(AsmBuilder* builder, MachineOperand*, MachineOperand*);
 
    template<typename... Args>
    void insertAdd(AsmBuilder* builder, Args... args)
    {
        auto cur_block = builder->getBlock();
        auto cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::ADD, args...);
 
        cur_block->InsertInst(cur_inst);
    }
};

#endif
