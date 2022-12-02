#include "Type.h"
#include <sstream>
//Int型大小为32，bool为1
IntType TypeSystem::commonInt = IntType(32);
IntType TypeSystem::commonBool = IntType(1);
VoidType TypeSystem::commonVoid = VoidType();

Type* TypeSystem::intType = &commonInt;
Type* TypeSystem::voidType = &commonVoid;
Type* TypeSystem::boolType = &commonBool;

std::string IntType::toStr()
{
    //将int型的size转化为string输出
    std::ostringstream buffer;
    buffer << "i" << size;
    return buffer.str();
}

std::string VoidType::toStr()
{
    return "void";
}

std::string FunctionType::toStr()
{
    //将Type类型转化为string输出
    std::ostringstream buffer;
    buffer << returnType->toStr() << "()";
    return buffer.str();
}

std::string PointerType::toStr()
{
    //将Type类型转化为string输出
    std::ostringstream buffer;
    buffer << valueType->toStr() << "*";
    return buffer.str();
}

void FunctionType::setparamsType(std::vector<Type*> in)
{
    paramsType = in;
}
