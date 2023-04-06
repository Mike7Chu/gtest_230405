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

int years[] = { 2010, 2020, 2030 };

// class CarTest : public testing::TestWithParam<std::tuple<std::string, int>> { };

using CarType = std::tuple<std::string, int, int>;
class CarTest : public testing::TestWithParam<CarType> { };

// testing::Combine
// => 두 개 이상의 데이터를 조합해서, 사용할 수 있습니다.

INSTANTIATE_TEST_SUITE_P(CarValues, CarTest,
    testing::Combine(
        testing::ValuesIn(cars),
        testing::Values(RED, WHITE, BLACK),
        testing::ValuesIn(years)));

TEST_P(CarTest, Sample)
{
    auto& param = GetParam();
    std::cout << std::get<0>(param)
              << ", " << std::get<1>(param)
              << ", " << std::get<2>(param)
              << std::endl;
}