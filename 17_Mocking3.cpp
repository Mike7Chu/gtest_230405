// 17_Mocking3.cpp
#include <gmock/gmock.h>

// Template Interface
template <typename T>
class StackInterface {
public:
    virtual ~StackInterface() { }

    virtual int GetSize() const = 0;
    virtual void Push(const T& x) = 0;
};

// 템플릿 기반 인터페이스/클래스에도 모의 객체를 생성할 수 있습니다.
template <typename T>
class MockStackInterface : public StackInterface<T> {
public:
    MOCK_METHOD(int, GetSize, (), (const, override));
    MOCK_METHOD(void, Push, (const T& x), (override));
};

template <typename T>
void foo(StackInterface<T>* p)
{
    // p->GetSize();
}

TEST(StackTest, Sample)
{
    MockStackInterface<int> mock;

    EXPECT_CALL(mock, GetSize);

    foo(&mock);
}