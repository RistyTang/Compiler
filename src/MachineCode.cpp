#include "MachineCode.h"
#include <iostream>
#include "Type.h"
extern FILE* yyout;

int MachineBlock::label = 0;

MachineOperand::MachineOperand(int tp, int val) {
    this->type = tp;
    if (tp == MachineOperand::IMM)
        this->val = val;
    else
        this->reg_no = val;
}

MachineOperand::MachineOperand(std::string label) {
    this->type = MachineOperand::LABEL;
    this->label = label;
}

bool MachineOperand::operator==(const MachineOperand& a) const {
    if (this->type != a.type)
        return false;
    if (this->type == IMM)
        return this->val == a.val;
    return this->reg_no == a.reg_no;
}

bool MachineOperand::operator<(const MachineOperand& a) const {
    if (this->type == a.type) {
        if (this->type == IMM)
            return this->val < a.val;
        return this->reg_no < a.reg_no;
    }
    return this->type < a.type;

    if (this->type != a.type)
        return false;
    if (this->type == IMM)
        return this->val == a.val;
    return this->reg_no == a.reg_no;
}

void MachineOperand::PrintReg() {
    fprintf(yyout,"%s",getRegString().c_str());
}

//获取编号
std::string MachineOperand::getRegString()
{
    switch (reg_no) {
        case 11:
            return "fp";
        case 13:
            return "sp";
        case 14:
            return "lr";
        case 15:
            return "pc";
        default:
            std::string temp="r" + std::to_string(reg_no);
            return temp;
    }
}

std::string MachineOperand::getOperandString()
{
    std::string temp;
    switch (this->type) {
        case IMM:
            temp="#" + std::to_string(this->val);
            break;
        case VREG:
            temp="v" + std::to_string(this->reg_no);
            break;
        case REG:
            //PrintReg();
            temp=getRegString();
            break;
        case LABEL:
            if (this->label.substr(0, 2) == ".L")
            {    
                temp=this->label.c_str();
            }
            else if (this->label.substr(0, 1) == "@")
            {    
                temp=this->label.c_str() + 1;
            }
            else
            {
                temp="addr_"+this->label+std::to_string(parent->getParent()->getParent()->getParent()->getN());
            }
            break;
        default:
            temp="";
            break;
    }
    return temp;
}

void MachineOperand::output() {
    /* HINT：print operand
     * Example:
     * immediate num 1 -> print #1;
     * register 1 -> print r1;
     * lable addr_a -> print addr_a; */
   fprintf(yyout,"%s",getOperandString().c_str());
}

void MachineInstruction::PrintCond() 
{
   fprintf(yyout,"%s",getCondString().c_str());
}

std::string MachineInstruction::getCondString()
{
    switch (cond) 
    {
        case EQ:
            return "eq";
        case NE:
            return "ne";
        case LT:
            return "lt";
        case LE:
            return "le";
        case GT:
            return "gt";
        case GE:
            return "ge";
        default:
            break;
    }
    //错误返回为空
    return "";
}

void MachineInstruction::insertBefore(MachineInstruction* inst) {
    auto& instructions = parent->getInsts();
    auto it = std::find(instructions.begin(), instructions.end(), this);
    instructions.insert(it, inst);
}

void MachineInstruction::insertAfter(MachineInstruction* inst) {
    auto& instructions = parent->getInsts();
    auto it = std::find(instructions.begin(), instructions.end(), this);
    instructions.insert(++it, inst);
}

BinaryMInstruction::BinaryMInstruction(MachineBlock* p, int op, MachineOperand* dst, MachineOperand* src1, MachineOperand* src2, int cond) 
{
    this->parent = p;
    this->type = MachineInstruction::BINARY;
    this->op = op;
    this->cond = cond;
    this->def_list.push_back(dst);
    this->use_list.push_back(src1);
    this->use_list.push_back(src2);
    dst->setParent(this);
    src1->setParent(this);
    src2->setParent(this);
}

std::string BinaryMInstruction::getCodeString()
{
    std::string temp="";
    switch (this->op) 
    {
        case BinaryMInstruction::ADD:
            temp="\tadd "+getCondString()+this->def_list[0]->getOperandString()+", "+this->use_list[0]->getOperandString() + ", " + this->use_list[1]->getOperandString() + "\n";
            break;
        case BinaryMInstruction::SUB:
            temp="\tsub "+getCondString()+this->def_list[0]->getOperandString()+", "+this->use_list[0]->getOperandString() + ", " + this->use_list[1]->getOperandString() + "\n";
            break;
        case BinaryMInstruction::AND:
            temp="\tand "+getCondString()+this->def_list[0]->getOperandString()+", "+this->use_list[0]->getOperandString() + ", " + this->use_list[1]->getOperandString() + "\n";
            break;
        case BinaryMInstruction::OR:
            temp="\torr "+getCondString()+this->def_list[0]->getOperandString()+", "+this->use_list[0]->getOperandString() + ", " + this->use_list[1]->getOperandString() + "\n";
            break;
        case BinaryMInstruction::MUL:
            temp="\tmul "+getCondString()+this->def_list[0]->getOperandString()+", "+this->use_list[0]->getOperandString() + ", " + this->use_list[1]->getOperandString() + "\n";
            break;
        case BinaryMInstruction::DIV:
            temp="\tsdiv "+getCondString()+this->def_list[0]->getOperandString()+", "+this->use_list[0]->getOperandString() + ", " + this->use_list[1]->getOperandString() + "\n";
            break;
        default:
            break;
    }
    return temp;
}

void BinaryMInstruction::output() 
{
    fprintf(yyout,"%s",getCodeString().c_str());
}

LoadMInstruction::LoadMInstruction(MachineBlock* p, MachineOperand* dst, MachineOperand* src1, MachineOperand* src2, int cond) 
{
    this->parent = p;
    this->type = MachineInstruction::LOAD;
    this->op = -1;
    this->cond = cond;
    this->def_list.push_back(dst);
    this->use_list.push_back(src1);
    if (src2)
        this->use_list.push_back(src2);
    dst->setParent(this);
    src1->setParent(this);
    if (src2)
        src2->setParent(this);
}

std::string LoadMInstruction::getLoadCodeString() 
{
    std::string temp="\tldr "+this->def_list[0]->getOperandString()+", ";
    //如果是立即数的话
    if (this->use_list[0]->isImm()) 
    {
        temp+="=";
        temp+=std::to_string(this->use_list[0]->getVal());
        temp+="\n";
        return temp;
    }
    else//寄存器
    {
        if (this->use_list[0]->isReg() || this->use_list[0]->isVReg())
        {
            temp+="[";
        }
        temp+=this->use_list[0]->getOperandString();
        if (this->use_list.size() > 1) 
        {
            temp+=", ";
            temp+=this->use_list[1]->getOperandString();
        }
        if (this->use_list[0]->isReg() || this->use_list[0]->isVReg())
        {    
            temp+="]";
        }
        temp+="\n";
        return temp;
    }
}

void LoadMInstruction::output() 
{
   fprintf(yyout,"%s",getLoadCodeString().c_str());
}

StoreMInstruction::StoreMInstruction(MachineBlock* p, MachineOperand* src1, MachineOperand* src2, MachineOperand* src3, int cond) 
{
    this->parent = p;
    this->type = MachineInstruction::STORE;
    this->op = -1;
    this->cond = cond;
    this->use_list.push_back(src1);
    this->use_list.push_back(src2);
    if (src3)
        this->use_list.push_back(src3);
    src1->setParent(this);
    src2->setParent(this);
    if (src3)
        src3->setParent(this);
}

std::string StoreMInstruction::getStoreCodeString()
{
    std::string temp;
    temp="\tstr ";
    temp+=this->use_list[0]->getOperandString();
    temp+=", ";
    if (this->use_list[1]->isReg() || this->use_list[1]->isVReg())
    {
        temp+="[";
    }
    temp+=this->use_list[1]->getOperandString();
    if (this->use_list.size() > 2)
    {
        temp+=", ";
        temp+=this->use_list[2]->getOperandString();
    }
    if (this->use_list[1]->isReg() || this->use_list[1]->isVReg())
    {
        temp+="]";
    }
    temp+="\n";
    return temp;
}

void StoreMInstruction::output() 
{
   fprintf(yyout,"%s",getStoreCodeString().c_str());
}

MovMInstruction::MovMInstruction(MachineBlock* p, int op, MachineOperand* dst, MachineOperand* src, int cond) 
{
    this->parent = p;
    this->type = MachineInstruction::MOV;
    this->op = op;
    this->cond = cond;
    this->def_list.push_back(dst);
    this->use_list.push_back(src);
    dst->setParent(this);
    src->setParent(this);
}

std::string MovMInstruction::getMovCodeString()
{
    std::string temp;
    temp="\tmov";
    temp+=getCondString();
    temp+=" ";
    temp+=this->def_list[0]->getOperandString();
    temp+=", ";
    temp+=this->use_list[0]->getOperandString();
    temp+="\n";
    return temp;
}

void MovMInstruction::output() 
{
   fprintf(yyout,"%s",getMovCodeString().c_str());
}

BranchMInstruction::BranchMInstruction(MachineBlock* p, int op, MachineOperand* dst, int cond) 
{
    this->parent = p;
    this->type = MachineInstruction::BRANCH;
    this->op = op;
    this->cond = cond;
    this->use_list.push_back(dst);
    dst->setParent(this);
}

std::string BranchMInstruction::getBranchCodeString()
{
    std::string temp;
    switch (op) 
    {
        case B:
            temp="\tb"+getCondString()+" "+this->use_list[0]->getOperandString()+"\n";
            break;
        case BX:
            temp="\tbx"+getCondString()+" "+this->use_list[0]->getOperandString()+"\n";
            break;
        case BL:
            temp="\tbl"+getCondString()+" "+this->use_list[0]->getOperandString()+"\n";
            break;
    }
    return temp;
}

void BranchMInstruction::output() 
{
   fprintf(yyout,"%s",getBranchCodeString().c_str());
}

CmpMInstruction::CmpMInstruction(MachineBlock* p, MachineOperand* src1, MachineOperand* src2, int cond) 
{
    this->parent = p;
    this->type = MachineInstruction::CMP;
    this->op = -1;
    this->cond = cond;
    p->setCmpCond(cond);
    this->use_list.push_back(src1);
    this->use_list.push_back(src2);
    src1->setParent(this);
    src2->setParent(this);
}

std::string CmpMInstruction::getCmpCodeString()
{
    std::string temp;
    temp="\tcmp "+this->use_list[0]->getOperandString()+", "+this->use_list[1]->getOperandString()+"\n";
    return temp;
}

void CmpMInstruction::output() 
{
   fprintf(yyout,"%s",getCmpCodeString().c_str());
}

StackMInstrcuton::StackMInstrcuton(MachineBlock* p, int op, std::vector<MachineOperand*> srcs, MachineOperand* src, MachineOperand* src1, int cond) 
{
    this->parent = p;
    this->type = MachineInstruction::STACK;
    this->op = op;
    this->cond = cond;
    if (srcs.size())
        for (auto it = srcs.begin(); it != srcs.end(); it++)
            this->use_list.push_back(*it);
    this->use_list.push_back(src);
    src->setParent(this);
    if (src1) {
        this->use_list.push_back(src1);
        src1->setParent(this);
    }
}

std::string StackMInstrcuton::getStackCodeString()
{
    std::string temp;
    if(op==PUSH)
    {
        temp="\tpush ";
    }
    else if( op == POP )
    {
        temp="\tpop ";
    }
    temp+="{";
    temp+=this->use_list[0]->getOperandString();
    for (long unsigned int i = 1; i < use_list.size(); i++) 
    {
        temp+=", ";
        temp+=this->use_list[i]->getOperandString();
    }
    temp+="}\n";
    return temp;
}

void StackMInstrcuton::output() 
{
   fprintf(yyout,"%s",getStackCodeString().c_str());
}

MachineFunction::MachineFunction(MachineUnit* p, SymbolEntry* sym_ptr) {
    this->parent = p;
    this->sym_ptr = sym_ptr;
    this->stack_size = 0;
    this->paramsNum =
        ((FunctionType*)(sym_ptr->getType()))->getParamsSe().size();
};

void MachineBlock::output() 
{
    bool first = true;
    int offset = (parent->getSavedRegs().size() + 2) * 4;
    int num = parent->getParamsNum();
    int count = 0;
    if (!inst_list.empty()) {
        fprintf(yyout, ".L%d:\n", this->no);
        for (auto it = inst_list.begin(); it != inst_list.end(); it++) {
            if ((*it)->isBX()) {
                auto fp = new MachineOperand(MachineOperand::REG, 11);
                auto lr = new MachineOperand(MachineOperand::REG, 14);
                auto cur_inst =
                    new StackMInstrcuton(this, StackMInstrcuton::POP,
                                         parent->getSavedRegs(), fp, lr);
                cur_inst->output();
            }
            if (num > 4 && (*it)->isStore()) {
                MachineOperand* operand = (*it)->getUse()[0];
                if (operand->isReg() && operand->getReg() == 3) {
                    if (first) {
                        first = false;
                    } else {
                        auto fp = new MachineOperand(MachineOperand::REG, 11);
                        auto r3 = new MachineOperand(MachineOperand::REG, 3);
                        auto off =
                            new MachineOperand(MachineOperand::IMM, offset);
                        offset += 4;
                        auto cur_inst = new LoadMInstruction(this, r3, fp, off);
                        cur_inst->output();
                    }
                }
            }
            if ((*it)->isAdd()) {
                auto dst = (*it)->getDef()[0];
                auto src1 = (*it)->getUse()[0];
                if (dst->isReg() && dst->getReg() == 13 && src1->isReg() &&
                    src1->getReg() == 13 && (*(it + 1))->isBX()) {
                    int size = parent->AllocSpace(0);
                    if (size < -255 || size > 255) {
                        auto r1 = new MachineOperand(MachineOperand::REG, 1);
                        auto off =
                            new MachineOperand(MachineOperand::IMM, size);
                        (new LoadMInstruction(nullptr, r1, off))->output();
                        (*it)->getUse()[1]->setReg(1);
                    } else
                        (*it)->getUse()[1]->setVal(size);
                }
            }
            (*it)->output();
            count++;
            if (count % 500 == 0) {
                fprintf(yyout, "\tb .B%d\n", label);
                fprintf(yyout, ".LTORG\n");
                parent->getParent()->printGlobal();
                fprintf(yyout, ".B%d:\n", label++);
            }
        }
    }
}

void MachineFunction::output() {
    fprintf(yyout, "\t.global %s\n", this->sym_ptr->toStr().c_str() + 1);
    fprintf(yyout, "\t.type %s , %%function\n",
            this->sym_ptr->toStr().c_str() + 1);
    fprintf(yyout, "%s:\n", this->sym_ptr->toStr().c_str() + 1);
    // TODO
    /* Hint:
     *  1. Save fp
     *  2. fp = sp
     *  3. Save callee saved register
     *  4. Allocate stack space for local variable */

    // Traverse all the block in block_list to print assembly code.
    auto fp = new MachineOperand(MachineOperand::REG, 11);
    auto sp = new MachineOperand(MachineOperand::REG, 13);
    auto lr = new MachineOperand(MachineOperand::REG, 14);
    (new StackMInstrcuton(nullptr, StackMInstrcuton::PUSH, getSavedRegs(), fp,
                          lr))
        ->output();
    (new MovMInstruction(nullptr, MovMInstruction::MOV, fp, sp))->output();
    int off = AllocSpace(0);
    auto size = new MachineOperand(MachineOperand::IMM, off);
    if (off < -255 || off > 255) {
        auto r4 = new MachineOperand(MachineOperand::REG, 4);
        (new LoadMInstruction(nullptr, r4, size))->output();
        (new BinaryMInstruction(nullptr, BinaryMInstruction::SUB, sp, sp, r4))
            ->output();
    } else {
        (new BinaryMInstruction(nullptr, BinaryMInstruction::SUB, sp, sp, size))
            ->output();
    }
    int count = 0;
    for (auto iter : block_list) {
        iter->output();
        count += iter->getSize();
        if(count > 160){
            fprintf(yyout, "\tb .F%d\n", parent->getN());
            fprintf(yyout, ".LTORG\n");
            parent->printGlobal();
            fprintf(yyout, ".F%d:\n", parent->getN()-1);
            count = 0;
        }
    }
    fprintf(yyout, "\n");
}

std::vector<MachineOperand*> MachineFunction::getSavedRegs() {
    std::vector<MachineOperand*> regs;
    for (auto it = saved_regs.begin(); it != saved_regs.end(); it++) {
        auto reg = new MachineOperand(MachineOperand::REG, *it);
        regs.push_back(reg);
    }
    return regs;
}

void MachineUnit::PrintGlobalDecl() 
{
    std::vector<int> constIdx;
    std::vector<int> zeroIdx;
    if (!global_list.empty())
    {
        fprintf(yyout, "\t.data\n");
    }
    for (long unsigned int i = 0; i < global_list.size(); i++) {
        IdentifierSymbolEntry* se = (IdentifierSymbolEntry*)global_list[i];
        if (se->getConst()) 
        {
            constIdx.push_back(i);
        } 
        else if (se->isAllZero()) 
        {
            zeroIdx.push_back(i);
        } 
        else 
        {
            //.global main
            std::string temp="\t.global "+se->toStr()+"\n";
            //.align 4
            temp+="\t.align 4\n";
            //.size n, 4
            temp+="\t.size ";
            temp+=se->toStr();
            temp+=", ";
            temp+=std::to_string(se->getType()->getSize() / 8);
            temp+="\n";
            //func:
            temp+=se->toStr();
            temp+=":\n";
            fprintf(yyout,"%s",temp.c_str());
            if (!se->getType()->isArray()) //不是数组直接打印
            {
                //  .word 0
                fprintf(yyout, "\t.word %d\n", se->getValue());
            } 
            else 
            {
                int n = se->getType()->getSize() / 32;
                int* p = se->getArrayValue();
                for (int i = 0; i < n; i++) 
                {
                    fprintf(yyout, "\t.word %d\n", p[i]);
                }
            }
        }
    }
    if (!constIdx.empty()) {
        fprintf(yyout, "\t.section .rodata\n");
        for (auto i : constIdx) {
            IdentifierSymbolEntry* se = (IdentifierSymbolEntry*)global_list[i];
            fprintf(yyout, "\t.global %s\n", se->toStr().c_str());
            fprintf(yyout, "\t.align 4\n");
            fprintf(yyout, "\t.size %s, %d\n", se->toStr().c_str(),
                    se->getType()->getSize() / 8);
            fprintf(yyout, "%s:\n", se->toStr().c_str());
            if (!se->getType()->isArray()) {
                fprintf(yyout, "\t.word %d\n", se->getValue());
            } else {
                int n = se->getType()->getSize() / 32;
                int* p = se->getArrayValue();
                for (int i = 0; i < n; i++) {
                    fprintf(yyout, "\t.word %d\n", p[i]);
                }
            }
        }
    }
    if (!zeroIdx.empty()) {
        for (auto i : zeroIdx) {
            IdentifierSymbolEntry* se = (IdentifierSymbolEntry*)global_list[i];
            if (se->getType()->isArray()) {
                fprintf(yyout, "\t.comm %s, %d, 4\n", se->toStr().c_str(),
                        se->getType()->getSize() / 8);
            }
        }
    }
}

void MachineUnit::output() {
    // TODO
    /* Hint:
     * 1. You need to print global variable/const declarition code;
     * 2. Traverse all the function in func_list to print assembly code;
     * 3. Don't forget print bridge label at the end of assembly code!! */
    fprintf(yyout, "\t.arch armv8-a\n");
    fprintf(yyout, "\t.arch_extension crc\n");
    fprintf(yyout, "\t.arm\n");
    PrintGlobalDecl();
    fprintf(yyout, "\t.text\n");
    for (auto iter : func_list)
        iter->output();
    printGlobal();
}

void MachineUnit::insertGlobal(SymbolEntry* se) {
    global_list.push_back(se);
}

void MachineUnit::printGlobal()
{
    for (auto s : global_list) {
        IdentifierSymbolEntry* se = (IdentifierSymbolEntry*)s;
        fprintf(yyout, "addr_%s%d:\n", se->toStr().c_str(), n);
        fprintf(yyout, "\t.word %s\n", se->toStr().c_str());
    }
    n++;
}