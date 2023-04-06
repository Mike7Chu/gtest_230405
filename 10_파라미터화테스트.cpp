// 10_파라미터화테스트.cpp

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

// 하나의 테스트 케이스 안에 여러 개의 단언문을 작성할 경우
// => EXPECT_
TEST(PrimeTest, IsPrime1)
{
    ASSERT_TRUE(IsPrime(2));
    ASSERT_TRUE(IsPrime(3));
    ASSERT_TRUE(IsPrime(5));
    ASSERT_TRUE(IsPrime(7));
}

TEST(PrimeTest, IsPrime2)
{
    EXPECT_TRUE(IsPrime(2));
    EXPECT_TRUE(IsPrime(3));
    EXPECT_TRUE(IsPrime(5));
    EXPECT_TRUE(IsPrime(7));
    EXPECT_TRUE(IsPrime(11));
    EXPECT_TRUE(IsPrime(13));
    EXPECT_TRUE(IsPrime(17));
    // ...
}

TEST(PrimeTest, IsPrime3)
{
    int primeValues[] = { 2, 3, 5, 7, 11, 13, 17 };

    for (auto e : primeValues) {
        EXPECT_TRUE(IsPrime(e));
    }
}