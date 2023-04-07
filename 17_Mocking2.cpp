// 17_Mocking2.cpp
#include <gmock/gmock.h>

struct Element { }; // Dummy

class Calc {
public:
    virtual ~Calc() { }

    virtual int Add(Element x) { return 0; }
    virtual int Add(int times, Element x) { return 0; } // --> 대상
};

// Google Mock
// > 상속 가능한 클래스의 Mocking이 가능합니다.
class MockCalc : public Calc {
public:
    // 행위 기반 검증을 수행하고자 하는 함수에 대해서만 MOCK_METHOD 하면 됩니다.
    MOCK_METHOD(int, Add, (int times, Element x), (override));

    // 주의사항
    // => 행위 기반 검증을 수행하고자는 함수와 동일한 이름의 함수가 존재한다면
    //    MOCK_METHOD로 인해서 가려지는 현상이 발생합니다.
    // 해결 방법
    // => 명시적으로 동일한 이름을 가지는 함수에 대한 선언이 필요합니다.
    using Calc::Add;
};

TEST(CalcTest, Add)
{
    MockCalc mock;

    EXPECT_CALL(mock, Add); // Add 함수가 호출되었는지 여부를 검증합니다.

    // mock.Add(10, Element());
    mock.Add(Element());
}