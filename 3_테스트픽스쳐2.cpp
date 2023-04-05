// 3_테스트픽스쳐2.cpp
class Calc {
public:
    // 요구 사항 변경
    Calc(int n) { }

    double Display() { return 0; }

    void Enter(double n) { }

    void PressPlus() { }
    void PressMinus() { }
};

#include <gtest/gtest.h>
#define SPEC(msg) printf("SPEC: " msg "\n")

// 2. Test Fixture 설치하는 방법 3가지
// 2) Delegate Set Up(위임 설치)
//  : 픽스쳐 설치에 관한 코드를 별도의 "테스트 유틸리티 함수" 통해 캡슐화합니다.
//  => 명시적인 테스트 스위트 클래스를 제공해야 합니다.

// - TEST
// class CalcTest_PressPlus_TwoPlusTwo_DisplaysFour_Test : public ::testing::Test

// 명시적인 테스트 스위트 클래스
class CalcTest : public testing::Test {
protected:
    // 구글 테스트에서 테스트 유틸리티 메소드를 제공할 때,
    // protected로 만들어야 하는 구조적인 이유를 이해하는 것이 중요합니다.

    Calc* CreateCalc() { return new Calc(0); }
};
// - TEST_F
// class CalcTest_PressPlus_TwoPlusTwo_DisplaysFour_Test : public CalcTest

// TEST_F의 매크로를 통해 테스트 케이스를 만들어야 합니다.
TEST_F(CalcTest, PressPlus_TwoPlusTwo_DisplaysFour)
{
    SPEC("2 더하기 2를 하였을 때, 결과가 4가 제대로 나오는지 검증한다.");

    // Arrange
    Calc* calc = CreateCalc();

    // Act
    calc->Enter(2);
    calc->PressPlus();
    calc->Enter(2);

    // Assert
    ASSERT_EQ(calc->Display(), 4) << "2+2 하였을 때";
}

// class CalcTest_PressMinus_Test : public ::testing::Test
TEST_F(CalcTest, PressMinus)
{
    // Arrange
    Calc* calc = CreateCalc();

    // Act
    calc->Enter(4);
    calc->PressMinus();
    calc->Enter(2);

    // Assert
    ASSERT_EQ(calc->Display(), 2) << "4-2 하였을 때";
}

// 1) 암묵적인 테스트 스위트 클래스
// TEST(SampleTest, foo)
// class SampleTest_foo_Test : public testing::Test {};

// TEST(SampleTest, goo)
// class SampleTest_goo_Test : public testing::Test {};

//                testing::Test
//                       |
//      -------------------------------------
//      |                                   |
// SampleTest_foo_Test           SampleTest_goo_Test

// 2) 명시적인 테스트 스위트 클래스
// class SampleTest : public testing::Test {};

// TEST_F(SampleTest, foo)
// class SampleTest_foo_Test : public SampleTest {};

// TEST_f(SampleTest, goo)
// class SampleTest_goo_Test : public SampleTest {};

//                 testing::Test
//                       |
//                  SampleTest => 테스트 유틸리티 메소드
//                       |
//      -------------------------------------
//      |                                   |
// SampleTest_foo_Test           SampleTest_goo_Test