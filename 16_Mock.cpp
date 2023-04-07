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
    // void Write(Level level, const std::string& message) override
    // - MOCK_METHOD{인자개수}(함수이름, 함수타입)

    MOCK_METHOD2(Write, void(Level level, const std::string& message));
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
