#include "Instruction.h"
#include <iostream>
#include <sstream>
#include "BasicBlock.h"
#include "Function.h"
#include "Type.h"
extern FILE* yyout;

Instruction::Instruction(unsigned instType, BasicBlock* insert_bb) {
    prev = next = this;
    opcode = -1;
    this->instType = instType;
    if (insert_bb != nullptr) {
        insert_bb->insertBack(this);
        parent = insert_bb;
    }
}

Instruction::~Instruction() {
    parent->remove(this);
}

BasicBlock* Instruction::getParent() {
    return parent;
}

void Instruction::setParent(BasicBlock* bb) {
    parent = bb;
}

void Instruction::setNext(Instruction* inst) {
    next = inst;
}

void Instruction::setPrev(Instruction* inst) {
    prev = inst;
}

Instruction* Instruction::getNext() {
    return next;
}

Instruction* Instruction::getPrev() {
    return prev;
}

BinaryInstruction::BinaryInstruction(unsigned opcode,
                                     Operand* dst,
                                     Operand* src1,
                                     Operand* src2,
                                     BasicBlock* insert_bb)
    : Instruction(BINARY, insert_bb) {
    this->opcode = opcode;
    operands.push_back(dst);
    operands.push_back(src1);
    operands.push_back(src2);
    dst->setDef(this);
    src1->addUse(this);
    src2->addUse(this);
}

BinaryInstruction::~BinaryInstruction() {
    operands[0]->setDef(nullptr);
    if (operands[0]->usersNum() == 0)
        delete operands[0];
    operands[1]->removeUse(this);
    operands[2]->removeUse(this);
}

void BinaryInstruction::output() const {
    std::string s1, s2, s3, op, type;
    s1 = operands[0]->toStr();
    s2 = operands[1]->toStr();
    s3 = operands[2]->toStr();
    type = operands[1]->getType()->toStr();
    if(opcode==NOT)
    {
        op="xor";
        fprintf(yyout, "  %s = %s %s %s, %s\n", s1.c_str(), op.c_str(), type.c_str(), s2.c_str(), "true");
        return;
    }
    else
    {
        switch (opcode) 
        {
            case ADD:
                op = "add";
                break;
            case SUB:
                op = "sub";
                break;
            case MUL:
                op = "mul";
                break;
            case DIV:
                op = "sdiv";
                break;
            case MOD:
                op = "srem";
                break;
            default:
                break;
        }
        fprintf(yyout, "  %s = %s %s %s, %s\n", s1.c_str(), op.c_str(),
                type.c_str(), s2.c_str(), s3.c_str());
    }
}

CmpInstruction::CmpInstruction(unsigned opcode,
                               Operand* dst,
                               Operand* src1,
                               Operand* src2,
                               BasicBlock* insert_bb)
    : Instruction(CMP, insert_bb) {
    this->opcode = opcode;
    operands.push_back(dst);
    operands.push_back(src1);
    operands.push_back(src2);
    dst->setDef(this);
    src1->addUse(this);
    src2->addUse(this);
}

CmpInstruction::~CmpInstruction() {
    operands[0]->setDef(nullptr);
    if (operands[0]->usersNum() == 0)
        delete operands[0];
    operands[1]->removeUse(this);
    operands[2]->removeUse(this);
}

void CmpInstruction::output() const {
    std::string s1, s2, s3, op, type;
    s1 = operands[0]->toStr();
    s2 = operands[1]->toStr();
    s3 = operands[2]->toStr();
    type = operands[1]->getType()->toStr();
    switch (opcode) {
        case E:
            op = "eq";
            break;
        case NE:
            op = "ne";
            break;
        case L:
            op = "slt";
            break;
        case LE:
            op = "sle";
            break;
        case G:
            op = "sgt";
            break;
        case GE:
            op = "sge";
            break;
        default:
            op = "";
            break;
    }

    fprintf(yyout, "  %s = icmp %s %s %s, %s\n", s1.c_str(), op.c_str(),
            type.c_str(), s2.c_str(), s3.c_str());
}

UncondBrInstruction::UncondBrInstruction(BasicBlock* to, BasicBlock* insert_bb)
    : Instruction(UNCOND, insert_bb) {
    branch = to;
}

void UncondBrInstruction::output() const {
    fprintf(yyout, "  br label %%B%d\n", branch->getNo());
}

void UncondBrInstruction::setBranch(BasicBlock* bb) {
    branch = bb;
}

BasicBlock* UncondBrInstruction::getBranch() {
    return branch;
}

CondBrInstruction::CondBrInstruction(BasicBlock* true_branch,
                                     BasicBlock* false_branch,
                                     Operand* cond,
                                     BasicBlock* insert_bb)
    : Instruction(COND, insert_bb) {
    this->true_branch = true_branch;
    this->false_branch = false_branch;
    cond->addUse(this);
    operands.push_back(cond);
}

CondBrInstruction::~CondBrInstruction() {
    operands[0]->removeUse(this);
}

void CondBrInstruction::output() const {
    std::string cond, type;
    cond = operands[0]->toStr();
    type = operands[0]->getType()->toStr();
    int true_label = true_branch->getNo();
    int false_label = false_branch->getNo();
    fprintf(yyout, "  br %s %s, label %%B%d, label %%B%d\n", type.c_str(),
            cond.c_str(), true_label, false_label);
}

void CondBrInstruction::setFalseBranch(BasicBlock* bb) {
    false_branch = bb;
}

BasicBlock* CondBrInstruction::getFalseBranch() {
    return false_branch;
}

void CondBrInstruction::setTrueBranch(BasicBlock* bb) {
    true_branch = bb;
}

BasicBlock* CondBrInstruction::getTrueBranch() {
    return true_branch;
}

RetInstruction::RetInstruction(Operand* src, BasicBlock* insert_bb)
    : Instruction(RET, insert_bb) {
    if (src != nullptr) {
        operands.push_back(src);
        src->addUse(this);
    }
}

RetInstruction::~RetInstruction() {
    if (!operands.empty())
        operands[0]->removeUse(this);
}

void RetInstruction::output() const {
    if (operands.empty()) {
        fprintf(yyout, "  ret void\n");
    } else {
        std::string ret, type;
        ret = operands[0]->toStr();
        type = operands[0]->getType()->toStr();
        fprintf(yyout, "  ret %s %s\n", type.c_str(), ret.c_str());
    }
}

AllocaInstruction::AllocaInstruction(Operand* dst,
                                     SymbolEntry* se,
                                     BasicBlock* insert_bb)
    : Instruction(ALLOCA, insert_bb) {
    operands.push_back(dst);
    dst->setDef(this);
    this->se = se;
}

AllocaInstruction::~AllocaInstruction() {
    operands[0]->setDef(nullptr);
    if (operands[0]->usersNum() == 0)
        delete operands[0];
}

void AllocaInstruction::output() const {
    std::string dst, type;
    dst = operands[0]->toStr();
    if (se->getType()->isInt()) {
        type = se->getType()->toStr();
        fprintf(yyout, "  %s = alloca %s, align 4\n", dst.c_str(),
                type.c_str());
    } else if (se->getType()->isArray()) {
        type = se->getType()->toStr();
        // type = operands[0]->getSymPtr()->getType()->toStr();
        fprintf(yyout, "  %s = alloca %s, align 4\n", dst.c_str(),
                type.c_str());
    }
}

LoadInstruction::LoadInstruction(Operand* dst,
                                 Operand* src_addr,
                                 BasicBlock* insert_bb)
    : Instruction(LOAD, insert_bb) {
    operands.push_back(dst);
    operands.push_back(src_addr);
    dst->setDef(this);
    src_addr->addUse(this);
}

LoadInstruction::~LoadInstruction() {
    operands[0]->setDef(nullptr);
    if (operands[0]->usersNum() == 0)
        delete operands[0];
    operands[1]->removeUse(this);
}

void LoadInstruction::output() const {
    std::string dst = operands[0]->toStr();
    std::string src = operands[1]->toStr();
    std::string src_type;
    std::string dst_type;
    dst_type = operands[0]->getType()->toStr();
    src_type = operands[1]->getType()->toStr();
    fprintf(yyout, "  %s = load %s, %s %s, align 4\n", dst.c_str(),
            dst_type.c_str(), src_type.c_str(), src.c_str());
}

StoreInstruction::StoreInstruction(Operand* dst_addr,
                                   Operand* src,
                                   BasicBlock* insert_bb)
    : Instruction(STORE, insert_bb) {
    operands.push_back(dst_addr);
    operands.push_back(src);
    dst_addr->addUse(this);
    src->addUse(this);
}

StoreInstruction::~StoreInstruction() {
    operands[0]->removeUse(this);
    operands[1]->removeUse(this);
}

void StoreInstruction::output() const {
    std::string dst = operands[0]->toStr();
    std::string src = operands[1]->toStr();
    std::string dst_type = operands[0]->getType()->toStr();
    std::string src_type = operands[1]->getType()->toStr();

    fprintf(yyout, "  store %s %s, %s %s, align 4\n", src_type.c_str(),
            src.c_str(), dst_type.c_str(), dst.c_str());
}

MachineOperand* Instruction::genMachineOperand(Operand* ope) 
{
    auto se = ope->getEntry();
    MachineOperand* mope = nullptr;
    //常数
    if (se->isConstant())
        mope = new MachineOperand(
            MachineOperand::IMM,
            dynamic_cast<ConstantSymbolEntry*>(se)->getValue());
    //临时变量
    else if (se->isTemporary())
        mope = new MachineOperand(
            MachineOperand::VREG,
            dynamic_cast<TemporarySymbolEntry*>(se)->getLabel());
    //变量
    else if (se->isVariable()) 
    {
        auto id_se = dynamic_cast<IdentifierSymbolEntry*>(se);
        //全局变量
        if (id_se->isGlobal())
            mope = new MachineOperand(id_se->toStr().c_str());
        //函数参数
        else if (id_se->isParam()) 
        {
            // TODO: 
            if (id_se->getParamNo() < 4)
                mope = new MachineOperand(MachineOperand::REG,
                                          id_se->getParamNo());
            else
                //复用r3
                mope = new MachineOperand(MachineOperand::REG, 3);
        } else
            exit(0);
    }
    return mope;
}

MachineOperand* Instruction::genMachineReg(int reg) {
    return new MachineOperand(MachineOperand::REG, reg);
}

MachineOperand* Instruction::genMachineVReg() {
    return new MachineOperand(MachineOperand::VREG, SymbolTable::getLabel());
}

MachineOperand* Instruction::genMachineImm(int val) {
    return new MachineOperand(MachineOperand::IMM, val);
}

MachineOperand* Instruction::genMachineLabel(int block_no) {
    std::ostringstream buf;
    buf << ".L" << block_no;
    std::string label = buf.str();
    return new MachineOperand(label);
}

void AllocaInstruction::genMachineCode(AsmBuilder* builder) {
    /* HINT:
     * Allocate stack space for local variabel
     * Store frame offset in symbol entry */
    auto cur_func = builder->getFunction();
    int size = se->getType()->getSize() / 8;
    if (size < 0)
        size = 4;
    int offset = cur_func->AllocSpace(size);
    auto se = (TemporarySymbolEntry*)operands[0]->getEntry();
    se->setOffset(-offset);
}

void LoadInstruction::genMachineCode(AsmBuilder* builder) {
    auto cur_block = builder->getBlock();
    MachineInstruction* cur_inst = nullptr;
    // Load global operand
    if (operands[1]->getEntry()->isVariable() &&
        dynamic_cast<IdentifierSymbolEntry*>(operands[1]->getEntry())
            ->isGlobal()) {
        auto dst = genMachineOperand(operands[0]);
        auto internal_reg1 = genMachineVReg();
        auto internal_reg2 = new MachineOperand(*internal_reg1);
        auto src = genMachineOperand(operands[1]);
        // example: load r0, addr_a
        cur_inst = new LoadMInstruction(cur_block, internal_reg1, src);
        cur_block->InsertInst(cur_inst);
        // example: load r1, [r0]
        cur_inst = new LoadMInstruction(cur_block, dst, internal_reg2);
        cur_block->InsertInst(cur_inst);
    }
    // Load local operand
    else if (operands[1]->getEntry()->isTemporary() && operands[1]->getDef() &&
             operands[1]->getDef()->isAlloc()) {
        // example: load r1, [r0, #4]
        auto dst = genMachineOperand(operands[0]);
        auto src1 = genMachineReg(11);
        int off = dynamic_cast<TemporarySymbolEntry*>(operands[1]->getEntry())
                      ->getOffset();
        auto src2 = genMachineImm(off);
        if (off > 255 || off < -255) {
            auto operand = genMachineVReg();
            cur_block->InsertInst(
                (new LoadMInstruction(cur_block, operand, src2)));
            src2 = operand;
        }
        cur_inst = new LoadMInstruction(cur_block, dst, src1, src2);
        cur_block->InsertInst(cur_inst);
    }
    // Load operand from temporary variable
    else {
        // example: load r1, [r0]
        auto dst = genMachineOperand(operands[0]);
        auto src = genMachineOperand(operands[1]);
        cur_inst = new LoadMInstruction(cur_block, dst, src);
        cur_block->InsertInst(cur_inst);
    }
}

void StoreInstruction::genMachineCode(AsmBuilder* builder) {
    auto cur_block = builder->getBlock();
    MachineInstruction* cur_inst = nullptr;
    auto src = genMachineOperand(operands[1]);
    // store immediate
    auto const_op1 = dynamic_cast<ConstantSymbolEntry*>(operands[1]->getEntry());
    if (const_op1) {
        MachineOperand* dst1;
        cur_block->InsertLoadInst(src, dst1);
        // src = dst1;
        src = new MachineOperand(*dst1);
    }
    // store to local
    auto temp_op0 = dynamic_cast<TemporarySymbolEntry*>(operands[0]->getEntry());
    auto variable_op0 = dynamic_cast<IdentifierSymbolEntry*>(operands[0]->getEntry());
    if (temp_op0 && operands[0]->getDef() &&
        operands[0]->getDef()->isAlloc()) {
        auto src1 = genMachineReg(11);
        int off = temp_op0->getOffset();
        auto src2 = genMachineImm(off);
        if (temp_op0->isOffsetOutbound()) {
            MachineOperand* operand;
            cur_block->InsertLoadInst(src2, operand);
            src2 = operand;
        }
        cur_inst = new StoreMInstruction(cur_block, src, src1, src2);
        cur_block->InsertInst(cur_inst);
    }
    // store to global
    else if (variable_op0 && variable_op0->isGlobal()) {
        // example: load r0, addr_a
        auto dst = genMachineOperand(operands[0]);
        MachineOperand* internal_reg1;
        cur_block->InsertLoadInst(dst, internal_reg1);
 
        // example: store r1, [r0]
        cur_inst = new StoreMInstruction(cur_block, src, internal_reg1);
        cur_block->InsertInst(cur_inst);
    }
    // store to pointer
    else if (operands[0]->getType()->isPtr()) {
        auto dst = genMachineOperand(operands[0]);
        cur_inst = new StoreMInstruction(cur_block, src, dst);
        cur_block->InsertInst(cur_inst);
    }
}

MachineOperand* replaceCmpImm(AsmBuilder* builder, MachineOperand* src){
    if (!src->isImm()){
        return src;
    }
    auto cur_block = builder->getBlock();
    auto internal_reg = MachineOperand::newVReg();
    auto cur_inst = new LoadMInstruction(cur_block, internal_reg, src);
    cur_block->InsertInst(cur_inst);
    return new MachineOperand(*internal_reg);
}
 
BinaryMInstruction::opType BinaryInstruction::toBinaryMType(BinaryInstruction::Type t){
    if (t == ADD){
        return BinaryMInstruction::ADD;
    } else if (t == SUB){
        return BinaryMInstruction::SUB;
    } else if (t == AND){
        return BinaryMInstruction::AND;
    } else if (t == OR){
        return BinaryMInstruction::OR;
    } else if (t == MUL){
        return BinaryMInstruction::MUL;
    } else {
        return BinaryMInstruction::DIV;
    }
}
 
void BinaryInstruction::genMachineCode(AsmBuilder* builder) {
    // complete other instructions
    auto cur_block = builder->getBlock();
    auto dst = genMachineOperand(operands[0]);
    auto src1 = genMachineOperand(operands[1]);
    auto src2 = genMachineOperand(operands[2]);
    /* HINT:
     * The source operands of ADD instruction in ir code both can be immediate
     * num. However, it's not allowed in assembly code. So you need to insert
     * LOAD/MOV instrucrion to load immediate num into register. As to other
     * instructions, such as MUL, CMP, you need to deal with this situation,
     * too.*/
    MachineInstruction* cur_inst = nullptr;
    if(opcode==NOT) {
        auto trueOperand = genMachineImm(1);
        auto falseOperand = genMachineImm(0);
        cur_inst = new MovMInstruction(cur_block, MovMInstruction::MOV, dst,
                                        trueOperand, MachineInstruction::EQ);
        cur_block->InsertInst(cur_inst);
        cur_inst = new MovMInstruction(cur_block, MovMInstruction::MOV, dst,
                                   falseOperand, MachineInstruction::NE);
        cur_block->InsertInst(cur_inst);
        return;
    }
    src1 = replaceCmpImm(builder, src1);
    // 合法立即数的判定太复杂 简单判定255以上均load
    // 这里应该也不需要考虑负数
    if (src2->isImm()) {
        if ((opcode <= BinaryInstruction::OR &&
             ((ConstantSymbolEntry*)(operands[2]->getEntry()))->getValue() > 255) ||
            opcode >= BinaryInstruction::MUL) {
            src2 = replaceCmpImm(builder, src2);
        }
    }
    if (opcode != MOD){
        auto binaryMType = toBinaryMType(BinaryInstruction::Type(opcode));
        cur_inst = new BinaryMInstruction(cur_block, binaryMType, dst, src1, src2);
            cur_block->InsertInst(cur_inst);
        return;
        }
            // c = a % b
            // c = a / b
    cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::DIV, dst, src1, src2);
            MachineOperand* dst1 = new MachineOperand(*dst);
            src1 = new MachineOperand(*src1);
            src2 = new MachineOperand(*src2);
            cur_block->InsertInst(cur_inst);
            // c = c * b
    cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::MUL, dst1, dst, src2);
            cur_block->InsertInst(cur_inst);
            dst = new MachineOperand(*dst1);
            // c = a - c
    cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::SUB, dst, src1, dst1);
    cur_block->InsertInst(cur_inst);
}
 
void insertCmpMov(AsmBuilder* builder, MachineOperand* dst, MachineOperand* op, unsigned opcode)
{
    auto cur_block = builder->getBlock();
    auto cur_inst = new MovMInstruction(cur_block, MovMInstruction::MOV, dst, op, opcode);
    cur_block->InsertInst(cur_inst);
}

void CmpInstruction::genMachineCode(AsmBuilder* builder) 
{
    //TODO
    //进行立即数合法化
    auto cur_block = builder->getBlock();
    auto src1 = genMachineOperand(operands[1]);
    auto src2 = genMachineOperand(operands[2]);
    if (src1->isImm()) 
    {
        src1 = replaceCmpImm(builder, src1);
    }
    if (src2->isImm() && ((ConstantSymbolEntry*)(operands[2]->getEntry()))->getValue() > 255) 
    {
        src2 = replaceCmpImm(builder, src2);
    }
    //生成汇编代码
    auto cur_inst = new CmpMInstruction(cur_block, src1, src2, opcode);
        cur_block->InsertInst(cur_inst);
    //如果是等于或者不等于的比较就不用再继续了
    if (!isLessOrGreater(opcode)){
        return;
    }
    //其余则需要mov结果
    auto dst = genMachineOperand(operands[0]);
    auto trueOperand = MachineOperand::newImm(1);
    auto falseOperand = MachineOperand::newImm(0);
    //记录结果true or false
    insertCmpMov(builder, dst, trueOperand, opcode);
    insertCmpMov(builder, dst, falseOperand, 7 - opcode);
}

void UncondBrInstruction::genMachineCode(AsmBuilder* builder) 
{
    //TODO
    auto cur_block = builder->getBlock();
    std::stringstream s;
    s << ".L" << branch->getNo();
    MachineOperand* dst = new MachineOperand(s.str());
    BranchMInstruction* cur_inst;
    cur_inst = new BranchMInstruction(cur_block, BranchMInstruction::B, dst);
    cur_block->InsertInst(cur_inst);
}
 
void CondBrInstruction::genMachineCode(AsmBuilder* builder) 
{
    //TODO
    auto cur_block = builder->getBlock();
    //true
    std::stringstream s1;
    s1 << ".L" << true_branch->getNo();
    MachineOperand* dst1 = new MachineOperand(s1.str());
    BranchMInstruction* cur_inst1;
    //如果条件为真
    cur_inst1 = new BranchMInstruction(cur_block, BranchMInstruction::B, dst1, cur_block->getCmpCond());
    cur_block->InsertInst(cur_inst1);
    
    //false
    std::stringstream s2;
    s2 << ".L" << false_branch->getNo();
    auto dst2 = new MachineOperand(s2.str());
    BranchMInstruction* cur_inst2;
    cur_inst2 = new BranchMInstruction(cur_block, BranchMInstruction::B, dst2);
    cur_block->InsertInst(cur_inst2);
}
 
void RetInstruction::insertOperand(AsmBuilder* builder)
{
    //没有返回值就直接返回
    if (operands.empty()){
        return;
    }
    //有返回值放入r0寄存器
    auto dst = new MachineOperand(MachineOperand::REG, 0);
    auto src = genMachineOperand(operands[0]);
    auto cur_block = builder->getBlock();
    auto cur_inst = new MovMInstruction(cur_block, MovMInstruction::MOV, dst, src);
    cur_block->InsertInst(cur_inst);
}

void RetInstruction::insertFunction(AsmBuilder* builder)
{
    auto cur_block = builder->getBlock();
    auto cur_func = builder->getFunction();
    auto sp = MachineOperand::newReg(MachineOperand::RegType::SP);
    auto size = new MachineOperand(MachineOperand::IMM, cur_func->AllocSpace(0));
    //生成ADD指令恢复栈帧
    auto cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::ADD,
                                           sp, sp, size);
    cur_block->InsertInst(cur_inst);
    //有 Callee saved 寄存器，我们还需要生成 POP 指令恢复这些寄存器
    //这一步在生成bx跳转指令时会完成
}
 
void RetInstruction::insertBx(AsmBuilder* builder)
{
    //生成跳转指令来返回到 Caller
    auto cur_block = builder->getBlock();
    auto lr = MachineOperand::newReg(MachineOperand::RegType::LR);
    auto cur_inst = new BranchMInstruction(cur_block, BranchMInstruction::BX, lr);
    cur_block->InsertInst(cur_inst);
}

void RetInstruction::genMachineCode(AsmBuilder* builder) 
{
    // TODO
    /* HINT:
     * 1. Generate mov instruction to save return value in r0
     * 2. Restore callee saved registers and sp, fp
     * 3. Generate bx instruction */
    //1
    insertOperand(builder);
    //2
    insertFunction(builder);
    //3
    insertBx(builder);
}

CallInstruction::CallInstruction(Operand* dst,
                                 SymbolEntry* func,
                                 std::vector<Operand*> params,
                                 BasicBlock* insert_bb)
    : Instruction(CALL, insert_bb), func(func), dst(dst) {
    operands.push_back(dst);
    if (dst)
        dst->setDef(this);
    for (auto param : params) {
        operands.push_back(param);
        param->addUse(this);
    }
}

void CallInstruction::BelowParams(AsmBuilder* builder)
{
    if (!operands.size()){
        return;
    }
    auto cur_block = builder->getBlock();
    auto it = operands.begin() + 1;
    //使用r0~r3传参
    for (int idx = 0; idx < 4 && it != operands.end(); ++idx, ++it)
    {
        auto operand = genMachineReg(idx);
        auto src = genMachineOperand(operands[idx+1]);
        MachineInstruction* cur_inst = nullptr;
        cur_inst = new MovMInstruction(cur_block, MovMInstruction::MOV, operand, src);
        cur_block->InsertInst(cur_inst);
    }
}

void CallInstruction::OverParams(AsmBuilder* builder)
{
    auto cur_block = builder->getBlock();
    for (int i = operands.size() - 1; i > 4; i--) 
    {
        auto operand = genMachineOperand(operands[i]);
        //操作对象是立即数
        if (operand->isImm()) 
        {
            MachineInstruction* cur_inst = nullptr;
            auto dst = MachineOperand::newVReg();
            cur_inst = new MovMInstruction(cur_block, MovMInstruction::MOV, dst, operand);
            cur_block->InsertInst(cur_inst);
            operand = dst;
        }
        //生成push指令传递参数
        auto cur_inst = new StackMInstrcuton(cur_block, StackMInstrcuton::PUSH, {}, operand);
        cur_block->InsertInst(cur_inst);
    }
}

void CallInstruction::BranchRestore(AsmBuilder* builder)
{
    auto cur_block = builder->getBlock();
    auto label = new MachineOperand(func->toStr().c_str());
    //跳转执行
    auto cur_inst = new BranchMInstruction(cur_block, BranchMInstruction::BL, label);
    cur_block->InsertInst(cur_inst);
    //恢复SP
    if (operands.size() >= 5) 
    {
        auto off = MachineOperand::newImm((operands.size() - 5) * 4);
        auto sp = MachineOperand::newReg(MachineOperand::RegType::SP);
        auto cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::ADD,
                                          sp, sp, off);
        cur_block->InsertInst(cur_inst);
    }
}

void CallInstruction::RetValue(AsmBuilder* builder)
{
    auto cur_block = builder->getBlock();
    //函数执行结果被用到，还需要保存 R0 寄存器中的返回值。
    if (dst) 
    {
        auto operand = genMachineOperand(dst);
        auto r0 = new MachineOperand(MachineOperand::REG, 0);
        auto cur_inst = new MovMInstruction(cur_block, MovMInstruction::MOV, operand, r0);
        cur_block->InsertInst(cur_inst);
    }
}

void CallInstruction::output() const 
{
    fprintf(yyout, "  ");
    if (operands[0])
        fprintf(yyout, "%s = ", operands[0]->toStr().c_str());
    FunctionType* type = (FunctionType*)(func->getType());
    fprintf(yyout, "call %s %s(", type->getRetType()->toStr().c_str(),
            func->toStr().c_str());
    for (long unsigned int i = 1; i < operands.size(); i++) {
        if (i != 1)
            fprintf(yyout, ", ");
        fprintf(yyout, "%s %s", operands[i]->getType()->toStr().c_str(),
                operands[i]->toStr().c_str());
    }
    fprintf(yyout, ")\n");
}

void CallInstruction::genMachineCode(AsmBuilder* builder) 
{
    //对于含参函数，需要使用 R0-R3 寄存器传递参数
    BelowParams(builder);
    //如果参数个数大于四个还需要生成 PUSH 指令来传递参数；
    OverParams(builder);
    BranchRestore(builder);
    RetValue(builder);
}

CallInstruction::~CallInstruction() {
    operands[0]->setDef(nullptr);
    if (operands[0]->usersNum() == 0)
        delete operands[0];
    for (long unsigned int i = 1; i < operands.size(); i++)
        operands[i]->removeUse(this);
}

ExtensionInstruction::ExtensionInstruction(Operand* dst,
                                 Operand* src,
                                 BasicBlock* insert_bb)
    : Instruction(EXTEND, insert_bb) {
    operands.push_back(dst);
    operands.push_back(src);
    dst->setDef(this);
    src->addUse(this);
}

void ExtensionInstruction::output() const {
    Operand* dst = operands[0];
    Operand* src = operands[1];
    fprintf(yyout, "  %s = zext %s %s to i32\n", dst->toStr().c_str(),
            src->getType()->toStr().c_str(), src->toStr().c_str());
}

ExtensionInstruction::~ExtensionInstruction() 
{
    operands[0]->setDef(nullptr);
    if (operands[0]->usersNum() == 0)
        delete operands[0];
    operands[1]->removeUse(this);
}


GepInstruction::GepInstruction(Operand* dst,
                               Operand* arr,
                               Operand* idx,
                               BasicBlock* insert_bb,
                               bool paramFirst)
    : Instruction(GEP, insert_bb), paramFirst(paramFirst) {
    operands.push_back(dst);
    operands.push_back(arr);
    operands.push_back(idx);
    dst->setDef(this);//要进行计算原始指针的类型
    arr->addUse(this);
    idx->addUse(this);//相当于offset,指明要操作的是第几个元素
    first = false;
    init = nullptr;
    last = false;
}

void GepInstruction::output() const 
{
    Operand* dst = operands[0];
    Operand* arr = operands[1];
    Operand* idx = operands[2];
    std::string arrType = arr->getType()->toStr();
    //%op2 = getelementptr [10 x i32], [10 x i32]* %op1, i32 0, i32 0
    if (paramFirst)
        fprintf(yyout, "  %s = getelementptr inbounds %s, %s %s, i32 %s\n",//inbounds为越界检查
                dst->toStr().c_str(),
                arrType.substr(0, arrType.size() - 1).c_str(), 
                arrType.c_str(),
                arr->toStr().c_str(), idx->toStr().c_str());
    else
        fprintf(yyout, "  %s = getelementptr inbounds %s, %s %s, i32 0, i32 %s\n",
                dst->toStr().c_str(),
                arrType.substr(0, arrType.size() - 1).c_str(),
                arrType.c_str(),
                arr->toStr().c_str(), idx->toStr().c_str());
}

GepInstruction::~GepInstruction() {
    operands[0]->setDef(nullptr);
    if (operands[0]->usersNum() == 0)
        delete operands[0];
    operands[1]->removeUse(this);
    operands[2]->removeUse(this);
}

void ExtensionInstruction::genMachineCode(AsmBuilder* builder) 
{
    auto cur_block = builder->getBlock();
    auto dst = genMachineOperand(operands[0]);
    auto src = genMachineOperand(operands[1]);
    //mov实现扩展
    auto cur_inst = new MovMInstruction(cur_block, MovMInstruction::MOV, dst, src);
    cur_block->InsertInst(cur_inst);
}

void GepInstruction::genInit(AsmBuilder* builder)
{
    //如果是最后一个gep
    if(last)
    {
        auto cur_block = builder->getBlock();
        auto dst = genMachineOperand(operands[0]);
        auto base = genMachineOperand(init);
        //在生成下一个gep之前需要+4以使得dst指向新一维度的首个元素地址
        auto cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::ADD, dst, base, MachineOperand::newImm(4));
        cur_block->InsertInst(cur_inst);
    }
}

void GepInstruction::insertImm(AsmBuilder* builder, MachineOperand* &idx)
{
    //索引一定是立即数
    if (!idx->isImm()) 
    {
        return;
    }
    auto idx1 = MachineOperand::newVReg();
    auto cur_block = builder->getBlock();
    MachineInstruction* cur_inst = nullptr;
    if (idx->getVal() < 255) //合法立即数则直接mov即可。
    {
        cur_inst = new MovMInstruction(cur_block, MovMInstruction::MOV, idx1, idx);
    } 
    else //非合法立即数利用ldr伪指令
    {
        cur_inst = new LoadMInstruction(cur_block, idx1, idx);
    }
    idx = new MachineOperand(*idx1);
    cur_block->InsertInst(cur_inst);
}

void GepInstruction::calcSize(AsmBuilder* builder, int& size)
{
    //如果是参数
    if (paramFirst) 
    {
        size = ((PointerType*)(operands[1]->getType()))->getType()->getSize() / 8;
        return;
    }
    ArrayType* type = (ArrayType*)(((PointerType*)(operands[1]->getType()))->getType());
    size = type->getElementType()->getSize() / 8;
 
}

//记录该元素的偏移量
void GepInstruction::insertMovLoad(AsmBuilder* builder, int v, MachineOperand*& vreg)
{
    auto imm = MachineOperand::newImm(v);//偏移量
    vreg = MachineOperand::newVReg();
    MachineInstruction* cur_inst = nullptr;
    auto cur_block = builder->getBlock();
    if (v > -255 && v < 255) //偏移量合法则使用mov
    {
        cur_inst = new MovMInstruction(cur_block, MovMInstruction::MOV, vreg, imm);
    } 
    else 
    {
        cur_inst = new LoadMInstruction(cur_block, vreg, imm);
    }
    cur_block->InsertInst(cur_inst);
}

void GepInstruction::handleFirst(AsmBuilder* builder, MachineOperand*& base)
{
    if (!first) 
    {
        return;
    }
    //如果是第一个元素
    auto cur_block = builder->getBlock();
    MachineInstruction* cur_inst;
    base = MachineOperand::newVReg();
    //如果arr是全局变量
    if (operands[1]->getEntry()->isVariable() && ((IdentifierSymbolEntry*)(operands[1]->getEntry())) ->isGlobal()) 
    {
        auto src = genMachineOperand(operands[1]);
        //把这个一维数组的地址放进base中
        cur_inst = new LoadMInstruction(cur_block, base, src);
        cur_block->InsertInst(cur_inst);
        return;
    }
    //如果是局部变量或者函数参数
    //获取偏移量
    int offset = ((TemporarySymbolEntry*)(operands[1]->getEntry())) ->getOffset();
    insertMovLoad(builder, offset, base);
}

void GepInstruction::handleParamFirst(AsmBuilder* builder, MachineOperand* base, MachineOperand* off)
{
    auto dst = genMachineOperand(operands[0]);
    auto cur_block = builder->getBlock();
    if (paramFirst || !first) //如果不是函数参数数组中一维数组第一个元素
    {
        auto arr = genMachineOperand(operands[1]);
        insertAdd(builder, dst, arr, off);//根据偏移量计算即可
        return;
    }
    //如果是
    MachineInstruction* cur_inst = nullptr;
    auto addr = MachineOperand::newVReg();
    auto base1 = new MachineOperand(*base);
    
    insertAdd(builder, addr, base1, off);
    addr = new MachineOperand(*addr);
    //全局变量则需要存储结果地址
    if (operands[1]->getEntry()->isVariable() && ((IdentifierSymbolEntry*)(operands[1]->getEntry()))->isGlobal()) 
    {
        cur_inst = new MovMInstruction(cur_block, MovMInstruction::MOV, dst, addr);
        cur_block->InsertInst(cur_inst);
        return;
    }
    auto fp = MachineOperand::newReg(MachineOperand::RegType::FP);
    //下一个数组位置
    insertAdd(builder, dst, fp, addr);
}

void GepInstruction::genMachineCode(AsmBuilder* builder) 
{
    //如果不是一开始的最低维度
    if(init)
    {
        genInit(builder);
        return;
    }
    //如果是在最开始的最低维度，需要对索引的立即数进行合法性调整
    auto cur_block = builder->getBlock();
    MachineInstruction* cur_inst;
    auto idx = genMachineOperand(operands[2]);
    MachineOperand* base = nullptr;//这一维数组的首地址
    int size;//一维数组的大小
    //对索引的立即数进行合法性调整
    insertImm(builder, idx);
    //确定该一维数组大小
    calcSize(builder, size);
    //第一个元素需要特殊处理
    handleFirst(builder, base);
    MachineOperand* size1 = nullptr;
    //不是第一个元素无需处理，直接寻找下一个一维数组
    insertMovLoad(builder, size, size1);
    auto off = MachineOperand::newVReg();
    cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::MUL, off, idx, size1);
    off = new MachineOperand(*off);
    cur_block->InsertInst(cur_inst);

    handleParamFirst(builder, base, off);
}
