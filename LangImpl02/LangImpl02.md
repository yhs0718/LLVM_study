## 1. 목표: Parser & AST 만들기
이 단계에서는 Kaleidoscope 언어의 Parser를 만들고, AST 생성

✏️ 목표
- Lexer를 사용하여 이벽을 Token으로 변환 (LangImpl01에서 완료)
- Token을 기반으로 AST (추상 구문 트리) 생성
- 수식 파싱 (1 + 2 * 3) 지원
- 함수 정의 (def add(x y) x + y) 지원
- 함수 호출 (add(4, 5)) 지원

## 2. AST
AST는 코드의 구조를 트리 형태로 표현한 것   
코드의 문법적 구조를 이해하는데 중요하며, LLVM IR 변환 및 최적화를 수행할 때 사용됨
``` 
# 예제 코드
def add(x, y) x + y

# AST 형태
    +
   / \
  x   y

# 함수 정의
Function: add
  ├── Param: x
  ├── Param: y
  └── Body:
        └── (+ x y)
```
