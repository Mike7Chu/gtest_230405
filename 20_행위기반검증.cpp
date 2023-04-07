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
    EXPECT_CALL(mock, Go(100, 20));

    UsePerson1(&mock);
}