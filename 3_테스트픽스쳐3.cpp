#include <iostream>

// 3_테스트픽스쳐3.cpp
class Calc {
public:
    // 요구 사항 변경
    Calc(int n) { }
    ~Calc() { std::cout << "~Calc()" << std::endl; }

    double Display() { return 0; }

    void Enter(double n) { }

    void PressPlus() { }
    void PressMinus() { }
};

#include <gtest/gtest.h>
#define SPEC(msg) printf("SPEC: " msg "\n")

// 2. Test Fixture 설치하는 방법 3가지
// 3) Implicit Set Up / Tear Down(암묵적 설치/해체)
//  => 여러 테스트케이스 안에서 같은 테스트 픽스쳐의 설치/해체의 코드를 암묵적으로 호출되는
//     함수를 통해서 처리합니다.
//  => 명시적인 테스트 스위트 클래스가 필요합니다.
//  장점: 테스트 코드 중복을 제거하고, 불필요한 준비 과정을 테스트케이스 안에서 제거할 수 있습니다.
//  단점: 테스트 픽스쳐 설치 코드가 테스트 케이스 외부에 존재하기 때문에
//       테스트 케이스만으로 테스트 코드를 분석하기 어렵다.

// 3. ASSERT_XX
//  => 테스트케이스 안에서 ASSERT가 실패할 경우,
//     이후의 코드가 수행되지 않습니다.

// 4. xUnit Test Pattern에서 테스트케이스를 구성하는 방법
// => 4단계 테스트 패턴(Four Phase Test Pattern)
//  1단계: 테스트 픽스쳐를 설치하거나, 실제 결과를 관찰하기 위해
//        필요한 것을 설정합니다. => SetUp

//  2단계: SUT와 상호 작용합니다.
//  3단계: 기대 결과를 확인합니다.

//  4단계: 테스트 픽스쳐를 해체해서, 테스트케이스 시작 이전의 상태와
//        동일하게 만들어줍니다. => TearDown

class CalcTest : public testing::Test {
protected:
    Calc* calc = nullptr;

    void SetUp() override
    {
        std::cout << "SetUp" << std::endl;
        calc = new Calc(0);
    }

    void TearDown() override
    {
        std::cout << "TearDown" << std::endl;
        delete calc;
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

    // delete calc;
}

TEST_F(CalcTest, PressMinus)
{
    // Act
    calc->Enter(4);
    calc->PressMinus();
    calc->Enter(2);

    // Assert
    ASSERT_EQ(calc->Display(), 2) << "4-2 하였을 때";

    // delete calc;
}