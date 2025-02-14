#ifndef AST_H
#define AST_H

#include <string>
#include <memory>
#include <vector>

// 기본 AST 노드 (모든 AST 노드의 부모 클래스)
class ExprAST {
public:
    virtual ~ExprAST() = default;
};

// 숫자 노드
class NumberExprAST : public ExprAST {
    double Val;
public:
    NumberExprAST(double Val) : Val(Val) {}
};

// 변수 노드
class VariableExprAST : public ExprAST {
    std::string Name;
public:
    VariableExprAST(const std::string &Name) : Name(Name) {}
};

// 이항 연산 노드 (예: x + y)
class BinaryExprAST : public ExprAST {
    char Op; // 연산자 (+, -, *, /)
    std::unique_ptr<ExprAST> LHS, RHS; // 왼쪽/오른쪽 피연산자
public:
    BinaryExprAST(char Op, std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS) : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
};

// 함수 호출 노드
class CallExprAST : public ExprAST {
    std::string Callee;
    std::vector<std::unique_ptr<ExprAST>> Args;
public:
    CallExprAST(const std::string &Callee, std::vector<std::unique_ptr<ExprAST>> Args) : Callee(Callee), Args(std::move(Args)) {}
};

// 함수 정의 노드
class PrototypeAST {
    std::string Name;
    std::vector<std::string> Args;

public:
    PrototypeAST(const std::string &Name, std::vector<std::string> Args) : Name(Name), Args(std::move(Args)) {}
};

// 함수 본체 노드 (함수 선언 + 함수 바디)
class FunctionAST {
    std::unique_ptr<PrototypeAST> Proto;
    std::unique_ptr<ExprAST> Body;

public:
    FunctionAST(std::unique_ptr<PrototypeAST> Proto, std::unique_ptr<ExprAST> Body) : Proto(std::move(Proto)), Body(std::move(Body)) {}
};

#endif