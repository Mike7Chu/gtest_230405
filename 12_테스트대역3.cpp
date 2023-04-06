// 12_테스트대역.cpp

#include <string>

// 1) 협력 객체의 인터페이스를 도입합니다.
class IFileSystem {
public:
    virtual ~IFileSystem() { }

    virtual bool IsValidFilename(const std::string& filename) = 0;
};

class FileSystem : public IFileSystem {
public:
    bool IsValidFilename(const std::string& filename) override
    {
        // 현재의 파일 시스템에서 지원 가능한 파일 이름의 형태인지 확인합니다.
        return false; // !!
    }
};

class Logger {
    IFileSystem* fs;

public:
    Logger(IFileSystem* p = nullptr)
        : fs(p)
    {
        // 기존 제품 코드가 사용하던 방식과 동일하게 사용할 수 있도록 해줍니다.
        if (fs == nullptr) {
            fs = new FileSystem; // !!!
        }
    }

    // 확장자를 제외한 파일의 이름이 5글자 이상이어야 한다.
    // ex)
    //  file.log => file  => invalid
    // hello.log => hello => valid
    bool IsValidLogFilename(const std::string& filename)
    {
        // --- 테스트 대상 코드 ---
        size_t index = filename.find_last_of(".");
        std::string name = filename.substr(0, index);
        if (name.size() < 5) {
            return false;
        }
        // --- 테스트 대상 코드 ---

        // 2) 협력 객체를 직접 생성하는 것이 아니라, 외부에서 생성해서 전달해야 합니다.
        // IFileSystem* fs = new FileSystem;
        // => 의존성 주입(Dependency Injection)
        //  1) 생성자 주입
        //   : 협력 객체가 필수적일 때
        //  2) 메소드 주입
        //   : 협력 객체가 필수적이지 않을 때

        return fs->IsValidFilename(filename);
    }
};
//-------

// 문제점
//  Logger
//    IsValidLogFilename ------X------> FileSystem.IsValidFilename
//          |
//          -----------------> TestDouble

// 테스트 대역(Test Double)
//  - 목적: 테스트 환경을 통제하기 위해서 사용합니다.
// => 테스트 대역은 무조건 적용이 불가능합니다.
//    제품의 코드가 테스트 대역을 적용할 수 있는 형태의 설계가 필요합니다.
//    "약한 결합 / 느슨한 결합"

//    강한 결합: 협력 객체를 이용할 때, 구체적인 타입에 의존합니다.
//    약한 결합: 협력 객체를 이용할 때, 구체적인 타입이 아니라,
//             추상 타입(추상 클래스, 인터페이스)에 의존합니다.

#include <gtest/gtest.h>

// 테스트 대역을 만드는 방법
// => 일반적으로 협력 객체의 인터페이스를 구현합니다.
class TestDouble : public IFileSystem {
public:
    // 무조건 성공합니다.
    bool IsValidFilename(const std::string& filename)
    {
        return true; // !!!
    }
};

TEST(LoggerTest, IsValidLogFilename_NameLonggerThan5Chars_ReturnsTrue)
{
    TestDouble testdouble;
    Logger logger(&testdouble);
    std::string validFilename = "valid.log";

    EXPECT_TRUE(logger.IsValidLogFilename(validFilename))
        << "확장자를 제외한 파일명이 다섯글자 이상일 때";
}

TEST(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnFalse)
{
    TestDouble testdouble;
    Logger logger(&testdouble);
    std::string invalidFilename = "bad.log";

    EXPECT_FALSE(logger.IsValidLogFilename(invalidFilename))
        << "확장자를 제외한 파일명이 다섯글자 미만일 때";
}

// Test Double(테스트 대역) 4가지
// 1) Test Stub
// 2) Fake Object
// 3) Test Spy
// 4) Mock Object