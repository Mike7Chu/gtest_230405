// 9_테스트전용하위클래스2.cpp
#include <iostream>

class Engine {
public:
    virtual ~Engine() { }

    virtual void Start()
    {
        std::cout << "Engine Start" << std::endl;
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
        engine->Start();
    }
};