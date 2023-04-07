// 18_Mock종류.cpp
#include <string>

class Car {
public:
    virtual ~Car() { }

    virtual void Go() { }
    virtual std::string GetName() const { return "Avante"; }
};

void Go(Car* p)
{
    // ...
    p->Go();

    // ...
    p->GetName();
}

#include <gmock/gmock.h>

// > MOCK_METHOD한 메소드가 EXPECT_CALL을 하지 않았는데,
//   테스트 과정에서 호출된 경우
// Google Mock 종류
// 1) Naggy Mock(Default)
// => 테스트의 결과에 영향을 주지 않습니다.
//    관심없는 호출에 대한 경고가 발생합니다.
// GMOCK WARNING:
// Uninteresting mock function call - returning default value.
//    Function call: GetName()
//          Returns: ""

// 2) Nice Mock
// => 테스트의 결과에 영향을 주지 않고, 경고도 발생하지 않습니다.
//  : 행위 기반 검증을 수행하지 않는 목적으로 사용할 경우, 필요합니다.

// 3) Strict Mock
// => 관심 없는 호출이 발생할 경우, 테스트는 실패합니다.
//   : 엄격한 기준의 테스트를 수행할 수 있지만,
//     테스트를 작성하는 비용이 증가할 수 있습니다.

class MockCar : public Car {
public:
    MOCK_METHOD(void, Go, (), (override));
    MOCK_METHOD(std::string, GetName, (), (const, override));
};

using testing::NiceMock;
using testing::StrictMock;

TEST(CarTest, Go)
{
    // MockCar mock;
    // NiceMock<MockCar> mock;
    StrictMock<MockCar> mock;

    EXPECT_CALL(mock, Go);

    Go(&mock);
}

TEST(CarTest, GetName)
{
}
