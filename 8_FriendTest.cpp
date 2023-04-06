// 8_FriendTest.cpp
#include <string>

// User.h
#if 0
class User {
private:
    int age = 10;

    // 문제: 테스트에서 확인해야 하는 상태가
    //      private 이라서 테스트하지 못한 요구사항이 존재합니다.
    int GetAge() const { return age; }

public:
    void NextYear() { ++age; }
};
#endif

// 절대 사용하면 안되는 방법입니다.
#if 0
#define private public
#define class struct
#include "User.h"
#undef private
#undef class
#endif

#include <gtest/gtest.h>
#include "User.h"

// Friend Test
// => C++의 friend 기능을 이용해서
//    특정한 테스트케이스가 SUT의 private에
//    접근할 수 있습니다.
// => SUT에 Google Test 프레임워크에 대한
//    의존성이 생깁니다.

// Clean Code
// 1. 제품 코드는 테스트가 용이해야 합니다.
//   "테스트 용이성"
// 2. 테스트되지 않은 private 메소드보다
//    테스트된 public 메소드가 안전하다.
// 3. private 메소드
//  > private 메소드는 public 메소드의 가독성을 높이기
//    위해 사용해야 한다.
//    public 메소드를 검증하면, private 메소드도
//    자연스럽게 검증될 것이다.

TEST(UserTest, NextYear)
{
    User user;

    user.NextYear();

    EXPECT_EQ(user.GetAge(), 11);
}