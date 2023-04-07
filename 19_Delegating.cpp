// 19_Delegating.cpp
#include <iostream>

class Calc {
public:
    virtual ~Calc() { }

    virtual int Add(int a, int b)
    {
        std::cout << "Calc::Add" << std::endl;
        return a + b;
    }

    virtual int Sub(int a, int b)
    {
        return a - b;
    }
};

void Process(Calc* p)
{
    if (p->Add(10, 20) == 30) {
        int result = p->Sub(100, 20);
        std::cout << "Success: " << result << std::endl;
    } else {
        std::cout << "Fail" << std::endl;
    }
}

//----
#include <gmock/gmock.h>

// 1. MOCK_METHOD한 함수는 결과가 int()입니다. => 0
// 2. MOCK_METHOD한 함수에 대한 결과를 제어할 수 있습니다.
//   : ON_CALL(mock, Add(10, 20)).WillByDefault(...)
//  - 함수/함수객체/람다표현식

class MockCalc : public Calc {
public:
    MOCK_METHOD(int, Add, (int a, int b), (override));
    MOCK_METHOD(int, Sub, (int a, int b), (override));
};

using testing::Return;

int AddImpl(int a, int b) { return a + b; }

TEST(ProcessTest, Sample)
{
    MockCalc mock;
    // ON_CALL(mock, Add(10, 20)).WillByDefault(Return(30));
    // ON_CALL(mock, Sub(100, 20)).WillByDefault(Return(80));
    // ON_CALL(mock, Add).WillByDefault(AddImpl);
    ON_CALL(mock, Add).WillByDefault([](int a, int b) { return a + b; });
    ON_CALL(mock, Sub).WillByDefault([](int a, int b) { return a - b; });

    EXPECT_CALL(mock, Add(10, 20));
    EXPECT_CALL(mock, Sub(100, 20));

    // std::cout << mock.Add(10, 20) << std::endl;

    Process(&mock);
}