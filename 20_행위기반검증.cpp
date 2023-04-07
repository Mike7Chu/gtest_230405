// 20_행위기반검증.cpp
#include <vector>

// 행위 기반 검증 => EXPECT_CALL
//  정의: SUT 내부에서 발생하는 함수의 호출을 통해 정상 동작 여부를 검증합니다.
//   1) 함수 호출 여부
//   2) 함수 호출 횟수
//   3) 함수 호출 인자
//   4) 함수 호출 순서

class Person {
public:
    virtual ~Person() { }

    virtual void Go(int x, int y) = 0;
    virtual void Print(const std::vector<int>& numbers) = 0;
};

//----
#include <gmock/gmock.h>

class MockPerson : public Person {
public:
    MOCK_METHOD(void, Go, (int x, int y), (override));
    MOCK_METHOD(void, Print, (const std::vector<int>& numbers), (override));
};

// 1. 함수 호출 여부
void UsePerson1(Person* p)
{
    p->Go(100, 2022);
}

TEST(PersonTest, Sample1)
{
    MockPerson mock;

    // 인자에 상관없이 Go의 호출 여부를 판단합니다.
    // EXPECT_CALL(mock, Go);

    // Go(100, 20) 호출 여부를 판단합니다.
    EXPECT_CALL(mock, Go(100, 2022));

    UsePerson1(&mock);
}

// 2. 함수 호출 횟수
//  EXPECT_CALL(mock, Go)            => 1번
//  EXPECT_CALL(mock, Go).Times(N)   => N번

//  Cardnality
using testing::AtLeast; // N번 이상
using testing::AtMost; // N번 이하
using testing::Between; // 범위

void UsePerson2(Person* p)
{
    p->Go(100, 20);
    p->Go(100, 20);
    p->Go(100, 20);
    p->Go(100, 20);
}

TEST(PersonTest, Sample2)
{
    MockPerson mock;

    // Go가 1번 호출되는지 여부를 검증합니다.
    // EXPECT_CALL(mock, Go).Times(3);
    // EXPECT_CALL(mock, Go).Times(AtLeast(2));

    EXPECT_CALL(mock, Go).Times(Between(1, 3));

    UsePerson2(&mock);
}