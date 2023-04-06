// 10_파라미터화테스트5.cpp
#include <gtest/gtest.h>

enum Color {
    RED,
    WHITE,
    BLACK
};

std::vector<std::string> cars = {
    "Sonata", "Avante", "Genesis"
};

// class CarTest : public testing::TestWithParam<std::tuple<std::string, int>> { };

using CarType = std::tuple<std::string, int>;
class CarTest : public testing::TestWithParam<CarType> { };

INSTANTIATE_TEST_SUITE_P(CarValues, CarTest,
    testing::Combine(
        testing::ValuesIn(cars),
        testing::Values(RED, WHITE, BLACK)));

TEST_P(CarTest, Sample)
{
    auto& param = GetParam();
    std::cout << std::get<0>(param) << ", " << std::get<1>(param) << std::endl;
}