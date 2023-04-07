// 21_Hamcrest.cpp
#include <gmock/gmock.h>

// Hamcrest Mathcer
// : JUnit / TestNG 테스트 프레임워크에서 단언문을 작성할 때
//   가독성이 좋은 단언문을 작성할 수 있도록 하는
//   "비교 표현의 확장 라이브러리" 입니다.

// => Google Mock에서 단언문을 Macther 기반으로 작성할 수 있는 기능을 제공합니다.
int GetAge() { return 42; }
std::string GetMessage() { return "Hello, Google Test"; }

using namespace testing;

TEST(HamcrestTest, Sample1)
{
    EXPECT_EQ(GetAge(), 42); // !!!

    // Google Mock에서 제공하는 단언문입니다.
    EXPECT_THAT(GetAge(), Eq(42));

    EXPECT_THAT(GetMessage(), StartsWith("Hello"));
    EXPECT_THAT(GetMessage(), ContainsRegex("Google\\s+"));
}