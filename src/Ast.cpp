#include "Ast.h"
#include <stack>
#include <string>
#include "IRBuilder.h"
#include "Instruction.h"
#include "SymbolTable.h"
#include "Type.h"
#include "Unit.h"
extern Unit unit;
extern MachineUnit mUnit;

#include <iostream>

extern FILE* yyout;
int Node::counter = 0;
IRBuilder* Node::builder;

Node::Node() {
    seq = counter++;
    next = nullptr;
}

void Node::setNext(Node* node) {
    Node* n = this;
    while (n->getNext()) {
        n = n->getNext();
    }
    n->next = node;
}

void Node::backPatch(std::vector<Instruction*>& list, BasicBlock* bb) {
    for (auto& inst : list) {
        if (inst->isCond())
            dynamic_cast<CondBrInstruction*>(inst)->setTrueBranch(bb);
        else if (inst->isUncond())
            dynamic_cast<UncondBrInstruction*>(inst)->setBranch(bb);
    }
}

std::vector<Instruction*> Node::merge(std::vector<Instruction*>& list1,
                                      std::vector<Instruction*>& list2) {
    std::vector<Instruction*> res(list1);
    res.insert(res.end(), list2.begin(), list2.end());
    return res;
}

void Ast::genCode(Unit* unit) {
    IRBuilder* builder = new IRBuilder(unit);
    Node::setIRBuilder(builder);
    root->genCode();
}

void FunctionDef::genCode() {
    // 获取所在unit
    Unit* unit = builder->getUnit();
    Function* func = new Function(unit, se);
    BasicBlock* entry = func->getEntry();
    // set the insert point to the entry basicblock of this function.

    builder->setInsertBB(entry);
    if (decl)
        decl->genCode();
    // function中的stmt节点是用compoundstmt进行初始化的
    if (stmt)
        stmt->genCode();

    //要再次设置流图前后关系
    for (auto block = func->begin(); block != func->end(); block++) {
        //获取该块的最后一条指令
        Instruction* i = (*block)->begin();
        Instruction* last = (*block)->rbegin();
        while (i != last) {
            if (i->isCond() || i->isUncond()) {
                (*block)->remove(i);
            }
            i = i->getNext();
        }
        if (last->isCond()) {
            BasicBlock *truebranch, *falsebranch;
            truebranch =
                dynamic_cast<CondBrInstruction*>(last)->getTrueBranch();
            falsebranch =
                dynamic_cast<CondBrInstruction*>(last)->getFalseBranch();
            if (truebranch->empty()) {
                new RetInstruction(nullptr, truebranch);
            } else if (falsebranch->empty()) {
                new RetInstruction(nullptr, falsebranch);
            }
            (*block)->addSucc(truebranch);
            (*block)->addSucc(falsebranch);
            truebranch->addPred(*block);
            falsebranch->addPred(*block);
        } else if (last->isUncond())  //无条件跳转指令可获取跳转的目标块
        {
            BasicBlock* dst =
                dynamic_cast<UncondBrInstruction*>(last)->getBranch();
            (*block)->addSucc(dst);
            dst->addPred(*block);
            //027报错，缺少return语句
            if (dst->empty()) {
                if (((FunctionType*)(se->getType()))->getRetType() == TypeSystem::intType) {
                    new RetInstruction(new Operand(new ConstantSymbolEntry( TypeSystem::intType, 0)), dst);
                }
                else if (((FunctionType*)(se->getType()))->getRetType() == TypeSystem::voidType) {
                    new RetInstruction(nullptr, dst);
                }
            }

        }
        //最后一条语句不是返回以及跳转
        else if (!last->isRet()) {
            if (((FunctionType*)(se->getType()))->getRetType() ==
                TypeSystem::voidType) {
                new RetInstruction(nullptr, *block);
            }
        }
    }
}

BinaryExpr::BinaryExpr(SymbolEntry* se, int op, ExprNode* expr1, ExprNode* expr2)
    : ExprNode(se), op(op), expr1(expr1), expr2(expr2) {
    dst = new Operand(se);
    //结果为bool型的运算符
    if (op >= BinaryExpr::AND && op <= BinaryExpr::NOTEQUAL) {
        type = TypeSystem::boolType;
        if (op == BinaryExpr::AND || op == BinaryExpr::OR) {
            //修改为bool值
            if (expr1->getType()->isInt() && expr1->getType()->getSize() == 32)
            {
                SymbolEntry* zerosymb=new ConstantSymbolEntry(TypeSystem::intType, 0);
                Constant* zeroconst =new Constant(zerosymb);
                SymbolEntry* castsymb = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
                ExprNode* newexpr1=new BinaryExpr(castsymb,BinaryExpr::NOTEQUAL,expr1,zeroconst);
                this->expr1=newexpr1;
            }
            if (expr2->getType()->isInt() && expr2->getType()->getSize() == 32)
            {
                SymbolEntry* zerosymb=new ConstantSymbolEntry(TypeSystem::intType, 0);
                Constant* zeroconst =new Constant(zerosymb);
                SymbolEntry* castsymb = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
                ExprNode* newexpr2=new BinaryExpr(castsymb,BinaryExpr::NOTEQUAL,expr2,zeroconst);
                this->expr2=newexpr2;
            }
        }
    } else {
        type = TypeSystem::intType;
    }
};

void BinaryExpr::genCode() {
    //builder 是 IRBuilder 类对象，用于传递继承属性，辅助我们进行中间代码生成
    //通过 builder 得到后续生成的指令要插入的基本块 bb
    BasicBlock* bb = builder->getInsertBB();
    Function* func = bb->getParent();
    //生成子表达式的中间代码
    if (op == AND) {
        //第二个子表达式生成的指令需要插入的位置
        BasicBlock *trueBB = new BasicBlock(func);
        trueBB->addPred(bb);//放置这个基本块make
        bb->addSucc(trueBB);//放置这个基本块
        //在当前基本块生成第一个子表达式的中间代码，
        expr1->genCode();
        //当expr1为真时，跳转目标为trueBB，因此truelist的回填目标是trueBB
        backPatch(expr1->trueList(), trueBB);
        //设置当前块为trueBB，即接下来生成的中间代码放入truebb块
        this->builder->setInsertBB(trueBB);               // set the insert point to the trueBB so that intructions generated by expr2 will be inserted into it.
        //trueBB开始的指令为expr2的中间代码
        expr2->genCode();

        //恢复到当前的bb
        bb=builder->getInsertBB();
        //不能知道两个子表达式的 false_list 的跳转基本块，
        //便只能将其插入到当前结点的 false_list中，
        //让父结点回填当前结点的 true_list 和 false_list。
        true_list = expr2->trueList();
        false_list = merge(expr1->falseList(), expr2->falseList());

    } else if (op == OR) {
        // Todo ——————按照&&仿写
        //第二个子表达式生成的指令需要插入的位置
        BasicBlock *trueBB = new BasicBlock(func);
        //在当前基本块生成第一个子表达式的中间代码，
        expr1->genCode();
        //当expr1为假时，依赖于expr2的结果，因此跳转目标为trueBB，因此truelist的回填目标是trueBB
        backPatch(expr1->falseList(), trueBB);
        //设置当前块为trueBB，即接下来生成的中间代码放入truebb块
        builder->setInsertBB(trueBB);               // set the insert point to the trueBB so that intructions generated by expr2 will be inserted into it.
        //trueBB开始的指令为expr2的中间代码
        expr2->genCode();
        //不能知道两个子表达式的 true_list 的跳转基本块，
        //便只能将其插入到当前结点的 true_list
        //让父结点回填当前结点的 true_list 和 false_list。
        true_list = merge(expr1->trueList(), expr2->trueList());
        false_list = expr2->falseList();
    } else if (op >= LESS && op <= NOTEQUAL) {
        // Todo
        expr1->genCode();
        expr2->genCode();
        Operand* src1 = expr1->getOperand();
        Operand* src2 = expr2->getOperand();
        //如果有一方是bool类型，使用一个扩展语句
        if (src1->getType()->getSize() == 1)
        {
            Operand* dst = new Operand(new TemporarySymbolEntry(
                TypeSystem::intType, SymbolTable::getLabel()));
            new ExtensionInstruction(dst, src1, bb);
            src1 = dst;
        }
        if (src2->getType()->getSize() == 1) {
            Operand* dst = new Operand(new TemporarySymbolEntry(
                TypeSystem::intType, SymbolTable::getLabel()));
            new ExtensionInstruction(dst, src2, bb);
            src2 = dst;
        }
        int cmpopcode(-1);
        switch (op) {
            case LESS:
                cmpopcode = CmpInstruction::L;
                break;
            case LESSEQUAL:
                cmpopcode = CmpInstruction::LE;
                break;
            case GREATER:
                cmpopcode = CmpInstruction::G;
                break;
            case GREATEREQUAL:
                cmpopcode = CmpInstruction::GE;
                break;
            case EQUAL:
                cmpopcode = CmpInstruction::E;
                break;
            case NOTEQUAL:
                cmpopcode = CmpInstruction::NE;
                break;
        }
        new CmpInstruction(cmpopcode, dst, src1, src2, bb);
        //
        BasicBlock *truebb, *falsebb, *tempbb;
        //临时假块
        truebb = new BasicBlock(func);
        falsebb = new BasicBlock(func);
        tempbb = new BasicBlock(func);

        true_list.push_back(new CondBrInstruction(truebb, tempbb, dst, bb));

        false_list.push_back(new UncondBrInstruction(falsebb, tempbb));
    } else if (op >= ADD && op <= MOD) {
        expr1->genCode();
        expr2->genCode();
        Operand* src1 = expr1->getOperand();
        Operand* src2 = expr2->getOperand();
        int opcode(-1);
        switch (op) {
            case ADD:
                opcode = BinaryInstruction::ADD;
                break;
            case SUB:
                opcode = BinaryInstruction::SUB;
                break;
            case MUL:
                opcode = BinaryInstruction::MUL;
                break;
            case DIV:
                opcode = BinaryInstruction::DIV;
                break;
            case MOD:
                opcode = BinaryInstruction::MOD;
                break;
        }
        new BinaryInstruction(opcode, dst, src1, src2, bb);
    }
}

void Constant::genCode() {
    // we don't need to generate code.
}

void Id::genCode() {
    BasicBlock* bb = builder->getInsertBB();
    Operand* addr =
        dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getAddr();
    if (type->isInt()) //不是数组类型直接load值
    {
        new LoadInstruction(dst, addr, bb);
        return;
    }
    if (!type->isArray()) {
        return;
    }
    //如果不是数组
    if (!arrIdx) 
    {
        if (((ArrayType*)(this->type))->getLength() == -1) 
        {
            Operand* dst1 = new Operand(new TemporarySymbolEntry(
                new PointerType(
                    ((ArrayType*)(this->type))->getElementType()),
                SymbolTable::getLabel()));
            new LoadInstruction(dst1, addr, bb);
            dst = dst1;
        } 
        else 
        {
            Operand* idx = new Operand(
                new ConstantSymbolEntry(TypeSystem::intType, 0));
            auto gep = new GepInstruction(dst, addr, idx, bb);
            gep->setFirst();
        }
        return;
    }
    //如果是数组
    Type* type = ((ArrayType*)(this->type))->getElementType();
    Type* type1 = this->type;
    Operand* tempSrc = addr;
    Operand* tempDst = dst;
    ExprNode* idx = arrIdx;
    bool flag = false;
    bool pointer = false;
    bool firstFlag = true;
    while (true) 
    {
        if (((ArrayType*)type1)->getLength() == -1) //如果-1说明是参数里的数组，没有规定数组值
        {
            Operand* dst1 = new Operand(new TemporarySymbolEntry(
                new PointerType(type), SymbolTable::getLabel()));
            tempSrc = dst1;
            new LoadInstruction(dst1, addr, bb);
            flag = true;
            firstFlag = false;
        }
        if (!idx) //不是数组元素的话直接gep
        {
            Operand* dst1 = new Operand(new TemporarySymbolEntry(
                new PointerType(type), SymbolTable::getLabel()));
            Operand* idx = new Operand(
                new ConstantSymbolEntry(TypeSystem::intType, 0));
            new GepInstruction(dst1, tempSrc, idx, bb);
            tempDst = dst1;
            pointer = true;
            break;
        }
        //如果是数组元素
        idx->genCode();
        auto gep = new GepInstruction(tempDst, tempSrc,
                                      idx->getOperand(), bb, flag);
        if (!flag && firstFlag) {
            gep->setFirst();
            firstFlag = false;
        }
        flag = false;
        if (type == TypeSystem::intType ||
            type == TypeSystem::constIntType)
            break;
        type = ((ArrayType*)type)->getElementType();
        type1 = ((ArrayType*)type1)->getElementType();
        tempSrc = tempDst;
        tempDst = new Operand(new TemporarySymbolEntry(
            new PointerType(type), SymbolTable::getLabel()));
        idx = (ExprNode*)(idx->getNext());
    }
    dst = tempDst;
    // 如果是右值还需要一条load
    if (!left && !pointer) {
        Operand* dst1 = new Operand(new TemporarySymbolEntry(
            TypeSystem::intType, SymbolTable::getLabel()));
        new LoadInstruction(dst1, dst, bb);
        dst = dst1;
    }
}

void IfStmt::genCode() {
    Function *func;
    BasicBlock *then_bb, *end_bb;
    //得到后续生成的指令要插入的基本块 bb
    func = builder->getInsertBB()->getParent();
    //if(){}中为then基本块内容
    then_bb = new BasicBlock(func);
    //}结束时候的基本块
    end_bb = new BasicBlock(func);

    //生成 cond 结点的中间代码
    cond->genCode();
    //如果条件cond不是bool类型
    if(cond->getType()->isInt() && cond->getType()->getSize() == 32)
    {
        BasicBlock* condbb=cond->builder->getInsertBB();
        Function* tempfunc = cond->builder->getInsertBB()->getParent();
        BasicBlock* trueBB = new BasicBlock(tempfunc);
        BasicBlock* tempbb = new BasicBlock(tempfunc);
        BasicBlock* falseBB = new BasicBlock(tempfunc);
        Operand *temp = new Operand(new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel()));
        //在不相等时跳转，因此为NE
        new CmpInstruction(CmpInstruction::NE,
                            temp,
                            cond->getOperand(),
                            new Operand(new ConstantSymbolEntry(TypeSystem::intType,0)),
                            condbb);//int转bool
        cond->trueList().push_back(new CondBrInstruction(trueBB, tempbb, temp, condbb));
        cond->falseList().push_back(new UncondBrInstruction(falseBB, tempbb));
    }
    //本身就是bool类型不做处理

    //cond 为真时将跳转到基本块 then_bb，cond 为假时将跳转到基本块 end_bb
    backPatch(cond->trueList(), then_bb);
    backPatch(cond->falseList(), end_bb);//回填falseList的后续block为end_bb


    //设置插入点为基本块 then_bb
    builder->setInsertBB(then_bb);
    //生成 thenStmt 结点的中间代码
    thenStmt->genCode();
    //因为生成thenStmt 结点中间代码的过程中可能改变指令的插入点，因此更新
    then_bb = builder->getInsertBB();
    //生成无条件跳转指令跳转到 end_bb。最后设置后续指令的插入点为then_bb
    new UncondBrInstruction(end_bb, then_bb);

    builder->setInsertBB(end_bb);
}

void IfElseStmt::genCode() {
    //仿写ifStmt
    Function* func;
    BasicBlock *then_bb, *else_bb, *end_bb ;//得到后续生成的指令要插入的基本块 bb
    //所在的函数
    func = builder->getInsertBB()->getParent();
    //if(){}中为then基本块内容
    then_bb = new BasicBlock(func);
    //else{}的基本块
    else_bb = new BasicBlock(func);
    //else{}结束时候的基本块
    end_bb = new BasicBlock(func);

    //先生成 cond 结点的中间代码
    cond->genCode();
    //如果条件cond不是bool类型
    if(cond->getType()->isInt() && cond->getType()->getSize() == 32)
    {
        BasicBlock* condbb=cond->builder->getInsertBB();
        Function* tempfunc = cond->builder->getInsertBB()->getParent();
        BasicBlock* trueBB = new BasicBlock(tempfunc);
        BasicBlock* tempbb = new BasicBlock(tempfunc);
        BasicBlock* falseBB = new BasicBlock(tempfunc);
        Operand *temp = new Operand(new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel()));
        //在不相等时跳转，因此为NE
        new CmpInstruction(CmpInstruction::NE,
                            temp,
                            cond->getOperand(),
                            new Operand(new ConstantSymbolEntry(TypeSystem::intType,0)),
                            condbb);//int转bool
        cond->trueList().push_back(new CondBrInstruction(trueBB, tempbb, temp, condbb));
        cond->falseList().push_back(new UncondBrInstruction(falseBB, tempbb));
    }
    //本身就是bool类型不做处理

    //cond 为真时将跳转到基本块 then_bb，cond 为假时将跳转到基本块 else_bb
    backPatch(cond->trueList(), then_bb);
    backPatch(cond->falseList(), else_bb);

    //编写then_bb的代码
    builder->setInsertBB(then_bb);
    //之后在thenStmt中编写中间代码
    thenStmt->genCode();
    //因为生成thenStmt 结点中间代码的过程中可能改变指令的插入点，因此更新
    then_bb = builder->getInsertBB();
    //生成无条件跳转指令之后跳转到 end_bb。
    new UncondBrInstruction(end_bb, then_bb);

    //编写else{}中的中间代码
    builder->setInsertBB(else_bb);
    elseStmt->genCode();
    else_bb = builder->getInsertBB();
    //生成无条件跳转指令之后跳转到 end_bb。
    new UncondBrInstruction(end_bb, else_bb);
    //编写end基本块的中间代码
    builder->setInsertBB(end_bb);
}

void CompoundStmt::genCode() {
    // 递归即可。
    if (stmt)
        stmt->genCode();
}

void SeqNode::genCode() {
    // Todo
    stmt1->genCode();
    stmt2->genCode();
}
 
//数组元素的处理
void DeclStmt::genCodeExprList(Operand* addr)
{
    Operand* init = nullptr;
    BasicBlock* bb = builder->getInsertBB();
    ExprNode* temp = expr;
    std::stack<ExprNode*> stk;//
    std::vector<int> idx;//记录各个维度的索引
    idx.emplace_back(0);
    IdentifierSymbolEntry* se = (IdentifierSymbolEntry*)(id->getSymPtr());
 
    
    auto init_value_list = [&temp, &idx, &stk]()
    {
        stk.push(temp);
        idx.emplace_back(0);
        temp = ((InitValueListExpr*)temp)->getExpr();
    };
 
    auto handle = [&temp, &idx, &stk, &se, &addr, &bb, &init]()
    {
        //生成结果
        temp->genCode();
        Type* type = ((ArrayType*)(se->getType()))->getElementType();
        Operand* tempSrc = addr;
        Operand* tempDst;
        Operand* index;
        bool flag = true;
        int i = 1;
        //为每个元素生成gep指令
        while (true) 
        {
            tempDst = new Operand(new TemporarySymbolEntry(new PointerType(type), SymbolTable::getLabel()));
            index = (new Constant(new ConstantSymbolEntry(TypeSystem::intType, idx[i++])))->getOperand();
            //生成gep指令以获取子元素地址
            auto gep = new GepInstruction(tempDst, tempSrc, index, bb);
            gep->setInit(init);
            //是这一维度的第一个元素
            if (flag) 
            {
                gep->setFirst();
                flag = false;
            }
            //是最后一个元素
            if (type == TypeSystem::intType || type == TypeSystem::constIntType)
            {
                //之前生成的gep指令就是最后一维度数组的gep
                gep->setLast();
                //init指向这一指针类型
                init = tempDst;
                break;
            }
            //其余情况下
            type = ((ArrayType*)type)->getElementType();
            tempSrc = tempDst;
        }
        //生成一条store指令，将值存入dst
        new StoreInstruction(tempDst, temp->getOperand(), bb);
    };
 
    auto pop_stack = [&temp, &idx, &stk]()
    {
        while (true) 
        {
            //下一个最低维度
            if (temp->getNext()) 
            {
                temp = (ExprNode*)(temp->getNext());
                idx[idx.size() - 1]++;
                break;
            } 
            else //全部出栈
            {
                temp = stk.top();
                stk.pop();
                idx.pop_back();
                if (stk.empty())
                    break;
            }
        }
    };
    while (temp) 
    {
        //确定到单维数组上
        while (temp && temp->isInitValueListExpr()) 
        {
            init_value_list();
        }
        if (!temp)
        {
            return;
        }
        //生成gep指令获取各个地址
        handle();
        //全部出栈
        pop_stack();
        //stk清空时退出
        if (!stk.size())
            return;
    }
}
 
void DeclStmt::genCodeExpr(Operand* addr)
{
    //可能不存在初始值
    if (!expr){
        return;
    }
    if (!expr->isInitValueListExpr())//非数组情况
    {
        //直接生成结果然后存入对应地址中。
        BasicBlock* bb = builder->getInsertBB();
        expr->genCode();
        Operand* src = expr->getOperand();
        new StoreInstruction(addr, src, bb);
        return;
    }
    //如果是数组的话需要另外处理
    genCodeExprList(addr);
}

//全局常变量的处理
void DeclStmt::genCodeGlobal()
{
    IdentifierSymbolEntry* se = (IdentifierSymbolEntry*)(id->getSymPtr());
    if (!se->isGlobal()) 
    {
        return;
    }
    Operand* addr = nullptr;
    //新建一个addr_se作为指针指向se
    SymbolEntry* addr_se = new IdentifierSymbolEntry(*se);
    Type* type ;
    //指针类型
    type = new PointerType(se->getType());
    //设置为指针类型
    addr_se->setType(type);
    //操作数是指向se的指针
    addr = new Operand(addr_se);
    se->setAddr(addr);
    //插入全局作用域id表
    unit.insertGlobal(se);
    mUnit.insertGlobal(se);
}

void DeclStmt::genCodeLocal()
{
    IdentifierSymbolEntry* se = (IdentifierSymbolEntry*)(id->getSymPtr());
    if (!se->isLocal()){
        return;
    }
    //先获取所在函数的基本块链表
    Function* func = builder->getInsertBB()->getParent();
    BasicBlock* entry = func->getEntry();
    Instruction* alloca ;
    Operand* addr ;
    SymbolEntry* addr_se ;
    Type* type ;
    //指针类型
    type = new PointerType(se->getType());
    addr_se = new TemporarySymbolEntry(type, SymbolTable::getLabel());
    addr = new Operand(addr_se);
    // 在函数栈中分配空间
    alloca = new AllocaInstruction(addr, se);
    entry->insertFront(alloca);  // 分配指令应该在entry块中
    se->setAddr(addr);  //在符号项中设置addr操作数，以便在后续的代码生成中使用它。
    //对应的值的生成
    genCodeExpr(addr);
}
 
void DeclStmt::genCodeParam()
{
    IdentifierSymbolEntry* se = (IdentifierSymbolEntry*)(id->getSymPtr());
    if (!se->isParam())
    {
        return;
    }
    //先获取所在函数的基本块链表
    Function* func = builder->getInsertBB()->getParent();
    BasicBlock* entry = func->getEntry();
    Instruction* alloca;
    Operand* addr;
    SymbolEntry* addr_se;
    Type* type;
    //指针类型
    type = new PointerType(se->getType());
    addr_se = new TemporarySymbolEntry(type, SymbolTable::getLabel());
    addr = new Operand(addr_se);
    //在函数栈中为该变量id分配空间
    alloca = new AllocaInstruction(addr, se);
    entry->insertFront(alloca);  // allocate instructions should be inserted
                                    // into the begin of the entry block.
    Operand* temp = se->getAddr();
    se->setAddr(addr);
    //对应的值的生成
    genCodeExpr(addr);
    //放入此基本块
    BasicBlock* bb = builder->getInsertBB();
    //temp结果放入addr
    new StoreInstruction(addr, temp, bb);
}
 
void DeclStmt::genCode() {
    //获取符号表项
    IdentifierSymbolEntry* se = (IdentifierSymbolEntry*)(id->getSymPtr());
    //全局常变量
    if (se->isGlobal()) {
        genCodeGlobal();
    }
    //局部变量
    else if (se->isLocal())
    {
        genCodeLocal();
    }
    //函数参数
    else if(se->isParam())
    {
        genCodeParam();
    }
    if (this->getNext()) 
    {
        this->getNext()->genCode();
    }
}


void ReturnStmt::genCode() {
    // Todo
    BasicBlock* bb = builder->getInsertBB();
    Operand* src = nullptr;
    if (retValue) {
        retValue->genCode();
        src = retValue->getOperand();
    }
    //插入的基本块为当前基本块，返回operand
    new RetInstruction(src, bb);
}

void ExprStmt::genCode() {
    // Todo
    expr->genCode();
}
void ContinueStmt::genCode() {
    // Todo
    Function* func = builder->getInsertBB()->getParent();
    BasicBlock* bb = builder->getInsertBB();
    new UncondBrInstruction(((WhileStmt*)whileStmt)->get_cond_bb(), bb);
    BasicBlock* continue_next_bb = new BasicBlock(func);
    builder->setInsertBB(continue_next_bb);
}
void BreakStmt::genCode() {
    // Todo
    Function* func = builder->getInsertBB()->getParent();
    BasicBlock* bb = builder->getInsertBB();
    //跳转到while结束的基本块
    new UncondBrInstruction(((WhileStmt*)whileStmt)->get_end_bb(), bb);
    BasicBlock* break_next_bb = new BasicBlock(func);
    builder->setInsertBB(break_next_bb);
}
void WhileStmt::genCode() {
    Function* func;
    BasicBlock *cond_bb, *while_bb, *end_bb, *bb;
    bb = builder->getInsertBB();
    func = builder->getInsertBB()->getParent();
    cond_bb = new BasicBlock(func);
    while_bb = new BasicBlock(func);
    end_bb = new BasicBlock(func);

    this->cond_bb = cond_bb;
    this->end_bb = end_bb;
    //从当前基本块无条件跳转到cond基本块
    //跟if不同，因为要判断多次
    new UncondBrInstruction(cond_bb, bb);

    builder->setInsertBB(cond_bb);
    cond->genCode();
    //如果条件cond不是bool类型
    if(cond->getType()->isInt() && cond->getType()->getSize() == 32)
    {
        BasicBlock* condbb=cond->builder->getInsertBB();
        Function* tempfunc = cond->builder->getInsertBB()->getParent();
        BasicBlock* trueBB = new BasicBlock(tempfunc);
        BasicBlock* tempbb = new BasicBlock(tempfunc);
        BasicBlock* falseBB = new BasicBlock(tempfunc);
        Operand *temp = new Operand(new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel()));
        //在不相等时跳转，因此为NE
        new CmpInstruction(CmpInstruction::NE,
                            temp,
                            cond->getOperand(),
                            new Operand(new ConstantSymbolEntry(TypeSystem::intType,0)),
                            condbb);//int转bool
        cond->trueList().push_back(new CondBrInstruction(trueBB, tempbb, temp, condbb));
        cond->falseList().push_back(new UncondBrInstruction(falseBB, tempbb));
    }
    //本身就是bool类型不做处理

    backPatch(cond->trueList(), while_bb);
    backPatch(cond->falseList(), end_bb);

    builder->setInsertBB(while_bb);
    stmt->genCode();

    while_bb = builder->getInsertBB();
    new UncondBrInstruction(cond_bb, while_bb);

    builder->setInsertBB(end_bb);
}
void EmptyStmt::genCode() {
    // Todo
}

void InitValueListExpr::genCode() {
    // Todo
}
void FuncCallNode::genCode() {
    //先打印各个参数的中间代码
    std::vector<Operand*> operands;
    ExprNode* temp = param;
    while (temp) {
        temp->genCode();
        operands.push_back(temp->getOperand());
        temp = ((ExprNode*)temp->getNext());
    }
    BasicBlock* bb = builder->getInsertBB();
    //函数调用指令
    new CallInstruction(dst, symbolEntry, operands, bb);
}

void OneOpExpr::genCode() {
    // Todo
    expr->genCode();
    BasicBlock* bb = builder->getInsertBB();
    Operand* src = expr->getOperand();
    if (op == NOT) {
        if(expr->getType()->isInt())
        {
           //改为bool类型
            Operand* temp1 = new Operand(new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel()));
            SymbolEntry *temp2 = new ConstantSymbolEntry(TypeSystem::intType, 0);//和0比
            Constant* digit = new Constant(temp2);
            //属于比较指令
            new CmpInstruction(CmpInstruction::NE, temp1, src,digit->getOperand(),bb);
            src = temp1;
        }
        new BinaryInstruction(BinaryInstruction::NOT, dst, src, src, bb);

        //设置为bool类型
        dst -> getType() -> setKind(5);

    } else if (op == SUB) {
        //是bool类型要扩展之后进行运算
        if(src->getType()->isBool())
        {
            Operand* t =new Operand(new TemporarySymbolEntry(TypeSystem::intType,SymbolTable::getLabel()));
            new ExtensionInstruction(t,expr->getOperand(),bb);
            expr->SetDst(t);
            src = t;
        }
        int opcode=BinaryInstruction::SUB;
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, 0);
        Constant* digit = new Constant(se);
        new BinaryInstruction(opcode, dst, digit -> getOperand(), src, bb);
    }
    true_list = expr->trueList();
    false_list = expr->falseList();
}

void ExprNode::genCode() {
    // Todo
}


void ContinueStmt::typeCheck() {
}
void BreakStmt::typeCheck() {
}
void WhileStmt::typeCheck() {
}
void EmptyStmt::typeCheck() {
}
void InitValueListExpr::typeCheck() {
}
void FuncCallNode::typeCheck() {
}
void OneOpExpr::typeCheck() {
    std::string op_str = op == OneOpExpr::NOT ? "!" : "-";
    if (expr->getType()->isVoid()) {
        fprintf(stderr,"一元运算符\'%s\'操作对象为void类型\n",op_str.c_str());
    }
}

void ExprStmt::typeCheck() {
}

void AssignStmt::genCode() {
    BasicBlock* bb = builder->getInsertBB();
    expr->genCode();
    Operand* addr = nullptr;
    if (lval->getOriginType()->isInt())
        addr = dynamic_cast<IdentifierSymbolEntry*>(lval->getSymPtr())
                   ->getAddr();
    else if (lval->getOriginType()->isArray()) {
        ((Id*)lval)->setLeft();
        lval->genCode();
        addr = lval->getOperand();
    }
    Operand* src = expr->getOperand();
    /***
     * We haven't implemented array yet, the lval can only be ID. So we just
     * store the result of the `expr` to the addr of the id. If you want to
     * implement array, you have to caculate the address first and then store
     * the result into it.
     */
    new StoreInstruction(addr, src, bb);
}

void Ast::typeCheck() {
    if (root != nullptr)
        root->typeCheck();
}

void FunctionDef::typeCheck() {
}

void BinaryExpr::typeCheck() {
    std::string op_str;
    switch (op) {
        case ADD:
            op_str = "+";
            break;
        case SUB:
            op_str = "-";
            break;
        case MUL:
            op_str = "*";
            break;
        case DIV:
            op_str = "/";
            break;
        case MOD:
            op_str = "%";
            break;
        case AND:
            op_str = "&&";
            break;
        case OR:
            op_str = "||";
            break;
        case LESS:
            op_str = "<";
            break;
        case LESSEQUAL:
            op_str = "<=";
            break;
        case GREATER:
            op_str = ">";
            break;
        case GREATEREQUAL:
            op_str = ">=";
            break;
        case EQUAL:
            op_str = "==";
            break;
        case NOTEQUAL:
            op_str = "!=";
            break;
    }
    if (expr1->getType()->isVoid() || expr2->getType()->isVoid())
    {
        fprintf(stderr,"双元运算符 %s 中一方为void类型\n",op_str.c_str());
    }
}

void Constant::typeCheck() {
}

void Id::typeCheck() {
}

void IfStmt::typeCheck() {
}

void IfElseStmt::typeCheck() {
}

void CompoundStmt::typeCheck() {
}

void SeqNode::typeCheck() {
}

void DeclStmt::typeCheck() {
}

void ReturnStmt::typeCheck() {
}

void AssignStmt::typeCheck() {
}

FuncCallNode::FuncCallNode(SymbolEntry* se, ExprNode* param)
    : ExprNode(se), param(param) {
    // 做参数的检查
    dst = nullptr;
    SymbolEntry* s = se;
    int paramCnt = 0;
    ExprNode* temp = param;
    while (temp) {
        paramCnt++;
        temp = (ExprNode*)(temp->getNext());
    }
    while (s) {
        Type* type = s->getType();
        std::vector<Type*> params = ((FunctionType*)type)->getParamsType();
        if ((long unsigned int)paramCnt == params.size()) {
            this->symbolEntry = s;
            break;
        }
        s = s->getNext();
    }
    if (symbolEntry) {
        Type* type = symbolEntry->getType();
        this->type = ((FunctionType*)type)->getRetType();
        if (this->type != TypeSystem::voidType) {
            SymbolEntry* se =
                new TemporarySymbolEntry(this->type, SymbolTable::getLabel());
            dst = new Operand(se);
        }
        std::vector<Type*> params = ((FunctionType*)type)->getParamsType();
        ExprNode* temp = param;
        for (auto it = params.begin(); it != params.end(); it++) {
            if (temp == nullptr) {
                fprintf(stderr, "too few arguments to function %s %s\n",
                        symbolEntry->toStr().c_str(), type->toStr().c_str());
                break;
            } else if ((*it)->getKind() != temp->getType()->getKind())
                fprintf(stderr, "parameter's type %s can't convert to %s\n",
                        temp->getType()->toStr().c_str(),
                        (*it)->toStr().c_str());
            temp = (ExprNode*)(temp->getNext());
        }
        if (temp != nullptr) {
            fprintf(stderr, "too many arguments to function %s %s\n",
                    symbolEntry->toStr().c_str(), type->toStr().c_str());
        }
    }
    if (((IdentifierSymbolEntry*)se)->isSysy()) {
        unit.insertDeclare(se);
    }
}

AssignStmt::AssignStmt(ExprNode* lval, ExprNode* expr)
    : lval(lval), expr(expr) {
    Type* type = ((Id*)lval)->getType();
    SymbolEntry* se = lval->getSymPtr();
    if (type->isInt()) {
        if (((IntType*)type)->isConst()) {
            fprintf(stderr,
                    "cannot assign to variable \'%s\' with const-qualified "
                    "type \'%s\'\n",
                    ((IdentifierSymbolEntry*)se)->toStr().c_str(),
                    type->toStr().c_str());
            return;
        }
    } else if (type->isArray()) {
        fprintf(stderr, "array type \'%s\' is not assignable\n",
                type->toStr().c_str());
        return;
    }
    if (!expr->getType()->isInt()) {
        fprintf(stderr,
                "cannot initialize a variable of type \'int\' with an rvalue "
                "of type \'%s\'\n",
                expr->getType()->toStr().c_str());
    }
}

Type* Id::getType() {
    SymbolEntry* se = this->getSymPtr();
    if (se == nullptr)
        return TypeSystem::voidType;
    Type* type = se->getType();
    if (!arrIdx)
        return type;
    if (!type->isArray()) {
        fprintf(stderr, "subscripted value is not an array\n");
        return TypeSystem::voidType;
    }
    ArrayType* temp1 = (ArrayType*)type;
    ExprNode* temp2 = arrIdx;
    while (!temp1->getElementType()->isInt()) {
        if (!temp2) {
            return temp1;
        }
        temp2 = (ExprNode*)(temp2->getNext());
        temp1 = (ArrayType*)(temp1->getElementType());
    }
    if (!temp2) {
        fprintf(stderr, "subscripted value is not an array\n");
        return temp1;
    } else if (temp2->getNext()) {
        fprintf(stderr, "subscripted value is not an array\n");
        return TypeSystem::voidType;
    }
    return TypeSystem::intType;
}

void ExprNode::output(int level) {
    std::string name, type;
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();
    fprintf(yyout, "%*cconst string\ttype:%s\t%s\n", level, ' ', type.c_str(),
            name.c_str());
}

void Ast::output() {
    fprintf(yyout, "program\n");
    if (root != nullptr)
        root->output(4);
}

void BinaryExpr::output(int level) {
    std::string op_str;
    switch (op) {
        case ADD:
            op_str = "add";
            break;
        case SUB:
            op_str = "sub";
            break;
        case MUL:
            op_str = "mul";
            break;
        case DIV:
            op_str = "div";
            break;
        case MOD:
            op_str = "mod";
            break;
        case AND:
            op_str = "and";
            break;
        case OR:
            op_str = "or";
            break;
        case LESS:
            op_str = "less";
            break;
        case LESSEQUAL:
            op_str = "lessequal";
            break;
        case GREATER:
            op_str = "greater";
            break;
        case GREATEREQUAL:
            op_str = "greaterequal";
            break;
        case EQUAL:
            op_str = "equal";
            break;
        case NOTEQUAL:
            op_str = "notequal";
            break;
    }
    fprintf(yyout, "%*cBinaryExpr\top: %s\ttype: %s\n", level, ' ',
            op_str.c_str(), type->toStr().c_str());
    expr1->output(level + 4);
    expr2->output(level + 4);
}

int BinaryExpr::getValue() {
    int value = 0;
    switch (op) {
        case ADD:
            value = expr1->getValue() + expr2->getValue();
            break;
        case SUB:
            value = expr1->getValue() - expr2->getValue();
            break;
        case MUL:
            value = expr1->getValue() * expr2->getValue();
            break;
        case DIV:
            if(expr2->getValue())
                value = expr1->getValue() / expr2->getValue();
            break;
        case MOD:
            value = expr1->getValue() % expr2->getValue();
            break;
        case AND:
            value = expr1->getValue() && expr2->getValue();
            break;
        case OR:
            value = expr1->getValue() || expr2->getValue();
            break;
        case LESS:
            value = expr1->getValue() < expr2->getValue();
            break;
        case LESSEQUAL:
            value = expr1->getValue() <= expr2->getValue();
            break;
        case GREATER:
            value = expr1->getValue() > expr2->getValue();
            break;
        case GREATEREQUAL:
            value = expr1->getValue() >= expr2->getValue();
            break;
        case EQUAL:
            value = expr1->getValue() == expr2->getValue();
            break;
        case NOTEQUAL:
            value = expr1->getValue() != expr2->getValue();
            break;
    }
    return value;
}

OneOpExpr::OneOpExpr(SymbolEntry* se, int op, ExprNode* expr)
    : ExprNode(se, ONEOPEXPR), op(op), expr(expr) {
    type = TypeSystem::intType;
    dst = new Operand(se);
    //如果此时右端expr也是一元表达式
    if(expr->isOneOpExpr())
    {
        OneOpExpr* temp=(OneOpExpr*)expr;
        //并且是!expr形式，说明为bool值
        if(temp->getOp() == OneOpExpr::NOT)
        {
            temp->setType(TypeSystem::boolType);
        }
    }
};

void OneOpExpr::output(int level) {
    std::string op_str;
    switch (op) {
        case NOT:
            op_str = "not";
            break;
        case SUB:
            op_str = "minus";
            break;
    }
    fprintf(yyout, "%*cOneOpExpr\top: %s\ttype: %s\n", level, ' ',
            op_str.c_str(), type->toStr().c_str());
    expr->output(level + 4);
}

int OneOpExpr::getValue() {
    int value = 0;
    switch (op) {
        case NOT:
            value = !(expr->getValue());
            break;
        case SUB:
            value = -(expr->getValue());
            break;
    }
    return value;
}

void FuncCallNode::output(int level) {
    std::string name, type;
    int scope;
    if (!symbolEntry) {
        return;
    }
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();
    scope = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getScope();
    fprintf(yyout, "%*cFuncCallNode\tfunction name: %s\tscope: %d\ttype: %s\n",
            level, ' ', name.c_str(), scope, type.c_str());
    Node* temp = param;
    while (temp) {
        temp->output(level + 4);
        temp = temp->getNext();
    }
}

void Constant::output(int level) {
    std::string type, value;
    type = symbolEntry->getType()->toStr();
    value = symbolEntry->toStr();
    fprintf(yyout, "%*cIntegerLiteral\tvalue: %s\ttype: %s\n", level, ' ',
            value.c_str(), type.c_str());
}

int Constant::getValue() {
    return ((ConstantSymbolEntry*)symbolEntry)->getValue();
}

int Id::getValue() {
    return ((IdentifierSymbolEntry*)symbolEntry)->getValue();
}

void Id::output(int level) {
    std::string name, type;
    int scope;
    if (!symbolEntry) {
        return;
    }
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();
    scope = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getScope();
    fprintf(yyout, "%*cId\tname: %s\tscope: %d\ttype: %s\n", level, ' ',
            name.c_str(), scope, type.c_str());
    if (!arrIdx) {
        return;
    }
    ExprNode* temp = arrIdx;
    int i = 0;
    while (temp) {
        temp->output(level + 4 + 4 * i++);
        temp = (ExprNode*)(temp->getNext());
    }
}

void InitValueListExpr::output(int level) {
    std::string type;
    if (symbolEntry->getType())
        type = symbolEntry->getType()->toStr();
    fprintf(yyout, "%*cInitValueListExpr\ttype: %s\n", level, ' ',
            type.c_str());
    Node* temp = expr;
    while (temp) {
        temp->output(level + 4);
        temp = temp->getNext();
    }
}

void InitValueListExpr::addExpr(ExprNode* expr) 
{
    if (this->expr == nullptr) {
        assert(childCnt == 0);
        childCnt++;
        this->expr = expr;
    } else {
        childCnt++;
        this->expr->setNext(expr);
    }
}

bool InitValueListExpr::isFull() //是否全部填充完毕
{
    ArrayType* type = (ArrayType*)(this->symbolEntry->getType());
    return childCnt == type->getLength();
}

//将数组中未定义部分全部0填充
void InitValueListExpr::fill() 
{
    Type* type = ((ArrayType*)(this->getType()))->getElementType();
    //是最后一维数组
    if (type->isInt()) 
    {
        while (!isFull())//未定义部分0填充
            this->addExpr(new Constant(new ConstantSymbolEntry(type, 0)));
        return;
    }
    if (type->isArray()) 
    {
        while (!isFull())//未定义部分type填充
            this->addExpr(new InitValueListExpr(new ConstantSymbolEntry(type)));
        ExprNode* temp = expr;
        while (temp) 
        {
            ((InitValueListExpr*)temp)->fill();
            temp = (ExprNode*)(temp->getNext());
        }
    }
}

void CompoundStmt::output(int level) {
    fprintf(yyout, "%*cCompoundStmt\n", level, ' ');
    if (stmt)
        stmt->output(level + 4);
}

void SeqNode::output(int level) {
    // fprintf(yyout, "%*cSequence\n", level, ' ');
    stmt1->output(level);
    stmt2->output(level);
}

void DeclStmt::output(int level) {
    fprintf(yyout, "%*cDeclStmt\n", level, ' ');
    id->output(level + 4);
    if (expr)
        expr->output(level + 4);
    if (this->getNext()) {
        this->getNext()->output(level);
    }
}

void EmptyStmt::output(int level) {
    fprintf(yyout, "%*cBlankStmt\n", level, ' ');
}

void IfStmt::output(int level) {
    fprintf(yyout, "%*cIfStmt\n", level, ' ');
    cond->output(level + 4);
    thenStmt->output(level + 4);
}

void IfElseStmt::output(int level) {
    fprintf(yyout, "%*cIfElseStmt\n", level, ' ');
    cond->output(level + 4);
    thenStmt->output(level + 4);
    elseStmt->output(level + 4);
}

void WhileStmt::output(int level) {
    fprintf(yyout, "%*cWhileStmt\n", level, ' ');
    cond->output(level + 4);
    stmt->output(level + 4);
}
void BreakStmt::output(int level) {
    fprintf(yyout, "%*cBreakStmt\n", level, ' ');
}

void ContinueStmt::output(int level) {
    fprintf(yyout, "%*cContinueStmt\n", level, ' ');
}

void ReturnStmt::output(int level) {
    fprintf(yyout, "%*cReturnStmt\n", level, ' ');
    if (retValue != nullptr)
        retValue->output(level + 4);
}

void AssignStmt::output(int level) {
    fprintf(yyout, "%*cAssignStmt\n", level, ' ');
    lval->output(level + 4);
    expr->output(level + 4);
}

void ExprStmt::output(int level) {
    fprintf(yyout, "%*cExprStmt\n", level, ' ');
    expr->output(level + 4);
}

void FunctionDef::output(int level) {
    std::string name, type;
    name = se->toStr();
    type = se->getType()->toStr();
    fprintf(yyout, "%*cFunctionDefine\tfunction name: %s\ttype: %s\n", level,
            ' ', name.c_str(), type.c_str());
    if (decl) {
        decl->output(level + 4);
    }
    stmt->output(level + 4);
}

