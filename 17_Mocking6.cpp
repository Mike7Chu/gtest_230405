// 17_Mocking16.cpp
enum Level {
    INFO,
    WARN
};

class Logger {
public:
    virtual ~Logger() { }

    virtual void Send(
        Level level,
        const char* dir, const char* filename, int line,
        const char* message)
        = 0;
};

class User {
public:
    void Process(Logger* logger)
    {
        logger->Send(INFO, "/tmp", "user.log", 10, "user process succeed...");
    }
};
//---
#include <gmock/gmock.h>

// User.Process 함수에서 Logger에게 "/tmp", "user.log", 10 정보가 제대로 전달되어 호출되는지 여부를
// 검증하고 싶다.

// Mock 간략화.
#if 1
class MockLogger : public Logger {
public:
    // 검증하고자 하는 인자를 가진 형태로 작성합니다.
    MOCK_METHOD(void, Send, (const char* dir, const char* filename, int line));

    void Send(
        Level level,
        const char* dir, const char* filename, int line,
        const char* message) override
    {
        Send(dir, filename, line); // 핵심입니다.
    }
};

TEST(LoggerTest, Sample)
{
    MockLogger mock;
    User user;

    EXPECT_CALL(mock, Send("/tmp", "user.log", 10));

    user.Process(&mock);
}
#endif

#if 0
class MockLogger : public Logger {
public:
    // 검증하고자 하는 인자를 가진 형태로 작성합니다.
    MOCK_METHOD(void, Send, (Level level, const char* dir, const char* filename, int line, const char* message), (override));
};

TEST(LoggerTest, Sample)
{
    MockLogger mock;
    User user;

    EXPECT_CALL(mock, Send(INFO, "/tmp", "user.log", 10, "user process succeed..."));

    user.Process(&mock);
}
#endif