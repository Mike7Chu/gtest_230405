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

// 2) 등록하는 방법 2가지
// => 주의사항은 객체를 new로 생성해야 합니다.

// MyTestEnvironment myTestEnv;

//  1) main을 직접 정의한 경우
#if 0
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    testing::AddGlobalTestEnvironment(new MyTestEnvironment); // !!!
    testing::AddGlobalTestEnvironment(new MyTestEnvironment); // !!!

    // testing::AddGlobalTestEnvironment(&myTestEnv); - 오류!

    return RUN_ALL_TESTS();
}
#endif

//    2) main을 정의하지 않는 경우 - 전역 변수
//     => 전역 변수가 main 함수 이전에 초기화되는 특성을 이용합니다.
testing::Environment* myEnv = testing::AddGlobalTestEnvironment(new MyTestEnvironment);