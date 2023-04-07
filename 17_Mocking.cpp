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
    virtual int Go(const std::string& address) const noexcept = 0;

    // 주의 사항
    virtual std::pair<bool, int> GetPair() const = 0;
    virtual bool CheckMap(std::map<int, double> a, bool b) const = 0;
};

// 1. Google Mock 헤더를 포함해야 합니다.
//  아래의 헤더에서 자동적으로 gtest/gtest.h 에 대한 포함이 수행됩니다.
#include <gmock/gmock.h>

// 2. 테스트 대역 - 모의 객체
//  > 협력 객체의 인터페이스를 구현합니다.
class MockMP3 : public MP3 {
public:
    // MOCK_METHOD(반환타입, 이름, (인자정보, ...), (한정자, ...))
    // - override: 생략이 가능합니다.
    // -    const: 반드시 명시해야 합니다.
    // - noexcept: 반드시 명시해야 합니다.

    // void Play() override
    MOCK_METHOD(void, Play, (), (override));

    // void Stop(int n) override
    MOCK_METHOD(void, Stop, (int n), (override));

    // std::string GetTitle() const override
    MOCK_METHOD(std::string, GetTitle, (), (const, override));

    // int Go(const std::string& address) const noexcept override
    MOCK_METHOD(int, Go, (const std::string& address), (const, noexcept, override));

    // 주의 사항: 템플릿 인자가 2개 이상인 경우, 괄호가 필요합니다.
    // std::pair<bool, int> GetPair() const override
    MOCK_METHOD((std::pair<bool, int>), GetPair, (), (const, override));

    // bool CheckMap(std::map<int, double> a, bool b) const override;
    MOCK_METHOD(bool, CheckMap, ((std::map<int, double> a), bool b), (const, override));
};

TEST(MP3Test, Sample)
{
    MockMP3 mock;
}