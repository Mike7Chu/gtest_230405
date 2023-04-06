// 6_GoogleTest2.cpp
#include <gtest/gtest.h>

// 6. 테스트 필터
// > 원하는 테스트를 선택할 수 있는 기능을 제공합니다.
// $ ./a.out --gtest_filter=ImageTest.foo:ImageTest.goo:ImageTest.hoo

// > 와일드카드도 사용할 수 있습니다.
// $ ./a.out --gtest_filter=ImageTest.*
// $ ./a.out --gtest_filter=*.foo

// ImageTest.foo
TEST(ImageTest, foo) { }

// ImageTest.goo
TEST(ImageTest, goo) { }

// ImageTest.hoo
TEST(ImageTest, hoo) { }

TEST(ImageProcessorTest, foo) { }
TEST(ImageProcessorTest, goo) { }
TEST(ImageProcessorTest, hoo) { }