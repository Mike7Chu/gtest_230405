// 17_Mocking2.cpp
#include <gmock/gmock.h>

struct Element { }; // Dummy

class Calc {
public:
    virtual ~Calc() { }

    virtual int Add(Element x) { return 0; }
    virtual int Add(int times, Element x) { return 0; }
};

// Google Mock
// > 상속 가능한 클래스의 Mocking이 가능합니다.
class MockCalc : public Calc {
public:
};

TEST(CalcTest, Add)
{
    MockCalc mock;
}