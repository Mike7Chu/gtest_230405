// 16_Mock.cpp
#include <string>
#include <vector>

enum Level {
    INFO,
    WARN,
    ERROR
};

class DLoggerTarget {
public:
    virtual ~DLoggerTarget() { }

    virtual void Write(Level level, const std::string& message) = 0;
};

class FileTarget : public DLoggerTarget {
public:
    void Write(Level level, const std::string& message)
    {
        // 파일의 메세지를 등록합니다.
    }
};

class NetTarget : public DLoggerTarget {
public:
    void Write(Level level, const std::string& message)
    {
        // 네트워크 스트림으로 전송합니다.
    }
};

class DLogger {
    std::vector<DLoggerTarget*> targets;

public:
    void AddTarget(DLoggerTarget* p)
    {
        targets.push_back(p);
    }

    void Write(Level level, const std::string& message)
    {
        for (auto e : targets) {
            e->Write(level, message);
        }
    }
};

//------

// Mock Object Pattern
//  의도: SUT의 함수를 호출하였을 때, 발생하는 부수효과를 관찰할 수 없어서
//       테스트 되지 않은 요구사항이 존재합니다.
//  방법: 행위 기반 검증을 수행합니다.

// - 상태 검증
//  > 객체에 작용을 가한 후, 단언 함수를 통해 내부 상태값의 변화를 통해 검증을 수행합니다.
// - 동작 검증(행위 기반 검증)
//  > 객체에 작용을 가한 후, 내부적으로 발생하는 함수의 호출 여부 / 호출 순서 / 호출 횟수
//    / 호출 인자 등을 통해 정상 동작 여부를 검증합니다.
//  => 모의 객체를 위한 프레임워크를 사용합니다.
//    - Mock Framework
//    Java: jMock, EqsyMock, Mockito, Spock ..
//     C++: Google Mock

#include <gmock/gmock.h>

// 1. 모의 객체 - Mocking
class MockTarget : public DLoggerTarget {
public:
    // - MOCK_METHOD{인자개수}(함수이름, 함수타입)

    // 1.10 이전
    // MOCK_METHOD2(Write, void(Level level, const std::string& message));

    // 1.10 이후
    // => MOCK_METHOD 하나로 통일되었습니다.
    // => MOCK_METHOD(반환타입, 이름, 인자 정보, 한정자)

    // void Write(Level level, const std::string& message) override
    MOCK_METHOD(void, Write, (Level level, const std::string& message), (override));
};

TEST(DLoggerTest, Write)
{
    // Arrange
    DLogger logger;
    MockTarget t1, t2;
    logger.AddTarget(&t1);
    logger.AddTarget(&t2);
    Level testLevel = INFO;
    std::string testMessage = "test logging message";

    // Assert
    // EXPECT_CALL: 호출 여부 검증
    EXPECT_CALL(t1, Write(testLevel, testMessage));
    EXPECT_CALL(t2, Write(testLevel, testMessage));

    // Act
    logger.Write(testLevel, testMessage);

    // 주의사항: 호출되기 전에, EXPECT_CALL을 통해 검증해야 합니다.
}

#if 0
TEST(DLoggerTest, Write)
{
    // Arrange
    DLogger logger;
    SpyTarget t1, t2;
    logger.AddTarget(&t1);
    logger.AddTarget(&t2);
    Level testLevel = INFO;
    std::string testMessage = "test logging message";

    // Act
    logger.Write(testLevel, testMessage);

    // Assert
    EXPECT_TRUE(t1.IsReceived(testLevel, testMessage));
    EXPECT_TRUE(t2.IsReceived(testLevel, testMessage));
}
#endif

// 테스트 대역(Test Double) => xUnit Test Pattern
// 1. Test Stub
// => 특수한 상황을 시뮬레이션합니다.
// => 협력 객체가 SUT가 테스트하는데 필요한 결과를 주도록 제어합니다.

// 2. Fake Object
// => 가벼운 테스트 대역을 통해, 아직 구현되지 않은 사용하기 어려운, 너무 느린 협력 객체를
//    이용하는 SUT를 검증합니다.

// 3. Test Spy
// => SUT에 관찰할 수 있는 부수효과가 존재하지 않는 경우,
//    협력 객체를 통해 목격한 일을 기록해두었다가, 검증에 사용합니다.

// 4. Mock Object
// => SUT에 관찰할 수 있는 부수효과가 존재하지 않는 경우,
//    행위 기반 검증을 수행합니다.

// Google Mock => 테스트 대역 프레임워크
//  => Google Mock을 이용해서, Stub, Fake도 만들 수 있습니다.