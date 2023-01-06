#include "LinearScan.h"
#include <algorithm>
#include <iostream>
#include "LiveVariableAnalysis.h"
#include "MachineCode.h"

LinearScan::LinearScan(MachineUnit* unit) 
{
    this->unit = unit;
    //r0~r3传参数
    for (int i = 4; i < 11; i++)
        regs.push_back(i);
}

void LinearScan::allocateRegisters() 
{
    for (auto& f : unit->getFuncs()) 
    {
        func = f;
        bool success;
        success = false;
        while (!success)  // repeat until all vregs can be mapped
        {
            computeLiveIntervals();
            success = linearScanRegisterAllocation();
            if (success)  // all vregs can be mapped to real regs
                modifyCode();
            else  // spill vregs that can't be mapped to real regs
                genSpillCode();//有临时变量被溢出到栈内
        }
    }
}

void LinearScan::makeDuChains() 
{
    LiveVariableAnalysis lva;
    lva.pass(func);
    du_chains.clear();
    int i = 0;
    std::map<MachineOperand, std::set<MachineOperand*>> liveVar;
    for (auto& bb : func->getBlocks()) {
        liveVar.clear();
        for (auto& t : bb->getLiveOut())
            liveVar[*t].insert(t);
        int no;
        no = i = bb->getInsts().size() + i;
        for (auto inst = bb->getInsts().rbegin(); inst != bb->getInsts().rend();
             inst++) {
            (*inst)->setNo(no--);
            for (auto& def : (*inst)->getDef()) {
                if (def->isVReg()) {
                    auto& uses = liveVar[*def];
                    du_chains[def].insert(uses.begin(), uses.end());
                    auto& kill = lva.getAllUses()[*def];
                    std::set<MachineOperand*> res;
                    set_difference(uses.begin(), uses.end(), kill.begin(),
                                   kill.end(), inserter(res, res.end()));
                    liveVar[*def] = res;
                }
            }
            for (auto& use : (*inst)->getUse()) {
                if (use->isVReg())
                    liveVar[*use].insert(use);
            }
        }
    }
}

void LinearScan::computeLiveIntervals() 
{
    makeDuChains();
    intervals.clear();
    for (auto& du_chain : du_chains) {
        int t = -1;
        for (auto& use : du_chain.second)
            t = std::max(t, use->getParent()->getNo());
        Interval* interval = new Interval({du_chain.first->getParent()->getNo(),
                                           t,
                                           false,
                                           0,
                                           0,
                                           {du_chain.first},
                                           du_chain.second});
        intervals.push_back(interval);
    }
    bool change;
    change = true;
    while (change) {
        change = false;
        std::vector<Interval*> t(intervals.begin(), intervals.end());
        for (size_t i = 0; i < t.size(); i++)
            for (size_t j = i + 1; j < t.size(); j++) {
                Interval* w1 = t[i];
                Interval* w2 = t[j];
                if (**w1->defs.begin() == **w2->defs.begin()) {
                    std::set<MachineOperand*> temp;
                    set_intersection(w1->uses.begin(), w1->uses.end(),
                                     w2->uses.begin(), w2->uses.end(),
                                     inserter(temp, temp.end()));
                    if (!temp.empty()) {
                        change = true;
                        w1->defs.insert(w2->defs.begin(), w2->defs.end());
                        w1->uses.insert(w2->uses.begin(), w2->uses.end());
                        w1->start = std::min(w1->start, w2->start);
                        w1->end = std::max(w1->end, w2->end);
                        auto it =
                            std::find(intervals.begin(), intervals.end(), w2);
                        if (it != intervals.end())
                            intervals.erase(it);
                    }
                }
            }
    }
    sort(intervals.begin(), intervals.end(), compareStart);
}

void LinearScan::InitRegs()
{
    regs.clear();
    for (int i = 4; i < 11; i++){
        regs.emplace_back(i);
    }
}

bool LinearScan::PopReg(int& res)
{
    if (regs.empty()) {
        return false;
    }
    res = *regs.begin();
    regs.erase(regs.begin());
    return true;
}

//线性扫描分配寄存器
bool LinearScan::linearScanRegisterAllocation() 
{
    //TODO
    bool success = true;
    active.clear();
    InitRegs();
    for (auto& i : intervals) 
    {
        //step1
        expireOldIntervals(i);
        //step2 判断 active 列表中 interval 的数目和可用的物理寄存器数目是否相等
        int allocateReg;
        if (PopReg(allocateReg))//分配寄存器
        {
            i->rreg = allocateReg;
            insertActive(i);
        } 
        else 
        {
            spillAtInterval(i);//寄存器溢出操作
            success = false;
        }
    }
    return success;
}

void LinearScan::modifyCode() 
{
    for (auto& interval : intervals) 
    {
        func->addSavedRegs(interval->rreg);
        for (auto def : interval->defs)
            def->setReg(interval->rreg);
        for (auto use : interval->uses)
            use->setReg(interval->rreg);
    }
}

void LinearScan::genIntervalUse(Interval*& interval, MachineOperand* off, MachineOperand* fp, MachineOperand* use)
{
    //获取use指令列表
    auto temp = new MachineOperand(*use);
    //在 USE 指令前插入 LoadMInstruction，将其从栈内加载到目前的虚拟寄存器中
    auto operand = MachineOperand::newVReg();
    auto inst1 = new LoadMInstruction(use->getParent()->getParent(), operand, off);
    use->getParent()->insertBefore(inst1);
    //在操作该临时变量时插入对应的 LoadMInstruction 和 StoreMInstruction
    auto inst = new LoadMInstruction(use->getParent()->getParent(), temp, fp, new MachineOperand(*operand));
    use->getParent()->insertBefore(inst);
}

void LinearScan::genIntervalDef(Interval*& interval, MachineOperand* off, MachineOperand* fp, MachineOperand* def)
{
    //获取def指令列表
    auto temp = new MachineOperand(*def);
    //在 DEF 指令后插入 StoreMInstruction，将其从目前的虚拟寄存器中存到栈内;
    auto operand = MachineOperand::newVReg();
    auto inst1 = new LoadMInstruction(def->getParent()->getParent(), operand, off);
    def->getParent()->insertAfter(inst1);
    //在操作该临时变量时插入对应的 LoadMInstruction 和 StoreMInstruction
    auto inst = new StoreMInstruction(def->getParent()->getParent(), temp, fp, new MachineOperand(*operand));
    inst1->insertAfter(inst);
 
}

void LinearScan::genIntervalCode(Interval*& interval)
{
    if (!interval->spill)
        return;
    // TODO
    /* HINT:
        * The vreg should be spilled to memory.
        * 1. insert ldr inst before the use of vreg
        * 2. insert str inst after the def of vreg
        */
    //为其在栈内分配空间，获取当前在栈内相对 FP 的偏移
    interval->disp = -func->AllocSpace(4);
    auto off = new MachineOperand(MachineOperand::IMM, interval->disp);
    auto fp = MachineOperand::newReg(MachineOperand::RegType::FP);

    //遍历其 USE 指令的列表，在 USE 指令前插入 LoadMInstruction，将其从栈内加载到目前的虚拟寄存器中;
    for (auto use : interval->uses) 
    {
        genIntervalUse(interval, off, fp, use);
    }

    //遍历其 DEF 指令的列表，在 DEF 指令后插入 StoreMInstruction，将其从目前的虚拟寄存器中存到栈内;
    for (auto def : interval->defs) {
        genIntervalDef(interval, off, fp, def);
    }
}

void LinearScan::genSpillCode() 
{
    //active列表中每一个interval进行寄存器分配。
    for (auto& interval : intervals) 
    {
        genIntervalCode(interval);
    }
}

void LinearScan::expireOldIntervals(Interval* interval) 
{
    //TODO
    /*
    遍历 active 列表，看该列表中是否存在结束时间早于 unhandled interval 的 interval（即与当前
    unhandled interval 的活跃区间不冲突），若有，则说明此时为其分配的物理寄存器可以回收，可
    以用于后续的分配，需要将其在 active 列表删除；
    */
    //遍历 active 列表
    auto it = active.begin();
    while (it != active.end()) 
    {
        //结束时间早于 unhandled interval 的 interval
        if ((*it)->end >= interval->start)
            break;
        regs.emplace_back((*it)->rreg);
        //在 active 列表删除；
        it = active.erase(it);
    }
    sort(regs.begin(), regs.end());
}

void LinearScan::insertActive(Interval* elem)
{
    active.emplace_back(elem);
    sort(active.begin(), active.end(), [](Interval* a, Interval* b){return a->end < b->end;});
}

//溢出
void LinearScan::spillAtInterval(Interval* interval) 
{
     //TODO
    auto spill = active.back();
    if (spill->end <= interval->end) //选择的是 unhandled interval 
    {
        interval->spill = true;
    } 
    else 
    {
        spill->spill = true;//置位其spill标志位
        interval->rreg = spill->rreg;//同时将其占用的寄存器分配给 unhandled interval
        insertActive(interval);//插入到 active 列表中
    }
}

bool LinearScan::compareStart(Interval* a, Interval* b) 
{
    return a->start < b->start;
}

//新增比较
bool LinearScan::compareEnd(Interval* a, Interval* b) 
{
    return a->end < b->end;
}