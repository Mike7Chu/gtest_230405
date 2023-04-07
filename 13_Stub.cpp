// 13_Stub.cpp
#include <iostream>

class IConnection {
public:
    virtual ~IConnection() { }

    // ...
    virtual void Move(int x, int y) = 0;
};

class TCPConnection : public IConnection {
public:
    void Move(int x, int y) override
    {
        // TCP 패킷을 조립해서, Move의 프로토콜을 구현합니다.
    }
};

class NetworkException : public std::exception {
public:
    const char* what() const noexcept override
    {
        return "Network rror!";
    }
};

class Player {
    IConnection* conn;

public:
    Player(IConnection* p)
        : conn(p)
    {
    }

    void Move(int x, int y)
    {
        // ...
        try {
            conn->Move(x, y);
        } catch (NetworkException& e) {
            // 네트워크 오류를 핸들링합니다.
            throw e;
        }
    }
};

// Player ---X--> TCPConnection
//                StubConnection => throw NetworkException();
#include <gtest/gtest.h>
// Player의 Move를 호출하였을 때,
// Network 예외 상황에서 예외 핸들링의 코드가 제대로 동작하는지 여부를 검증하고 싶습니다.

// 문제점: 단위 테스트는 어떤 상황에서도 동일한 결과가 나와야 합니다.
#if 0
TEST(PlayerTest, Move)
{
    TCPConnection conn;
    Player player(&conn);

    EXPECT_THROW(player.Move(10, 20), NetworkException);
}
#endif

// 해결 방법
//  Test Stub Pattern
//   - 의도: '다른 컴포넌트로부터의 간접 입력'에 의존하는 로직을
//           독립적으로 검증하고 싶다.
//   - 방법: 실제 의존하는 객체를 테스트 대역으로 교체해서
//          SUT가 테스트하는데 필요한 결과를 보내도록 '제어'합니다.
//  => 특수한 상황을 시뮬레이션 하기 위해 사용합니다.

// 의존성 주입(약한 결합)
//  : 제품 코드를 사용하는 방식 그대로, 테스트 코드를 작성할 수 있습니다.

class StubConnection : public IConnection {
public:
    void Move(int x, int y) override
    {
        throw NetworkException();
    }
};

TEST(PlayerTest, Move)
{
    StubConnection conn;
    Player player(&conn);

    EXPECT_THROW(player.Move(10, 20), NetworkException);
}

#include <gmock/gmock.h>

class MockConnection : public IConnection {
public:
    MOCK_METHOD(void, Move, (int x, int y), (override));
};

using testing::NiceMock;
using testing::Throw;
TEST(PlayerTest2, Move)
{
    NiceMock<MockConnection> conn;

    ON_CALL(conn, Move).WillByDefault(Throw(NetworkException()));
    Player player(&conn);

    EXPECT_THROW(player.Move(10, 20), NetworkException);
}