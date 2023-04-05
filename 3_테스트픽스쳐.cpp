// 3_테스트픽스쳐.cpp
class Calc {
public:
    // 요구 사항 변경
    // Calc(int n) { }

    double Display() { return 0; }

    void Enter(double n) { }

    void PressPlus() { }
    void PressMinus() { }
};

#include <gtest/gtest.h>
#define SPEC(msg) printf("SPEC: " msg "\n")

// 1. Test Fixture
//  정의: xUnit Test Framework에서 SUT를 실행하기 위해서 준비해야 하는
//      모든 것을 테스트 픽스쳐라고 합니다.
//      테스트 픽스쳐를 구성하는 모든 코드의 로직부분을 "픽스쳐 설치"라고 합니다.

// 2. Test Fixture 설치하는 방법 3가지
// 1) Inline Fixture Setup
//  : 모든 픽스쳐 설치를 테스트 케이스 안에서 수행합니다.
//  장점: 픽스쳐를 설치하는 과정과 검증의 로직이 하나의 테스트 케이스 함수 안에 존재하기
//       때문에 인과 관계를 분석하기 쉽다.
//  단점: 모든 테스트케이스 안에서 "테스트 코드 중복" 문제가 발생합니다.

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
}

TEST(CalcTest, PressMinus)
{
    // Arrange
    Calc* calc = new Calc;

    // Act
    calc->Enter(4);
    calc->PressMinus();
    calc->Enter(2);

    // Assert
    ASSERT_EQ(calc->Display(), 2) << "4-2 하였을 때";
}