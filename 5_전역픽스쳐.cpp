// 5_전역픽스쳐.cpp
#include <gtest/gtest.h>

// 1. 전역 픽스쳐(Global Fixture)
// - xUnit Test Framework의 기능이 아닙니다.
// => Google Test 고유의 기능입니다.

// => 프로그램의 시작/종료에서 픽스쳐를 설치하고, 해체하는 기능을
//    제공할 수 있습니다.
TEST(SampleTest, First) { }
TEST(SampleTest, Second) { }

TEST(ImageProcessorTest, ResizeImage) { }

// 2. 전역 픽스쳐 설치/해체 방법
// 1) testing::Environment를 상속해서
//    설치와 해체의 코드를 작성합니다.
class MyTestEnvironment : public testing::Environment {
public:
    void SetUp() override
    {
        std::cout << "MyTestEnvironment SetUp()" << std::endl;
    }

    void TearDown() override
    {
        std::cout << "MyTestEnvironment TearDown()" << std::endl;
    }
};

class MyTestEnvironment2 : public testing::Environment {
public:
    void SetUp() override
    {
        std::cout << "MyTestEnvironment2 SetUp()" << std::endl;
    }

    void TearDown() override
    {
        std::cout << "MyTestEnvironment2 TearDown()" << std::endl;
    }
};

// 2) 등록하는 방법 2가지
// => 주의사항은 객체를 new로 생성해야 합니다.

// MyTestEnvironment myTestEnv;

//  1) main을 직접 정의한 경우
#if 1
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    testing::AddGlobalTestEnvironment(new MyTestEnvironment); // !!!
    testing::AddGlobalTestEnvironment(new MyTestEnvironment2); // !!!

    // testing::AddGlobalTestEnvironment(&myTestEnv); - 오류!

    return RUN_ALL_TESTS();
}
#endif

#if 0
//    2) main을 정의하지 않는 경우 - 전역 변수
//     => 전역 변수가 main 함수 이전에 초기화되는 특성을 이용합니다.
// test1.cpp
testing::Environment* myEnv = testing::AddGlobalTestEnvironment(new MyTestEnvironment);

// test2.cpp
testing::Environment* myEnv2 = testing::AddGlobalTestEnvironment(new MyTestEnvironment2);

// C++ 표준에서는 각 파일의 전역 객체의 초기화/파괴의 순서가 정의되어 있지 않습니다.

#endif

// 3. Google Test Framework - Fixture
// 1) Test Fixture
//  => 테스트케이스 단위에서의 SetUp / TearDown
//  => xUnit Test Framework

// 2) Suite Fixture
//  => 테스트스위트 단위에서의 SetUp / TearDown
//  => xUnit Test Framework

// 3) Global Fixture
//  => 프로그램 단위에서의 SetUp / TearDown
//  => Google Test Framework