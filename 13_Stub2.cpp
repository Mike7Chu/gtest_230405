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
