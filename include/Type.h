#ifndef __TYPE_H__
#define __TYPE_H__
#include <vector>
#include <string>
                                           
class Type
{
private:
    int kind;
protected:
    //增加bool类型
    enum {INT, VOID, FUNC, PTR, BOOL};
public:
    Type(int kind) : kind(kind) {};
    virtual ~Type() {};
    virtual std::string toStr() = 0;
    bool isInt() const {return kind == INT;};
    bool isVoid() const {return kind == VOID;};
    bool isFunc() const {return kind == FUNC;};
    //那这里要不要加isPtr?
    bool isPtr() const {return kind==PTR;};
    bool isBool() const {return kind == BOOL;};
    //设置类型
    void setKind(int n) {this->kind=n;};
    //获取类型
    int getKind() const { return kind; };
};

class IntType : public Type
{
private:
    int size;
public:
    IntType(int size) : Type(Type::INT), size(size){};
    std::string toStr();
};

class VoidType : public Type
{
public:
    VoidType() : Type(Type::VOID){};
    std::string toStr();
};

class FunctionType : public Type
{
private:
    Type *returnType;//返回类型
    std::vector<Type*> paramsType;//各个函数参数的类型
public:
    FunctionType(Type* returnType, std::vector<Type*> paramsType) : 
    Type(Type::FUNC), returnType(returnType), paramsType(paramsType){};
    std::string toStr();
    //设置参数类型
    void setparamsType(std::vector<Type*>);
    Type* getRetType() {return this->returnType;};
};

class PointerType : public Type
{
private:
    Type *valueType;
public:
    PointerType(Type* valueType) : Type(Type::PTR) {this->valueType = valueType;};
    std::string toStr();
};

class TypeSystem
{
private:
    static IntType commonInt;
    static IntType commonBool;
    static VoidType commonVoid;
public:
    static Type *intType;
    static Type *voidType;
    static Type *boolType;
};

#endif
