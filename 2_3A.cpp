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
//   - Arrange: 테스트 대상 코드(SUT)를 초기화하고, 필요한 경우 설정하고 준비합니다.
//   -     Act: 테스트 대상 코드에 작용(함수, 메소드)을 가합니다.
//   -  Assert: 기대하는 바를 단언합니다.

TEST(CalcTest, Plus)
{
    // Arrange
    Calc* calc = new Calc;

    // Act
    calc->Enter(2);
    calc->PressPlus();
    calc->Enter(2);

    // Assert
    if (calc->Display() == 4) {
        SUCCEED();
    } else {
        FAIL() << "2+2 하였을 때, 기대한 결과와 다릅니다.";
    }
}