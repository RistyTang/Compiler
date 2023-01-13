#include "MachineCode.h"
#include <iostream>
#include "Type.h"
extern FILE* yyout;

int MachineBlock::label = 0;

MachineOperand::MachineOperand(int tp, int val) 
{
    //是立即数则赋值，否则设置寄存器号。
    this->type = tp;
    if (tp == MachineOperand::IMM)
        this->val = val;
    else
        this->reg_no = val;
}

MachineOperand::MachineOperand(std::string label) 
{
    //地址编号
    this->type = MachineOperand::LABEL;
    this->label = label;
}

bool MachineOperand::operator==(const MachineOperand& a) const 
{
    if (this->type != a.type)
        return false;
    if (this->type == IMM)
        return this->val == a.val;
    return this->reg_no == a.reg_no;
}

bool MachineOperand::operator<(const MachineOperand& a) const 
{
    if (this->type == a.type) 
    {
        if (this->type == IMM)
            return this->val < a.val;
        return this->reg_no < a.reg_no;
    }
    return this->type < a.type;

    //？这些代码为什么要存在？
    if (this->type != a.type)
        return false;
    if (this->type == IMM)
        return this->val == a.val;
    return this->reg_no == a.reg_no;
}

void MachineOperand::PrintReg() 
{
    fprintf(yyout,"%s",getRegString().c_str());
}

//获取寄存器编号
std::string MachineOperand::getRegString()
{
    switch (reg_no) 
    {
        case 11:
            return "fp";//栈顶指针，指向一个栈帧的顶部
        case 13:
            return "sp";//栈指针（也称为栈底指针），指向栈当前的位置
        case 14:
            return "lr";//链接寄存器，保存函数返回的地址。
        case 15:
            return "pc";//存储指向下一条命令的地址
        default:
            std::string temp="r" + std::to_string(reg_no);
            return temp;
    }
}

std::string MachineOperand::getOperandString()
{
    std::string temp;
    switch (this->type) 
    {
        case IMM://立即数
            temp="#" + std::to_string(this->val);//immediate num 1 -> print #1;
            break;
        case VREG://虚拟寄存器
            temp="v" + std::to_string(this->reg_no);//register 1 -> print v1;
            break;
        case REG://分配的寄存器
            temp=getRegString();//register 1 -> print r1;
            break;
        case LABEL://地址
            if (this->label.substr(0, 2) == ".L")
            {    
                temp=this->label.c_str();
            }
            else if (this->label.substr(0, 1) == "@")//@putint || @putch
            {    
                temp=this->label.c_str() + 1;
            }
            else//lable addr_a -> print addr_a;
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

void MachineOperand::output() 
{
    /* HINT：print operand
     * Example:
     * immediate num 1 -> print #1;
     * register 1 -> print r1;
     * lable addr_a -> print addr_a; */
   fprintf(yyout,"%s",getOperandString().c_str());
}

MachineOperand* MachineOperand::newReg(RegType regType) 
{
    return new MachineOperand(MachineOperand::REG, regType);
}

MachineOperand* MachineOperand::newVReg()
{
    return new MachineOperand(MachineOperand::VREG, SymbolTable::getLabel());
}


std::string MachineInstruction::getCondString()
{
    switch (cond) 
    {
        case EQ://相等
            return "eq";
        case NE://不等
            return "ne";
        case LT://小于
            return "lt";
        case LE://<=
            return "le";
        case GT://>
            return "gt";
        case GE://>=
            return "ge";
        default:
            break;
    }
    //错误返回为空
    return "";
}

void MachineInstruction::PrintCond() 
{
   fprintf(yyout,"%s",getCondString().c_str());
}

void MachineInstruction::addUseList(std::vector<MachineOperand*> list)
{
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        use_list.emplace_back(*it);
    }
}

//本指令插入到inst之前
void MachineInstruction::insertBefore(MachineInstruction* inst) 
{
    auto& instructions = parent->getInsts();
    auto it = std::find(instructions.begin(), instructions.end(), this);
    instructions.insert(it, inst);
}

//本指令插入到inst之后
void MachineInstruction::insertAfter(MachineInstruction* inst) 
{
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
        case BinaryMInstruction::ADD://add r5, r6, r7       结果在r5
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
        if (this->use_list[0]->isReg() || this->use_list[0]->isVReg())//[]取内容
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
    //TODO 
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
    //str r4, [r6]
    std::string temp;
    temp="\tstr ";
    temp+=this->use_list[0]->getOperandString();
    temp+=", ";
    if (this->use_list[1]->isReg() || this->use_list[1]->isVReg())//是寄存器的话要加上[取值
    {
        temp+="[";
    }
    temp+=this->use_list[1]->getOperandString();
    if (this->use_list.size() > 2)//str r5, [fp, #-8]
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
    this->def_list.push_back(dst);
    dst->setParent(this);
}

std::string BranchMInstruction::getBranchCodeString()
{
    std::string temp;
    switch (op) 
    {
        case B:
            temp="\tb"+getCondString()+" "+this->def_list[0]->getOperandString()+"\n";
            break;
        case BX:
            temp="\tbx"+getCondString()+" "+this->def_list[0]->getOperandString()+"\n";
            break;
        case BL:
            temp="\tbl"+getCondString()+" "+this->def_list[0]->getOperandString()+"\n";
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
    //仿写
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
    if (srcs.size() > 0){
        addUseList(srcs);
    }
    addSrc(src);
    if (src1) {
        addSrc(src1);
    }
}

void StackMInstrcuton::addSrc(MachineOperand* src)
{
    use_list.emplace_back(src);
    src->setParent(this);
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

MachineFunction::MachineFunction(MachineUnit* p, SymbolEntry* sym_ptr) 
{
    this->parent = p;
    this->sym_ptr = sym_ptr;
    this->stack_size = 0;
    //增加对参数个数的判断
    this->paramsNum = ((FunctionType*)(sym_ptr->getType()))->getParamsSe().size();
};

//将保存的寄存器都出栈
void MachineBlock::outputBlockBx()
{
    auto fp = MachineOperand::newReg(MachineOperand::RegType::FP);
    auto lr = MachineOperand::newReg(MachineOperand::RegType::LR);
    auto cur_inst = new StackMInstrcuton(this, StackMInstrcuton::POP, parent->getSavedRegs(), fp, lr);
    cur_inst->output();
}

//store指令输出
void MachineBlock::outputBlockStore(InsIterType it, bool& first, int& offset)
{
    MachineOperand* operand = (*it)->getUse()[0];
    if (operand->isReg() && operand->getReg() == 3) //是寄存器且编号为3
    {
        if (first) //第一次使用
        {
            first = false;
        } 
        else //如果不是的话就要重用r3寄存器传参
        {
            auto fp = MachineOperand::newReg(MachineOperand::RegType::FP);
            auto r3 = new MachineOperand(MachineOperand::REG, 3);
            auto off = new MachineOperand(MachineOperand::IMM, offset);
            offset += 4;
            auto cur_inst = new LoadMInstruction(this, r3, fp, off);
            cur_inst->output();
        }
    }
}

void MachineBlock::outputBlockAdd(InsIterType it)
{
    auto dst = (*it)->getDef()[0];
    auto src1 = (*it)->getUse()[0];
    //抬高栈：dst和src1都是sp寄存器
    if (dst->isReg() && dst->getReg() == 13 && src1->isReg() && src1->getReg() == 13 && (*(it + 1))->isBX()) 
    {
        int size = parent->AllocSpace(0);
        if (size < -255 || size > 255) //非合法立即数
        {
            //用寄存器r1存
            auto r1 = new MachineOperand(MachineOperand::REG, 1);
            auto off = new MachineOperand(MachineOperand::IMM, size);
            (new LoadMInstruction(nullptr, r1, off))->output();
            (*it)->getUse()[1]->setReg(1);
        } else
            (*it)->getUse()[1]->setVal(size);
    }
}

void MachineBlock::outputInst(InsIterType it, int& offset, int& count, bool& first, int num)
{
    if ((*it)->isBX()) //是分支指令
    {
        outputBlockBx();
    }
    if (num > 4 && (*it)->isStore()) //如果是存储指令且函数参数>4，r0~r3不够用
    {
        outputBlockStore(it, first, offset);
    }
    if ((*it)->isAdd()) 
    {
        outputBlockAdd(it);
    }
    (*it)->output();
    ++count;
    if (count % 500 == 0) 
    {
        //	b .F0
        std::string temp="\tb .B"+std::to_string(label)+"\n";
        //用于声明一个文字池，在使用LDR伪指令的时候，要在适当的地址加入LTORG声明文字池，
        //这样就会把要加载的数据保存在文字池内，再用ARM的加载指令读出数据
        temp+=".LTORG\n";
        fprintf(yyout,"%s",temp.c_str());
        parent->getParent()->printGlobal();
        //
        temp=".B"+std::to_string(label++)+":\n";
        fprintf(yyout,"%s",temp.c_str());
    }
}

void MachineBlock::output() 
{
    bool first = true;//是第一次使用
    int offset = (parent->getSavedRegs().size() + 2) * 4;
    int num = parent->getParamsNum();
    int count = 0;
    //输出块号.L146:
    fprintf(yyout, ".L%d:\n", this->no);
    //输出指令
    for (auto it = inst_list.begin(); it != inst_list.end(); it++) 
    {
        outputInst(it, offset, count, first, num);
    }
}

void MachineFunction::output() 
{
    //函数名	.global Dijkstra
    fprintf(yyout, "\t.global %s\n", this->sym_ptr->toStr().c_str() + 1);
    //类型.type Dijkstra , %function
    fprintf(yyout, "\t.type %s , %%function\n", this->sym_ptr->toStr().c_str() + 1);
    //函数具体翻译Dijkstra:
    fprintf(yyout, "%s:\n", this->sym_ptr->toStr().c_str() + 1);
    // TODO
    /* Hint:
     *  1. Save fp保存栈顶指针
     *  2. fp = sp抬高栈
     *  3. Save callee saved register保存寄存器
     *  4. Allocate stack space for local variable 分配空间
     * */

    // Traverse all the block in block_list to print assembly code.
    auto fp = MachineOperand::newReg(MachineOperand::RegType::FP);
    auto sp = MachineOperand::newReg(MachineOperand::RegType::SP);
    auto lr = MachineOperand::newReg(MachineOperand::RegType::LR);
    //1. Save fp保存栈顶指针
    (new StackMInstrcuton(nullptr, StackMInstrcuton::PUSH, getSavedRegs(), fp, lr))->output();

    //2. fp = sp抬高栈
    (new MovMInstruction(nullptr, MovMInstruction::MOV, fp, sp))->output();

    //3. Save callee saved register保存寄存器
    //获取当前偏移量
    int off = AllocSpace(0);
    auto size = new MachineOperand(MachineOperand::IMM, off);//operand为立即数off
    //如果是非法立即数，先存入寄存器
    if (off < -255 || off > 255) 
    {
        //设置为4号寄存器
        auto r4 = new MachineOperand(MachineOperand::REG, 4);
        //nullptr:具体在哪个块未定，存到寄存器r4
        (new LoadMInstruction(nullptr, r4, size))->output();
        //sp=sp-size抬高栈
        (new BinaryMInstruction(nullptr, BinaryMInstruction::SUB, sp, sp, r4))->output();
    } 
    else 
    {
        (new BinaryMInstruction(nullptr, BinaryMInstruction::SUB, sp, sp, size)) ->output();
    }
    long long count = 0;
    std::string temp;
    for (auto iter : block_list) 
    {
        iter->output();
        count += iter->getSize();
        if(count <= 160)
        {
            continue;
        }
        //	b .F0
        temp = "\tb .F"+std::to_string(parent->getN())+"\n";
        //.LTORG
        temp+=".LTORG\n";
        fprintf(yyout,"%s",temp.c_str());
        //全局常变量地址
        parent->printGlobal();
        //.F0:
        fprintf(yyout, ".F%d:\n", parent->getN()-1);
        count = 0;
    }
    fprintf(yyout, "\n");
}

//获取寄存器
std::vector<MachineOperand*> MachineFunction::getSavedRegs() 
{
    std::vector<MachineOperand*> regs;
    for (auto it = saved_regs.begin(); it != saved_regs.end(); it++) 
    {
        auto reg = new MachineOperand(MachineOperand::REG, *it);
        regs.push_back(reg);
    }
    return regs;
}

//打印ID表项
void MachineUnit::printIDSymbleEntry(IdentifierSymbolEntry* se)
{
    //	.global TAPE_LEN
    std::string temp="\t.global "+se->toStr()+"\n";
    //	.align 4
    temp+="\t.align 4\n";
    //	.size TAPE_LEN, 4
    temp+="\t.size ";
    temp+=se->toStr();
    temp+=", ";
    temp+=std::to_string(se->getType()->getSize() / 8);
    temp+="\n";
    fprintf(yyout,"%s",temp.c_str());
    //TAPE_LEN:
    temp=se->toStr()+":\n";
    fprintf(yyout,"%s",temp.c_str());
    //不是数组直接打印
    if (!se->getType()->isArray()) 
    {
        temp="\t.word "+std::to_string(se->getValue())+"\n";
        fprintf(yyout,"%s",temp.c_str());
    } 
    else //是数组的话依次打印
    {
        int n = se->getType()->getSize() / 32;
        int* p = se->getArrayValue();
        for (int i = 0; i < n; i++) 
        {
            temp="\t.word "+std::to_string(p[i])+"\n";
            fprintf(yyout,"%s",temp.c_str());
        }
    }
}

//常量数组声明
void MachineUnit::printConstIndices(std::vector<int> constIdx)
{
    //.section 来定义一个段，每个段以段名开始，以下一段名或者文件结 尾结束
    //.rodata用于维护只读数据，比如：常量字符串、带 const 修饰的全局变量和静态变量等
    fprintf(yyout,"\t.section .rodata\n");
    for (auto i : constIdx) 
    {
        IdentifierSymbolEntry* se = (IdentifierSymbolEntry*)global_list[i];
        printIDSymbleEntry(se);
    }
}

void MachineUnit::printZeroIndices(std::vector<int> zeroIdx)
{
    for (auto i : zeroIdx) 
    {
        IdentifierSymbolEntry* se = (IdentifierSymbolEntry*)global_list[i];
        if (se->getType()->isArray()) 
        {
            fprintf(yyout,"\t.comm %s, %d, 4\n", se->toStr().c_str(), se->getType()->getSize() / 8);
        }
    }
}

void MachineUnit::PrintGlobalDecl() 
{
    // TODO:
    // You need to print global variable/const declarition code;
    std::vector<int> constIdx;
    std::vector<int> zeroIdx;
    //先打印全局变量
    if (!global_list.empty())
    {
        fprintf(yyout, "\t.data\n");
    }
    for (long unsigned int i = 0; i < global_list.size(); i++) 
    {
        IdentifierSymbolEntry* se = (IdentifierSymbolEntry*)global_list[i];
        if (se->getConst()) 
        {
            constIdx.emplace_back(i);
            continue;
        } 
        else if (se->isAllZero()) 
        {
            zeroIdx.emplace_back(i);
            continue;
        } 
       printIDSymbleEntry(se);
    }
    //数组
    if (!constIdx.empty()) 
    {
       printConstIndices(constIdx);
    }
    if (!zeroIdx.empty()) 
    {
        printZeroIndices(zeroIdx);
    }
}

void MachineUnit::output() 
{
    // TODO
    /* Hint:
     * 1. You need to print global variable/const declarition code;
     * 2. Traverse all the function in func_list to print assembly code;
     * 3. Don't forget print bridge label at the end of assembly code!! */
    std::string temp;
    //.arch armv8-a
    temp="\t.arch armv8-a\n";

    //	.arch_extension crc
    temp+="\t.arch_extension crc\n";

    //	.arm
    temp+="\t.arm\n";
    fprintf(yyout, "%s",temp.c_str());

    //先打印全局常变量声明
    PrintGlobalDecl();

    //代码段
    temp="\t.text\n";
    fprintf(yyout, "%s",temp.c_str());
    //输出指令
    for (auto iter : func_list)
        iter->output();
    printGlobal();
}

void MachineUnit::insertGlobal(SymbolEntry* se) 
{
    global_list.push_back(se);
}

void MachineUnit::printGlobal()
{
    std::string temp;
    for (auto s : global_list) //输出全局的常变量地址
    {
        IdentifierSymbolEntry* se = (IdentifierSymbolEntry*)s;
        //addr_n0:
        temp="addr_"+se->toStr()+std::to_string(n)+":\n";
        //	.word n
        temp+="\t.word ";
        temp+=se->toStr();
        temp+="\n";
        fprintf(yyout, "%s",temp.c_str());
    }
    n++;
}