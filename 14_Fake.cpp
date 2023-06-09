// 14_Fake.cpp
#include <string>

class User {
    std::string name;
    int age;

public:
    User(const std::string& s, int n)
        : name(s)
        , age(n)
    {
    }

    std::string GetName() const { return name; }
    int GetAge() const { return age; }
};

class IDatabase {
public:
    virtual ~IDatabase() { }

    virtual void SaveUser(const std::string& name, User* user) = 0;
    virtual User* LoadUser(const std::string& name) = 0;
};

class UserRepository {
    IDatabase* database;

public:
    UserRepository(IDatabase* p)
        : database(p)
    {
    }

    void Save(User* user)
    {
        // ...
        database->SaveUser(user->GetName(), user);
    }

    User* Load(const std::string& name)
    {
        // ...
        return database->LoadUser(name);
    }
};
//-----
#include <gtest/gtest.h>
#include <map>

// Fake Object Pattern
//  의도: 아직 준비되지 않은 협력 객체로 인해서, 테스트 되지 않은 요구사항이 존재합니다.
//  방법: 동일한 기능을 제공하는 가벼운 테스트 대역을 만들어서
//       테스트 되지 않은 요구 사항을 검증할 수 있습니다.
//    1) 협력 객체가 준비되지 않았을 때
//    2) 협력 객체가 사용하기 어려울 때
//    3) 협력 객체가 너무 느려서, 느린 테스트의 문제가 발생할 때
class FakeDatabase : public IDatabase {
    std::map<std::string, User*> data;

public:
    void SaveUser(const std::string& name, User* user) override
    {
        data[name] = user;
    }

    User* LoadUser(const std::string& name) override
    {
        return data[name];
        // return nullptr;
    }
};

bool operator==(const User& lhs, const User& rhs)
{
    return lhs.GetName() == rhs.GetName()
        && lhs.GetAge() == rhs.GetAge();
}

std::ostream& operator<<(std::ostream& os, const User& user)
{
    return os << "User{name=" << user.GetName() << ", "
              << "age=" << user.GetAge() << "}";
}

TEST(UserRepositoryTest, Save)
{
    FakeDatabase fake;
    UserRepository repo(&fake); // !!!
    std::string testName = "test_name";
    int testAge = 42;
    User expected(testName, testAge);

    repo.Save(&expected);
    User* actual = repo.Load(testName);

    ASSERT_NE(actual, nullptr); // 사전 조건 단언문
    EXPECT_EQ(expected, *actual); // ==
    // 사용자 정의 객체에 대해서 단언문을 사용하기 위해서는
    // 해당하는 연산자 재정의가 필요합니다.
    //  bool operator==(const User& lhs, const User& rhs)

    // 사용자 정의 객체를 구글 테스트의 결과를 통해
    // 제대로 확인하기 위해서는 연산자 재정의가 필요합니다.
    //  std::ostream& operator<<(std::ostream& os, const User& user)
    // User fail("Tom", 42);
    // EXPECT_EQ(expected, fail);
}

#include <gmock/gmock.h>

class MockDatabase : public IDatabase {
    std::map<std::string, User*> data;

public:
    // void SaveUser(const std::string& name, User* user) override
    MOCK_METHOD(void, SaveUser, (const std::string& name, User* user), (override));
    // User* LoadUser(const std::string& name) override
    MOCK_METHOD(User*, LoadUser, (const std::string& name), (override));
};

using testing::NiceMock;
TEST(UserRepositoryTest2, Save)
{
    NiceMock<MockDatabase> fake;
    UserRepository repo(&fake);
    std::string testName = "test_name";
    int testAge = 42;
    User expected(testName, testAge);

    std::map<std::string, User*> data;
    ON_CALL(fake, SaveUser)
        .WillByDefault([&data](const std::string& name, User* user) {
            data[name] = user;
        });
    ON_CALL(fake, LoadUser)
        .WillByDefault([&data](const std::string& name) {
            return data[name];
        });

    repo.Save(&expected);
    User* actual = repo.Load(testName);

    ASSERT_NE(actual, nullptr);
    EXPECT_EQ(expected, *actual);
}