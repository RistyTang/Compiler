/**
 * linear scan register allocation
 */

#ifndef _LINEARSCAN_H__
#define _LINEARSCAN_H__
#include <list>
#include <map>
#include <set>
#include <vector>

class MachineUnit;
class MachineOperand;
class MachineFunction;
//为虚拟寄存器分配物理寄存器
class LinearScan 
{
   private:
    struct Interval {
        int start;
        int end;
        bool spill;  //是否溢出到栈
        int disp;    // 栈偏移
        int rreg;  // 如果vreg没有溢出到内存，则从虚拟寄存器映射到实寄存器
        std::set<MachineOperand*> defs;
        std::set<MachineOperand*> uses;
    };
    MachineUnit* unit;//机器代码单元
    MachineFunction* func;//机器代码的函数
    std::vector<int> regs;
    std::map<MachineOperand*, std::set<MachineOperand*>> du_chains;
    std::vector<Interval*> intervals;//还未分配寄存器的活跃区间；所有的 interval 都按照开始位置进行递增排序
    static bool compareStart(Interval* a, Interval* b);
    void expireOldIntervals(Interval* interval);
    void spillAtInterval(Interval* interval);
    void makeDuChains();
    void computeLiveIntervals();
    bool linearScanRegisterAllocation();//线性扫描实现寄存器分配
    void modifyCode();
    void genSpillCode();
    //新增
    std::vector<Interval*> active;
    static bool compareEnd(Interval* a, Interval* b);
    void InitRegs();
    bool PopReg(int& res);
    void genIntervalUse(Interval*& interval, MachineOperand* off, MachineOperand* fp, MachineOperand* use);
    void genIntervalDef(Interval*& interval, MachineOperand* off, MachineOperand* fp, MachineOperand* def);
    void genIntervalCode(Interval*& interval);
    void insertActive(Interval* elem);
public:
    LinearScan(MachineUnit* unit);
    void allocateRegisters();
};

#endif