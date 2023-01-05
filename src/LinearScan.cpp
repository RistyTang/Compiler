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
                genSpillCode();
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

bool LinearScan::linearScanRegisterAllocation() 
{
    //TODO
   bool success = true;
    active.clear();
    InitRegs();
    for (auto& i : intervals) 
    {
        expireOldIntervals(i);
        int allocateReg;
        if (PopReg(allocateReg)){
            i->rreg = allocateReg;
            insertActive(i);
        } else {
            spillAtInterval(i);
            // 不知道是不是该这样
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

void LinearScan::genIntervalUse(Interval*& interval, MachineOperand* off, MachineOperand* fp, MachineOperand* use){
    auto temp = new MachineOperand(*use);
    if (interval->disp > 255 || interval->disp < -255) 
    {
        auto operand = MachineOperand::newVReg();
        auto inst1 = new LoadMInstruction(use->getParent()->getParent(), operand, off);
        use->getParent()->insertBefore(inst1);
 
        auto inst = new LoadMInstruction(use->getParent()->getParent(), temp,
                                    fp, new MachineOperand(*operand));
        use->getParent()->insertBefore(inst);
    } 
    else 
    {
        auto inst = new LoadMInstruction(use->getParent()->getParent(), temp, fp, off);
        use->getParent()->insertBefore(inst);
    }
}

void LinearScan::genIntervalDef(Interval*& interval, MachineOperand* off, MachineOperand* fp, MachineOperand* def)
{
    auto temp = new MachineOperand(*def);
    if (interval->disp > 255 || interval->disp < -255) {
        auto operand = MachineOperand::newVReg();
        auto inst1 = new LoadMInstruction(def->getParent()->getParent(), operand, off);
        def->getParent()->insertAfter(inst1);
 
        auto inst = new StoreMInstruction(def->getParent()->getParent(), temp,
                                    fp, new MachineOperand(*operand));
 
        inst1->insertAfter(inst);
 
    } else {
        auto inst = new StoreMInstruction(def->getParent()->getParent(),
                                        temp, fp, off);
 
        def->getParent()->insertAfter(inst);
    }
 
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
    interval->disp = -func->AllocSpace(4);
    auto off = new MachineOperand(MachineOperand::IMM, interval->disp);
    auto fp = MachineOperand::newReg(MachineOperand::RegType::FP);
    for (auto use : interval->uses) {
        genIntervalUse(interval, off, fp, use);
    }
    for (auto def : interval->defs) {
        genIntervalDef(interval, off, fp, def);
    }
}

void LinearScan::genSpillCode() 
{
    for (auto& interval : intervals) 
    {
        genIntervalCode(interval);
    }
}

void LinearScan::expireOldIntervals(Interval* interval) 
{
    //TODO
    auto it = active.begin();
    while (it != active.end()) {
        if ((*it)->end >= interval->start)
            break;
        regs.emplace_back((*it)->rreg);
        it = active.erase(it);
    }
    sort(regs.begin(), regs.end());
}

void LinearScan::insertActive(Interval* elem)
{
    active.emplace_back(elem);
    sort(active.begin(), active.end(), [](Interval* a, Interval* b){return a->end < b->end;});
}

void LinearScan::spillAtInterval(Interval* interval) 
{
     //TODO
    auto spill = active.back();
    if (spill->end <= interval->end) 
    {
        interval->spill = true;
    } 
    else 
    {
        spill->spill = true;
        interval->rreg = spill->rreg;
        insertActive(interval);
    }
}

bool LinearScan::compareStart(Interval* a, Interval* b) 
{
    return a->start < b->start;
}

bool LinearScan::compareEnd(Interval* a, Interval* b) {
    return a->end < b->end;
}