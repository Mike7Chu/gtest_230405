// 20_행위기반검증2.cpp

class Dog {
public:
    virtual ~Dog() { }

    virtual void First() = 0;
    virtual void Second() = 0;
    virtual void Third() = 0;
    virtual void Forth() = 0;
};

#include <gmock/gmock.h>

class MockDog : public Dog {
public:
    MOCK_METHOD(void, First, (), (override));
    MOCK_METHOD(void, Second, (), (override));
    MOCK_METHOD(void, Third, (), (override));
    MOCK_METHOD(void, Forth, (), (override));
};

void Process(Dog* p)
{
    p->First();
    p->Second();
    p->Third();
    p->Forth();
}

// 4. 함수 호출 순서
//  - First -> Second -> Third -> Forth
//  - InSquence
using testing::InSequence;

TEST(DogTest, Sample1)
{
    InSequence seq; // !!!
    MockDog mock;

    EXPECT_CALL(mock, First);
    EXPECT_CALL(mock, Second);
    EXPECT_CALL(mock, Forth);
    EXPECT_CALL(mock, Third);

    Process(&mock);
}