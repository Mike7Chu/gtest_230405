// 12_테스트대역.cpp

#include <string>

class FileSystem {
public:
    bool IsValidFilename(const std::string& filename)
    {
        // 현재의 파일 시스템에서 지원 가능한 파일 이름의 형태인지 확인합니다.
        return false; // !!
    }
};

class Logger {
public:
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

        // 현재의 파일시스템에서 가능한 이름인지 확인이 필요합니다.
        FileSystem fs;
        return fs.IsValidFilename(filename);
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

#include <gtest/gtest.h>

TEST(LoggerTest, IsValidLogFilename_NameLonggerThan5Chars_ReturnsTrue)
{
    Logger logger;
    std::string validFilename = "valid.log";

    EXPECT_TRUE(logger.IsValidLogFilename(validFilename))
        << "확장자를 제외한 파일명이 다섯글자 이상일 때";
}

TEST(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnFalse)
{
    Logger logger;
    std::string invalidFilename = "bad.log";

    EXPECT_FALSE(logger.IsValidLogFilename(invalidFilename))
        << "확장자를 제외한 파일명이 다섯글자 미만일 때";
}