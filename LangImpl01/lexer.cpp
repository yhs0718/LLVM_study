#include <cctype>
#include <cstdio>
#include <string>

// 토큰 유형 정의
enum Token {
    tok_eof = -1,       // 파일 종료
    tok_def = -2,       // def 키워드
    tok_extern = -3,    // extern 키워드
    tok_identifier = -4, // 변수명 또는 함수명
    tok_number = -5     // 숫자
};

// 전역 변수
static std::string IdentifierStr;   // 변수 이름 저장
static double NumVal;               // 숫자 저장

// 입력에서 다음 토큰을 읽고 반환하는 함수
static int gettok() {
    static int LastChar = ' ';

    // 공백 무시
    while (isspace(LastChar))
        LastChar = getchar();
    
    // 변수명, 키워드 처리
    // 만약 isalpha(LastChar) 라면, 문자가 알파벳임을 의미
    // 반복문을 돌면서 foo123 같은 식별자를 인식할 수 있도록 함
    // 만약 키워드(def, extern)이면 해당 토큰 반환, 그렇지 않으면 일반 identifier(변수명, 함수명)으로 처리
    if (isalpha(LastChar)) {
        IdentifierStr = LastChar;
        while (isalnum((LastChar = getchar())))
            IdentifierStr += LastChar;
        
        if (IdentifierStr == "def") return tok_def;
        if (IdentifierStr == "extern") return tok_extern;
        return tok_identifier;
    }

    // 숫자 처리
    // 숫자가 나오면 NumStr 문자열에 추가
    // strtod()를 사용하여 실제 숫자로 변환
    // tok_number 토큰을 반환
    if (isdigit(LastChar) || LastChar == '.'){
        std::string NumStr;
        do {
            NumStr += LastChar;
            LastChar = getchar();
        } while (isdigit(LastChar) || LastChar == '.');

        NumVal = strtod(NumStr.c_str(), nullptr);
        return tok_number;
    }

    // 주석 처리 (# 이후의 모든 내용 무시)
    // gettok()를 다시 호출하여 주석 이후의 유효한 토큰을 분석
    if (LastChar == '#'){
        do LastChar = getchar();
        while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');
        if (LastChar != EOF) return gettok();
    }

    // 파일 종료 처리
    if (LastChar == EOF)
        return tok_eof;
    
    // 일반 문자 반환
    // 숫자, 문자, 주석이 아니라면 기본적으로 해당 문자를 그대로 반환
    // 예: +, -, *, /, (, ), ',' 등
    int ThisChar = LastChar;
    LastChar = getchar();
    return ThisChar;
}