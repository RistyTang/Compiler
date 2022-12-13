#ifndef __TYPE_H__
#define __TYPE_H__
#include <string>
#include <vector>
#include "SymbolTable.h"

class Type {
   private:
    int kind;

   protected:
    enum { INT, VOID, FUNC, PTR, ARRAY, BOOL};
    int size;

   public:
    Type(int kind, int size = 0) : kind(kind), size(size){};
    virtual ~Type(){};
    virtual std::string toStr() = 0;
    bool isInt() const { return kind == INT; };
    bool isVoid() const { return kind == VOID; };
    bool isFunc() const { return kind == FUNC; };
    bool isPtr() const { return kind == PTR; };
    bool isArray() const { return kind == ARRAY; };
    bool isBool() const {return kind == BOOL; };
    void setKind(int kinds) { this->kind = kinds; };
    int getKind() const { return kind; };
    int getSize() const { return size; };
};

//int类型
class IntType : public Type {
   private:
    bool constant;

   public:
    IntType(int size, bool constant = false)
        : Type(Type::INT, size), constant(constant){};
    std::string toStr();
    bool isConst() const { return constant; };
};

//void类型
class VoidType : public Type {
   public:
    VoidType() : Type(Type::VOID){};
    std::string toStr();
};

//bool类型
class BoolType : public Type
{
public:
    BoolType() : Type(Type::BOOL){};
    std::string toStr();
    Type* getrettype(){return NULL;}
};

//函数类型
class FunctionType : public Type {
   private:
    Type* returnType;
    std::vector<Type*> paramsType;
    std::vector<SymbolEntry*> paramsSe;

   public:
    FunctionType(Type* returnType,
                 std::vector<Type*> paramsType,
                 std::vector<SymbolEntry*> paramsSe)
        : Type(Type::FUNC),
          returnType(returnType),
          paramsType(paramsType),
          paramsSe(paramsSe){};
    void setParamsType(std::vector<Type*> paramsType) {
        this->paramsType = paramsType;
    };
    std::vector<Type*> getParamsType() { return paramsType; };
    std::vector<SymbolEntry*> getParamsSe() { return paramsSe; };
    Type* getRetType() { return returnType; };
    std::string toStr();
};

//数组类型
class ArrayType : public Type {
   private:
    Type* elementType;
    Type* arrayType = nullptr;
    int length;
    bool constant;

   public:
    ArrayType(Type* elementType, int length, bool constant = false)
        : Type(Type::ARRAY),
          elementType(elementType),
          length(length),
          constant(constant) {
        size = elementType->getSize() * length;
    };
    std::string toStr();
    int getLength() const { return length; };
    Type* getElementType() const { return elementType; };
    void setArrayType(Type* arrayType) { this->arrayType = arrayType; };
    bool isConst() const { return constant; };
    Type* getArrayType() const { return arrayType; };
};

//指针类型
class PointerType : public Type {
   private:
    Type* valueType;

   public:
    PointerType(Type* valueType) : Type(Type::PTR) {
        this->valueType = valueType;
    };
    std::string toStr();
    Type* getType() const { return valueType; };
};

class TypeSystem {
   private:
    static IntType commonInt;
    static IntType commonBool;
    static VoidType commonVoid;

   public:
    static Type* intType;
    static Type* voidType;
    static Type* boolType;
};

#endif
