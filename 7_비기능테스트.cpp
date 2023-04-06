// 7_비기능테스트.cpp

// 1. 비기능 테스트
// 정의: 기능적인 동작뿐 아니라 성능이나 메모리 등의 비기능적인 요소를 검증합니다.

#include <unistd.h>
#include <string>

// 2초 안에 수행되어야 합니다.
bool Connect(const std::string& url)
{
    // ...
    sleep(3);
    return true;
}

#include <gtest/gtest.h>

// 사용자 정의 단언문을 만들어봅시다. => 테스트 유틸리티
// > 테스트케이스의 가독성과 유지보수성을 올릴 수 있습니다.
#define EXPECT_TIMEOUT(fn, limit)                \
    do {                                         \
        time_t startTime = time(nullptr);        \
        fn;                                      \
        time_t diff = time(nullptr) - startTime; \
        EXPECT_LE(diff, limit);                  \
    } while (0)

TEST(ConnectTest, Connect2)
{
    EXPECT_TIMEOUT(Connect("https://a.com"), 2);
}

TEST(ConnectTest, Connect)
{
    // Connect 함수가 2초 안에 수행되는지 여부를 검증하고 싶습니다.
    // ---
    time_t startTime = time(nullptr);
    Connect("https://a.com");
    time_t diff = time(nullptr) - startTime;

    EXPECT_LE(diff, 2);
    // ---
}