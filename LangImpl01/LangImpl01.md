## 1. 개요
Kaleidoscope 언어는 다음 기능을 갖춘 간단한 스크립트 언어
1. 변수와 숫자 사용 가능
2. 함수 정의 가능 (def add(x y) x+y)
3. 표현식 지원 ((1+2)*3)

LLVM을 사용하여 컴파일 과정을 직접 구현하는 것이 목표
| Lexing -> Parsing -> AST -> LLVM IR -> JIT 실행 단계

## 2. Lexing (어휘 분석)
Lexing 은 소스코드를 읽어서 "토큰(Token)"으로 변환하는 과정

### 예제 코드
``` 
def foo(x y) x + y
```
Lexing 과정에서 위 코드를 다음과 같이 분해함
```
Token:  def     (키워드)
Token:  foo     (식별자)
Token:  (       (구분 기호)
Token:  x       (식별자)
Token:  y       (식별자)
Token:  )       (구분 기호)
Token:  x       (식별자)
Token:  +       (연산자)
Token:  y       (식별자)
```
-> 즉, 소스 코드의 문자를 분석하여 의미 있는 단위(토큰)로 변환하는 과정

## 3. Lexer 구현 (gettok) 함수

## 4. Lexer 테스트 
```
hsyun@Heesun-NOTEBOOK LangImpl01 % clang++ -g -O3 main.cpp lexer.cpp parser.cpp -o Kaleidoscope
hsyun@Heesun-NOTEBOOK LangImpl01 % ./Kaleidoscope
def add(x, y) x + y
Token -2
Token -4
Token 40
Token -4
Token 44
Token -4
Token 41
Token -4
Token 43
Token -4
```