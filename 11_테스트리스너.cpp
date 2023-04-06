// 11_테스트리스너.cpp
// > Google Test의 기능입니다.
// 정의: 모든 테스트의 과정에서 수행해야 하는 작업을 정의할 수 있습니다.

#include <gtest/gtest.h>

TEST(SampleTest, foo) { }
TEST(SampleTest, goo) { }

TEST(ImageTest, foo) { }
TEST(ImageTest, goo)
{
    FAIL();
}

// 1. 테스트 리스너를 만드는 방법
// class MyTestEventListener : public testing::TestEventListener {};

// > 필요한 함수만 구현하고 싶다면,
//   testing::EmptyTestEventListener를 상속하면, 원하는 기능만 재정의할 수 있습니다.
class MyTestEventListener : public testing::EmptyTestEventListener {
public:
    void OnTestProgramStart(const testing::UnitTest& unit_test) override
    {
        std::cout << __func__ << std::endl;
    }
    void OnTestProgramEnd(const testing::UnitTest& unit_test) override
    {
        std::cout << __func__ << std::endl;
    }

    void OnTestSuiteStart(const testing::TestSuite& test_case) override
    {
        std::cout << __func__ << std::endl;
    }
    void OnTestSuiteEnd(const testing::TestSuite& test_case) override
    {
        std::cout << __func__ << std::endl;
    }

    void OnTestStart(const testing::TestInfo& test_info) override
    {
        std::cout << __func__ << std::endl;
    }
    void OnTestEnd(const testing::TestInfo& test_info) override
    {
        std::cout << __func__ << std::endl;
        std::cout << test_info.test_suite_name() << "." << test_info.name()
                  << " : "
                  << (test_info.result()->Passed() ? "PASS" : "FAIL")
                  << std::endl;
    }
};

// 2. 테스트 리스너를 등록하는 방법
// => main을 직접 정의해서 등록해야 합니다.
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();
    listeners.Append(new MyTestEventListener);

    return RUN_ALL_TESTS();
}
