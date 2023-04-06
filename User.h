
#ifndef USER_H
#define USER_H

#include <gtest/gtest.h>

class User {
private:
    int age = 10;

    // 문제: 테스트에서 확인해야 하는 상태가
    //      private 이라서 테스트하지 못한 요구사항이 존재합니다.
    int GetAge() const { return age; }

public:
    void NextYear() { ++age; }

    //--- 핵심 코드
    FRIEND_TEST(UserTest, NextYear);
};

#endif