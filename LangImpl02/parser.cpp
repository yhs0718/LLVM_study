#include "lexer.cpp"
#include "ast.h"
#include <iostream>

// 현재 토큰 저장
static int CurTok;
static int getNextToken() { return CurTok = gettok(); }

// 숫자 파싱
static std::unique_ptr<ExprAST> ParseNumberExpr() {
    auto Result = std::make_unique<NumberExprAST>(NumVal);
    getNextToken(); // 숫자 다음 토큰으로 이동
    return std::move(Result);
}

// 변수 파싱
static std::unique_ptr<ExprAST> ParseIdentifierExpr() {
    std::string IdName = IdentifierStr;

    getNextToken(); // 다음 토큰으로 이동

    if (CurTok != '(') // 변수 단독 사용 
        return std::make_unique<VariableExprAST>(IdName);
    
    // 함수 호출
    getNextToken(); // '(' 넘기기
    std::vector<std::unique_ptr<ExprAST>> Args;
    if (CurTok != ')') {
        while (true) {
            if (auto Arg = ParseNumberExpr())
                Args.push_back(std::move(Arg));
            if (CurTok == ')') break;
            getNextToken();
        }
    }
    getNextToken(); // ')' 넘기기
    return std::make_unique<CallExprAST>(IdName, std::move(Args));
}

// 이항 연산자 파싱
static std::unique_ptr<ExprAST> ParseBinaryExpr() {
    auto LHS = ParseIdentifierExpr(); // 왼쪽 피연산자
    char Op = CurTok;
    getNextToken(); // 연산자 넘기기
    auto RHS = ParseIdentifierExpr(); // 오른쪽 피연산자
    return std::make_unique<BinaryExprAST>(Op, std::move(LHS), std::move(RHS));
}

// 함수 정의 파싱
static std::unique_ptr<FunctionAST> ParseFunctionDefinition() {
    getNextToken(); // 'def' 넘기기
    std::string FnName = IdentifierStr;
    getNextToken(); // 함수명 넘기기

    std::vector<std::string> Args;
    while (CurTok == tok_identifier) {
        Args.push_back(IdentifierStr);
        getNextToken();
    }

    auto Proto = std::make_unique<PrototypeAST>(FnName, std::move(Args));
    auto Body = ParseBinaryExpr();
    return std::make_unique<FunctionAST>(std::move(Proto), std::move(Body));
}