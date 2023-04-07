// 13_Stub2.cpp
#include <string>

class Time {
public:
    virtual ~Time() { }

    virtual std::string GetCurrentTime() = 0;
};

class Clock : public Time {
public:
    std::string GetCurrentTime() override
    {
        // 현재 시간을 아래 형태로 반환합니다.
        return "09:42";
    }
};

class User {
    Time* time;

public:
    User(Time* p)
        : time(p)
    {
    }

    int Alarm()
    {
        std::string current = time->GetCurrentTime();
        if (current == "00:00") {
            return 42;
        }

        if (current == "10:00") {
            return 100;
        }

        return 0;
    }
};

//-----
#include <gtest/gtest.h>

class StubClock : public Clock {
    std::string result;

public:
    StubClock(const std::string& s)
        : result(s)
    {
    }

    std::string GetCurrentTime() override { return result; }
};

TEST(UserTest, Alarm)
{
    StubClock stub("00:00");
    User user(&stub);

    EXPECT_EQ(user.Alarm(), 42);
}

TEST(UserTest, Alarm)
{
    StubClock stub("10:00");
    User user(&stub);

    EXPECT_EQ(user.Alarm(), 100);
}