// 6_GoogleTest2.cpp
#include <gtest/gtest.h>

// 6. 테스트 필터
// > 원하는 테스트를 선택할 수 있는 기능을 제공합니다.
// $ ./a.out --gtest_filter=ImageTest.foo:ImageTest.goo:ImageTest.hoo

// > 와일드카드도 사용할 수 있습니다.
// $ ./a.out --gtest_filter=ImageTest.*
// $ ./a.out --gtest_filter=*.foo
// $ ./a.out --gtest_filter=Image*.*

// > 제외도 가능합니다.
// $ ./a.out --gtest_filter=Image*.*:-*.goo

// - 원하는 종류의 테스트를 선택적으로 수행할 수 있습니다.
//  => 테스트케이스를 만들 때, 이름 규칙을 잘 결정하는 것이 좋습니다.
//  * 테스트의 성격에 따라서 접두를 사용했습니다.
//   P_OpenFile / N_OpenFile / X_OpenFile
//  => 가독성 뿐 아니라 필터의 기능을 활용하는데 도움이 됩니다.

// ImageTest.foo
TEST(ImageTest, foo) { }

// ImageTest.goo
TEST(ImageTest, goo) { }

// ImageTest.hoo
TEST(ImageTest, hoo) { }

TEST(ImageProcessorTest, foo) { }
TEST(ImageProcessorTest, goo) { }
TEST(ImageProcessorTest, hoo) { }

TEST(UserTest, foo) { }
TEST(UserTest, goo) { }
TEST(UserTest, hoo) { }