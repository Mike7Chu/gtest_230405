// 1_시작.cpp
#include <gtest/gtest.h>

// 테스트케이스를 추가하는 방법
TEST(Sample, Test1) { }

// Google Test main 함수 형태는 일정합니다.
// > libgtest.a 안에, main 함수를 포함시켜서 테스트 코드를 작성할 때
//   main을 생략할 수 있습니다.
#if 0
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif

// $ g++ 1_시작.cpp -lgtest -L. -I./googletest/googletest/include/ -pthread

// -lgtest
//  -> libgtest를 찾아서 연결해줍니다.
//     libgtest.so / libgtest.a