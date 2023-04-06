// 10_파라미터화테스트3.cpp
#include <gtest/gtest.h>

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