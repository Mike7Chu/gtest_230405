// 10_파라미터화테스트3.cpp
#include <gtest/gtest.h>

// 1. tuple을 이용하는 방법
#if 0
class SampleTest : public testing::TestWithParam<std::tuple<int, std::string>> {
};

INSTANTIATE_TEST_SUITE_P(SampleValues, SampleTest,
    testing::Values(
        std::make_tuple(10, "Tom"),
        std::make_tuple(20, "Bob"),
        std::make_tuple(30, "Alice")));

TEST_P(SampleTest, Sample1)
{
    auto& param = GetParam();
    std::cout << std::get<0>(param) << ", " << std::get<1>(param) << std::endl;
    FAIL();
}
#endif

// 2. 사용자 정의 타입
class User {
    std::string name;
    int age;

public:
    User(const std::string& s, int n)
        : name(s)
        , age(n)
    {
    }

    // 사용자 정의 타입을 출력하는 연산자 오버로딩 함수를 제공해야 합니다.
    friend std::ostream& operator<<(std::ostream& os, const User& user)
    {
        return os << user.name << ", " << user.age;
    }
};

class SampleTest : public testing::TestWithParam<User> {
};

INSTANTIATE_TEST_SUITE_P(SampleValues, SampleTest,
    testing::Values(
        User("Tom", 10),
        User("Bob", 20),
        User("Alice", 30)));

TEST_P(SampleTest, Sample1)
{
    const User& param = GetParam();
    FAIL();
}