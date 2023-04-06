// 10_파라미터화테스트4.cpp

#include <gtest/gtest.h>

class StringTest : public testing::TestWithParam<std::string> { };

// 1. testing::Values
// INSTANTIATE_TEST_SUITE_P(StringValues, StringTest,
//     testing::Values("Tom", "Alice", "Bob"));

// 2. testing::ValuesIn
// std::string names[] = { "Tom", "Alice", "Bob" };
// std::vector<std::string> names = { "Tom", "Alice", "Bob" };
std::vector<std::string> LoadFromFile()
{
    std::vector<std::string> names = { "Tom", "Alice", "Bob" };
    return names;
}

INSTANTIATE_TEST_SUITE_P(StringValues, StringTest,
    testing::ValuesIn(LoadFromFile()));

TEST_P(StringTest, Sample)
{
    std::cout << GetParam() << std::endl;
}