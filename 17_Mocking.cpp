// 17_Mocking.cpp

// Mocking: Google Mock에서 모의 객체를 만드는 방법
#include <string>
#include <map>
#include <utility>

// SUT의 협력객체의 인터페이스
class MP3 {
public:
    virtual ~MP3() { }

    virtual void Play() = 0;
    virtual void Stop(int n) = 0;

    virtual std::string GetTitle() const = 0;
    virtual int Go(const std::string& address) const noexpect = 0;
};

// 1. Google Mock 헤더를 포함해야 합니다.
//  아래의 헤더에서 자동적으로 gtest/gtest.h 에 대한 포함이 수행됩니다.
#include <gmock/gmock.h>

// 2. 테스트 대역 - 모의 객체
//  > 협력 객체의 인터페이스를 구현합니다.
class MockMP3 : public MP3 {
public:
    // MOCK_METHOD(반환타입, 이름, (인자정보, ...), (한정자, ...))
    // void Play() override
    MOCK_METHOD(void, Play, (), (override));

    // void Stop(int n) override
    MOCK_METHOD(void, Stop, (int n), (override));

    // std::string GetTitle() const override
    MOCK_METHOD(std::string, GetTitle, (), (const, override));
};

TEST(MP3Test, Sample)
{
    MockMP3 mock;
}