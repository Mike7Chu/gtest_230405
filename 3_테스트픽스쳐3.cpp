// 3_테스트픽스쳐3.cpp
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
// 3) Implicit Set Up(암묵적 설치)
//  => 여러 테스트케이스 안에서 같은 테스트 픽스쳐의 설치의 코드를 암묵적으로 호출되는
//     함수를 통해서 처리합니다.
//  => 명시적인 테스트 스위트 클래스가 필요합니다.
//  장점: 테스트 코드 중복을 제거하고, 불필요한 준비 과정을 테스트케이스 안에서 제거할 수 있습니다.
//  단점: 테스트 픽스쳐 설치 코드가 테스트 케이스 외부에 존재하기 때문에
//       테스트 케이스만으로 테스트 코드를 분석하기 어렵다.

class CalcTest : public testing::Test {
protected:
    Calc* calc = nullptr;

    void SetUp() override
    {
        std::cout << "SetUp" << std::endl;
        calc = new Calc(0);
    }
};

TEST_F(CalcTest, PressPlus_TwoPlusTwo_DisplaysFour)
{
    SPEC("2 더하기 2를 하였을 때, 결과가 4가 제대로 나오는지 검증한다.");

    // Act
    calc->Enter(2);
    calc->PressPlus();
    calc->Enter(2);

    // Assert
    ASSERT_EQ(calc->Display(), 4) << "2+2 하였을 때";
}

TEST_F(CalcTest, PressMinus)
{
    // Act
    calc->Enter(4);
    calc->PressMinus();
    calc->Enter(2);

    // Assert
    ASSERT_EQ(calc->Display(), 2) << "4-2 하였을 때";
}