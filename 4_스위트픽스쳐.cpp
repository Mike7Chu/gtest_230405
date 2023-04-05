// 4_스위트픽스쳐.cpp
#include <string>

class Terminal {
public:
    void Connect() { }
    void Disconnect() { }

    void Login(const std::string& id, const std::string& password) { }
    void Logout() { }

    bool IsLogin() const { return false; }
};

#include <gtest/gtest.h>

class TerminalTest : public testing::Test {
protected:
    Terminal* term = nullptr;

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