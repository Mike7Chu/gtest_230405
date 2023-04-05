// 3_테스트픽스쳐.cpp
class Calc {
public:
    double Display() { return 0; }

    void Enter(double n) { }

    void PressPlus() { }
    void PressMinus() { }
};

#include <gtest/gtest.h>

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