// 2_3A.cpp
// SUT(System Under Test, 테스트 대상 시스템)
//  => CUT(Class Under Test)
//     CUT(Code Under Test)
class Calc {
public:
    double Display() { return 0; }

    void Enter(double n) { }

    void PressPlus() { }
    void PressMinus() { }
};

#include <gtest/gtest.h>
// 1. Google Test Framework
// 1) 1.8  - Google Mock 프로젝트가 흡수되었습니다.
// 2) 1.10 - 구글 테스트의 내부 용어가 xUnit Test Framework 용어가 통일되었습니다.

// 1.10 이전
//  TestCase
//    - Test
//    - Test

// 1.10 이후
//  TestSuite
//    - TestCase
//    - TestCase

// 2. 테스트케이스를 구성하는 방법
//  1) TEST(테스트스위트 이름, 테스트케이스 이름)
//   => 일반적으로 테스트 대상 클래스의 이름의 뒤에 Test/Spec를 붙이는 형태로
//      테스트 스위트를 구성합니다.
// TEST(CalcTest, Plus) { }
// TEST(CalcTest, Minus) { }

//  2) 테스트를 수행하였을 때, 실패하지 않는다면
//     테스트는 성공합니다.
//  => 테스트를 명시적으로 실패하는 방법
//     FAIL()
//     - 실패의 이유를 명시해야 합니다.
#if 0
TEST(CalcTest, Plus)
{
    // 작성중입니다.
    FAIL() << "작성중입니다.";
}
#endif

//  3) 3A
//   - Arrange(Given): 테스트 대상 코드(SUT)를 초기화하고, 필요한 경우 설정하고 준비합니다.
//   -     Act(When): 테스트 대상 코드에 작용(함수, 메소드)을 가합니다.
//   -  Assert(Then): 기대하는 바를 단언합니다.

// 3. 테스트케이스 품질
//  1) 가독성
//   - 테스트케이스가 실패하였을 때, 실패의 원인이 오류 메세지를 통해
//     드러나는가
//   - 테스트케이스의 이름을 통해서, 테스트의 시나리오를 알 수 있어야 합니다.
//    ex) PressPlus_TwoPlusTwo_DisplaysFour
#define SPEC(msg) printf("SPEC: " msg "\n")

//  2) 유지보수성
//   - 테스트 코드도 유지보수의 대상입니다.
//   - 테스트 코드의 유지보수의 비용이 최소화되어야 합니다.
//    "테스트 코드 안에서 제어 구문의 사용을 최소화해야 합니다."
// > 테스트케이스 안에서 제어구문(조건문, 반복문, 예외 처리)의 발생을
//   최소화해야 합니다.

//  3) 신뢰성
//   - 테스트의 결과를 신뢰할 수 있어야 합니다.
//   => 각각의 테스트케이스를 독립적으로 구성해야 합니다.

// 4. BDD(Behavior Driven Developmern, 행위 주도 개발)
//  1) 가독성 => 용어를 좀 더 문장에 가깝게 사용하는 것을 지향합니다.
//  2) 행위 검증

// 5. 단언문
//   - 매크로 함수의 형태로 제공됩니다.
//    ASSERT_EQ, NE, LT, GT, LE, GE, TRUE, FALSE

// TEST(CalcTest, Plus)
#if 1
TEST(CalcTest, PressPlus_TwoPlusTwo_DisplaysFour)
{
    SPEC("2 더하기 2를 하였을 때, 결과가 4가 제대로 나오는지 검증한다.");

    // Arrange
    Calc* calc = new Calc;

    // Act
    calc->Enter(2);
    calc->PressPlus();
    calc->Enter(2);

    // Assert
    ASSERT_EQ(calc->Display(), 4) << "2+2 하였을 때";

#if 0
    if (calc->Display() == 4) {
        SUCCEED();
    } else {
        FAIL() << "2+2 하였을 때, 기대한 결과와 다릅니다.";
    }
#endif
}
#endif