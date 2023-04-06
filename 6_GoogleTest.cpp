// 6_GoogleTest.cpp

// xUnit Test Framework
// 1) Fixture
// 2) Assertion
// 3) Google Test 옵션

#include <gtest/gtest.h>

int foo() { return 42; }
int goo() { return 100; }

// 1. ASSERT_
// - 단언문이 실패할 경우, 이후의 코드를 수행하지 않습니다.
//   하나의 테스트케이스 안에 여러개의 단언문이 존재할 경우
//   이후의 단언문이 수행되지 않는 문제가 있습니다.
//   "죽은 단언문"
//   > 하나의 테스트케이스 안에 여러개의 단언문을 두지 말자.(xUnit Test Pattern)
//    - "중복된 테스트 케이스가 발생하고 유지 보수 비용이 증가합니다."
//   => Google Test는 새로운 단언문을 제공합니다.
//      EXPECT_EQ / NE / LT / GT / LE / GE / TRUE / FALSE ...
TEST(SampleTest1, Sample1)
{
    // 검증
    ASSERT_EQ(42, foo());
    ASSERT_EQ(100, goo());
    ASSERT_EQ(42, foo());
    ASSERT_EQ(100, goo());
    ASSERT_EQ(42, foo());
    ASSERT_EQ(100, goo());
}

// EXPECT_XX
// - 단언문이 실패할 경우, 테스트의 결과는 실패입니다.
//   이후의 검증을 계속 수행합니다.
TEST(SampleTest, Sample2)
{
    // 검증
    EXPECT_EQ(42, foo());
    EXPECT_EQ(100, goo());
    EXPECT_EQ(42, foo());
    EXPECT_EQ(100, goo());
    EXPECT_EQ(42, foo());
    EXPECT_EQ(100, goo());
}

//-----
class User {
    std::string name = "Tom";
    int age = 42;

public:
    std::string GetName() const { return name; }
    int GetAge() const { return age; }
};

User* GetUser() { return new User; }
// User* GetUser() { return nullptr; }

TEST(UserTest, Sample3)
{
    User* user = GetUser();

    ASSERT_NE(user, nullptr); // 사전 조건 단언문

    EXPECT_EQ(user->GetName(), "Tom");
    EXPECT_EQ(user->GetAge(), 42);
}

// 2. 문자열 비교 단언문
// => const char* / char[] 형태의 문자열 비교에서 사용해야 합니다.
// - EXPECT_STREQ / EXPECT_STRNE
// - EXPECT_STRCASEEQ / EXPECT_STRCASENE : 대소문자 무시
TEST(SampleTest2, Sample1)
{
    std::string s1 = "hello";
    std::string s2 = "hello";
    EXPECT_EQ(s1, s2);

    char s3[] = "HELLO";
    const char* s4 = "hello";
    // EXPECT_EQ(s3, s4);
    // EXPECT_STREQ(s3, s4);
    EXPECT_STRCASEEQ(s3, s4);
}

// 3. 부동소수점 비교 단언문
//  - float, double
//   EXPECT_FLOAT_EQ / EXPECT_DOUBLE_EQ

//  - 오차 범위를 직접 지정하고 싶다.
//   EXPECT_NEAR
TEST(SampleTest3, Sample1)
{
    double a = 0.7;
    double b = 0.1 * 7;

    // EXPECT_EQ(a, b);
    EXPECT_DOUBLE_EQ(a, b);
    EXPECT_NEAR(a, b, 0.00000001); // !!
}

// 4. 예외 검증을 위한 단언문을 제공합니다.
// => EXPECT_THROW: 기대한 예외가 발생하는지 여부를 검증합니다.
//    EXPECT_ANY_THROW: 예외 발생 여부를 검증합니다.
//    EXPECT_NO_THROW: 예외가 발생하지 않음을 검증합니다.
void OpenFile(const std::string filename)
{
    if (filename.empty()) {
        throw std::invalid_argument("invalid filename");
        // throw 1;
    }

    if (filename == ".") {
        throw std::bad_alloc();
    }

    // ...
}

TEST(SampleTest4, Sample2)
{
    std::string invalidFilename = "";
    std::string directory = ".";

    EXPECT_THROW(OpenFile(invalidFilename), std::invalid_argument);
    EXPECT_THROW(OpenFile(directory), std::bad_alloc);
    // EXPECT_ANY_THROW(OpenFile(invalidFilename));
    // EXPECT_NO_THROW(OpenFile(invalidFilename));
}

// 잘못된 파일 이름이 인자로 전달되었을 경우, invalid_argument 예외가
// 발생하는지 여부를 검증하고 싶다.
TEST(SampleTest4, Sample1)
{
    try {
        std::string invalidFilename = "";
        OpenFile(invalidFilename);
        FAIL() << "예외가 발생하지 않음.";
    } catch (std::invalid_argument&) {
        SUCCEED();
    } catch (...) {
        FAIL() << "기대한 예외가 다른 예외가 발생하였음.";
    }
}

// 5. 테스트 비활성화
// => 테스트의 결과에 포함되지 않지만, 비활성화된 테스트가 존재한다는 사실을
//    알려야 합니다.
// => TestSuite 이름 또는 TestCase의 이름이 DISABLED_ 접두를 가지면
//    비활성화됩니다.

TEST(SampleTest5, DISABLED_Sample1)
{
    FAIL() << "작성중입니다.";
}

TEST(DISABLED_SampleTest5, Sample2)
{
    FAIL() << "작성중입니다.";
}

class DISABLED_ImageTest : public testing::Test { };
TEST_F(DISABLED_ImageTest, BlurImage) { }
TEST_F(DISABLED_ImageTest, ResizeImage) { }

// - 작성 중인 테스트는 실패해야 합니다.
// - 테스트를 비활성화하기 위해서, 주석처리하면, "잊혀진 테스트"가 됩니다.
/*
TEST(SampleTest5, Sample)
{
    FAIL() << "작성중입니다.";
}
*/