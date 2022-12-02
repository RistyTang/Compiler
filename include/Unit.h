#ifndef __UNIT_H__
#define __UNIT_H__

#include <vector>
#include "Function.h"

//这个class的作用是用链表记录了一系列函数
class Unit
{
    typedef std::vector<Function *>::iterator iterator;//指针
    typedef std::vector<Function *>::reverse_iterator reverse_iterator;//反向指针
private:
    std::vector<Function *> func_list;//包含的函数
public:
    Unit() = default;
    ~Unit() ;
    void insertFunc(Function *);
    void removeFunc(Function *);
    void output() const;
    iterator begin() { return func_list.begin(); };
    iterator end() { return func_list.end(); };
    //反向迭代器的头应该是函数列表的尾部
    reverse_iterator rbegin() { return func_list.rbegin(); };
    reverse_iterator rend() { return func_list.rend(); };
};

#endif