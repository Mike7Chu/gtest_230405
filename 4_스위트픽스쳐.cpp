// 4_스위트픽스쳐.cpp
#include <string>
#include <unistd.h>

class Terminal {
public:
    // 가정: Connect / Disconnect가 느리다고 가정합니다.
    void Connect() { sleep(2); }
    void Disconnect() { sleep(2); }

    void Login(const std::string& id, const std::string& password) { }
    void Logout() { }

    bool IsLogin() const { return false; }
};

#include <gtest/gtest.h>

// 문제점: SetUp/ TearDown이 느려서(픽스쳐의 설치와 해체가 느려서)
//    테스트케이스가 추가될 때마다 전체적인 테스트의 수행 시간이 늘어나는 문제가
//    발생합니다.
//  => Slow Test 문제
//   1) 테스트가 너무 느려서, 테스트를 수행하는 개발자의 생산성을 떨어뜨립니다.
//   2) 테스트가 너무 느려서, 아무도 코드가 변경되어도 테스트를 수행하지 않습니다.

//  픽스쳐의 설치/해체로 인한 느린 테스트의 문제를 해결하는 방법
//  => 스위트 픽스쳐
//   "공유 픽스쳐 전략"
//   정의: 모든 테스트케이스가 동일한 하나의 픽스쳐를 공유합니다.
//        성능은 빠르게 동작하지만, 이전의 테스트케이스가 픽스쳐를 망가뜨리면
//        이후의 테스트의 결과를 신뢰할 수 없는 "변덕스러운 테스트" 문제가 발생할 수 있습니다.

// --- 스위트 픽스쳐 SetUp
// TerminalTest* ts = new TerminalTest;
// ts->SetUp();
// ts->TestBody();
// ts->TearDown();
// delete ts;

// TerminalTest* ts = new TerminalTest;
// ts->SetUp();
// ts->TestBody();
// ts->TearDown();
// delete ts;
// --- 스위트 픽스쳐 TearDown
#if 0
class TerminalTest : public testing::Test {
protected:
    Terminal* term = nullptr;

    // Suite Fixture
    static void SetUpTestSuite()
    {
        std::cout << "SetUpTestSuite" << std::endl;
    }

    static void TearDownTestSuite()
    {
        std::cout << "TearDownTestSuite" << std::endl;
    }

    void SetUp() override
    {
        term = new Terminal;
        term->Connect();
    }

    void TearDown() override
    {
        term->Disconnect();
        delete term;
    }
};
#endif

class TerminalTest : public testing::Test {
protected:
    static Terminal* term;

    // Suite Fixture
    // 1.10 이전
    // static void SetUpTestCase()

    // 1.10 이후
    static void SetUpTestSuite()
    {
        std::cout << "SetUpTestSuite" << std::endl;
        term = new Terminal;
        term->Connect();
    }

    // 1.10 이전
    // static void TearDownTestCase()

    // 1.10 이후
    static void TearDownTestSuite()
    {
        std::cout << "TearDownTestSuite" << std::endl;
        term->Disconnect();
        delete term;
    }

    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

Terminal* TerminalTest::term = nullptr;

TEST_F(TerminalTest, Login)
{
    term->Login("test_id", "test_password");
    ASSERT_TRUE(term->IsLogin()) << "로그인 하였을 때";
}

TEST_F(TerminalTest, Logout)
{
    term->Login("test_id", "test_password");
    term->Logout();

    ASSERT_FALSE(term->IsLogin()) << "로그아웃 하였을 때";
}

// 새로운 테스트케이스가 추가될 때마다, 느려집니다.
TEST_F(TerminalTest, Sample)
{
}

#if 0
TEST(TerminalTest, Login)
{
    Terminal* term = new Terminal;
    term->Connect();

    term->Login("test_id", "test_password");

    ASSERT_TRUE(term->IsLogin()) << "로그인 하였을 때";

    term->Disconnect();
    delete term;
}

TEST(TerminalTest, Logout)
{
    Terminal* term = new Terminal;
    term->Connect();

    term->Login("test_id", "test_password");
    term->Logout();

    ASSERT_FALSE(term->IsLogin()) << "로그아웃 하였을 때";

    term->Disconnect();
    delete term;
}
#endif