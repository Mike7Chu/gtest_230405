// 6_GoogleTest.cpp

// xUnit Test Framework
// 1) Fixture
// 2) Assertion
// 3) Google Test 옵션

#include <gtest/gtest.h>

int foo() { return 420; }
int goo() { return 100; }

// 1. ASSERT_
// - 단언문이 실패할 경우, 이후의 코드를 수행하지 않습니다.
//   하나의 테스트케이스 안에 여러개의 단언문이 존재할 경우
//   이후의 단언문이 수행되지 않는 문제가 있습니다.
//   "죽은 단언문"
//   > 하나의 테스트케이스 안에 여러개의 단언문을 두지 말자.(xUnit Test Pattern)
//    - "중복된 테스트 케이스가 발생하고 유지 보수 비용이 증가합니다."
//   => Google Test는 새로운 단언문을 제공합니다.
//      EXPECT_EQ / NE / LT / GT / LE / GE / TRUE / FALSE ...
TEST(SampleTest1, Sample1)
{
    // 검증
    ASSERT_EQ(42, foo());
    ASSERT_EQ(100, goo());
    ASSERT_EQ(42, foo());
    ASSERT_EQ(100, goo());
    ASSERT_EQ(42, foo());
    ASSERT_EQ(100, goo());
}

// EXPECT_XX
// - 단언문이 실패할 경우, 테스트의 결과는 실패입니다.
//   이후의 검증을 계속 수행합니다.
TEST(SampleTest, Sample2)
{
    // 검증
    EXPECT_EQ(42, foo());
    EXPECT_EQ(100, goo());
    EXPECT_EQ(42, foo());
    EXPECT_EQ(100, goo());
    EXPECT_EQ(42, foo());
    EXPECT_EQ(100, goo());
}