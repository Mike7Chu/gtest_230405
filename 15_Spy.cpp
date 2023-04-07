// 15_Spy.cpp
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
#include <gtest/gtest.h>
#include <algorithm>

// Test Spy Pattern
//  의도: SUT의 함수를 호출하였을 때, 발생하는 부수효과를 관찰할 수 없어서
//       테스트 되지 않은 요구사항이 존재합니다.
//  방법: 목격한 일을 기록해두었다가, 나중에 테스트에서 확인할 수 있도록 만들어진
//       테스트 대역
//       "다른 컴포넌트로부터의 간접 출력"을 저장해두었다가, 검증에 사용합니다.
class SpyTarget : public DLoggerTarget {
    std::vector<std::string> history;

    std::string concat(Level level, const std::string& message)
    {
        return std::to_string(level) + message;
    }

public:
    void Write(Level level, const std::string& message) override
    {
        history.push_back(concat(level, message));
    }

    bool IsReceived(Level level, const std::string& message)
    {
        return std::find(std::begin(history), std::end(history),
                   concat(level, message))
            != end(history);
    }
};

// DLogger에 대해서 Write를 하였을 때, 등록된 타겟에 제대로 Write가 수행되었는지
// 여부를 검증한다.
TEST(DLoggerTest, Write)
{
    DLogger logger;
    SpyTarget t1, t2;
    logger.AddTarget(&t1);
    logger.AddTarget(&t2);
    Level testLevel = INFO;
    std::string testMessage = "test logging message";

    logger.Write(testLevel, testMessage);

    EXPECT_TRUE(t1.IsReceived(testLevel, testMessage));
    EXPECT_TRUE(t2.IsReceived(testLevel, testMessage));
}