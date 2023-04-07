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
    EXPECT_CALL(mock, Third);
    EXPECT_CALL(mock, Forth);

    Process(&mock);
}

void Process2(Dog* p)
{
    p->First();

    p->Third();
    p->Forth();

    p->Second();
}

// 4. 함수 호출 순서
//  - First -------> Second           : seq1
//          |
//          -------> Third -> Forth   : seq2
using testing::Sequence;
TEST(DogTest, Sample2)
{
    Sequence seq1, seq2;
    MockDog mock;

    EXPECT_CALL(mock, First).InSequence(seq1, seq2);
    EXPECT_CALL(mock, Second).InSequence(seq1);

    EXPECT_CALL(mock, Third).InSequence(seq2);
    EXPECT_CALL(mock, Forth).InSequence(seq2);

    Process2(&mock);
}

//---
class OnClickListener {
public:
    virtual void OnClick() = 0;
};

class MockOnClickListener : public OnClickListener {
public:
    MOCK_METHOD(void, OnClick, (), (override));
};

TEST(SampleTest, foo)
{
    // ..
}