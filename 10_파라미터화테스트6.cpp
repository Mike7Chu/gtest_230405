// 10_파라미터화테스트6.cpp
#include <gtest/gtest.h>

class SampleTest : public testing::TestWithParam<int> { };

// 0 - 99
// 1) testing::Range(start, end)
//  - [start, end)

// 2) testing::Range(start, end, step)

INSTANTIATE_TEST_SUITE_P(
    SampleValues, SampleTest,
    testing::Range(0, 100, 3));

TEST_P(SampleTest, Sample)
{
    std::cout << GetParam() << std::endl;
}

//----
// 1) testing::Values
// 2) testing::ValuesIn
// 3) testing::Combine
// 4) testing::Range
