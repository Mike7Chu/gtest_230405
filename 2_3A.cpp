// 2_3A.cpp
// SUT(System Under Test, 테스트 대상 시스템)
//  => CUT(Class Under Test)
//     CUT(Code Under Test)
class Calc {
public:
    double Display() { return 0; }

    double Enter(double n) { }

    void PressPlus() { }
    void PressMinus() { }
};

#include <gtest/gtest.h>
// 1. Google Test Framework
// 1) 1.8  - Google Mock 프로젝트가 흡수되었습니다.
// 2) 1.10 - 구글 테스트의 내부 용어가 xUnit Test Framework 용어가 통일되었습니다.

// 1.10 이전
//  TestCase
//    - Test
//    - Test

// 1.10 이후
//  TestSuite
//    - TestCase
//    - TestCase

// 2. 테스트케이스를 구성하는 방법
//  1) TEST(테스트스위트 이름, 테스트케이스 이름)
//   => 일반적으로 테스트 대상 클래스의 이름의 뒤에 Test/Spec를 붙이는 형태로
//      테스트 스위트를 구성합니다.
TEST(CalcTest, Plus) { }

TEST(CalcTest, Minus) { }