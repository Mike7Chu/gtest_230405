// 9_테스트전용하위클래스2.cpp
#include <iostream>

class Engine {
public:
    virtual ~Engine() { }

    virtual void Start() // 가상 함수
    {
        // ...
        std::cout << "Engine Start" << std::endl;
        // ...
    }
};

class Car {
    Engine* engine;

public:
    Car(Engine* p)
        : engine(p)
    {
    }

    void Go()
    {
        // 내부 조건이 성립되면,
        // ...
        engine->Start();
    }
};

#include <gtest/gtest.h>

// Car의 Go가 호출되었을 때, Engine의 Start가 제대로 호출되었는지 여부를
// 검증하고 싶습니다.
//  > 문제점: Engine의 Start가 호출되었는지 여부를 확인할 수 있는 기능이
//          SUT에 제공되지 않습니다.
//          테스트 코드에서 단언문을 제공할 수 없습니다.
//    핵심: 가상함수 => 테스트 전용 하위 클래스 패턴을 통해 문제를 해결할 수 있습니다.
class TestEngine : public Engine {
    bool isStart = false;

public:
    void Start() override
    {
        Engine::Start(); // 부모의 기능을 그대로 호출합니다.
        // 테스트 검증을 위한 상태를 변경합니다.
        isStart = true;
    }

    bool IsStart() const { return isStart; }
};

TEST(CarTest, Engine)
{
    TestEngine engine;
    Car car(&engine);

    car.Go();

    EXPECT_TRUE(engine.IsStart()) << "Car가 Go하였을 때";
}

#if 0
TEST(CarTest, Engine)
{
    Engine engine;
    Car car(&engine);

    car.Go();
}
#endif