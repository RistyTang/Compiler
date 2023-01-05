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
    std::vector<Interval*> intervals;
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

public:
    LinearScan(MachineUnit* unit);
    void allocateRegisters();
};

#endif