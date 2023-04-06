// 10_파라미터화테스트2.cpp

bool IsPrime(int value)
{
    for (int i = 2; i < value; i++) {
        if (value % i == 0) {
            return false;
        }
    }

    return true;
}

#include <gtest/gtest.h>
// 파라미터화 테스트 패턴(Parameterized Test Pattern)
// : xUnit Test Framework가 제공하는 기능입니다.
//  => 파라미터화 테스트는 테스트의 복잡도를 높일 수 있다.
//    "테스트의 유지보수성이 낮아질 수 있습니다."

// 의도: 입력 데이터를 바꿔가며, 반복 검사하는 데이터 중심의 테스트에서
//     코드 중복을 제거할 수 있습니다.

// 1. 명시적인 테스트 스위트 클래스를 만들어야 합니다.
//  기존) class PrimeTest : public testing::Test {};
//  파라미터화 테스트) class PrimeTest : public testing::TestWithParam<int>
class PrimeTest : public testing::TestWithParam<int> {
public:
    void SetUp() override
    {
        std::cout << "SetUp()" << std::endl;
    }

    void TearDown() override
    {
        std::cout << "TearDown()" << std::endl;
    }

    static void SetUpTestSuite()
    {
        std::cout << "SetUpTestSuite()" << std::endl;
    }

    static void TearDownTestSuite()
    {
        std::cout << "TearDownTestSuite()" << std::endl;
    }
};

// 2. 데이터 셋을 정의해야 합니다.
// => 매크로 형태로 제공됩니다.
// INSTANTIATE_TEST_SUITE_P(데이터 셋 이름, 테스트 스위트 클래스, 데이터 셋)
INSTANTIATE_TEST_SUITE_P(PrimeValues, PrimeTest,
    testing::Values(2, 3, 5, 7, 11, 13, 17, 23, 29, 31, 34));

// 3. 데이터를 활용하는 테스트 케이스를 만들면 됩니다.
//  기존) TEST_F(PrimeTest, IsPrime)
//  파라미터화 테스트) TEST_P(PrimeTest, IsPrime)
TEST_P(PrimeTest, IsPrime)
{
    EXPECT_TRUE(IsPrime(GetParam()));
}

//-------
// Google Test 에서 테스트 케이스 만드는 방법 3가지
// 1) TEST
// => 명시적인 테스트 스위트 클래스가 필요하지 않을 때
// TEST(SampleTest, foo) {}

// 2) TEST_F
// => 명시적인 테스트 스위트 클래스가 필요할 때
// class SampleTest : public testing::Test {};
// TEST_F(SampleTest, foo) {}

// 3) TEST_P
// class SampleTest : public testing::TestWithParam<T> {};
// TEST_P(SampleTest, foo) {
//    GetParam();
// }