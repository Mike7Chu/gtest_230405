#include <gtest/gtest.h>
using namespace testing;

class TersePrinter : public EmptyTestEventListener {
private:
    // Called before any test activity starts.
    void OnTestProgramStart(const UnitTest& /* unit_test */) override { }

    // Called after all test activities have ended.
    void OnTestProgramEnd(const UnitTest& unit_test) override
    {
        fprintf(stdout, "TEST %s\n", unit_test.Passed() ? "PASSED" : "FAILED");
        fflush(stdout);
    }

    // Called before a test starts.
    void OnTestStart(const TestInfo& test_info) override
    {
        fprintf(stdout, "*** Test %s.%s starting.\n", test_info.test_suite_name(),
            test_info.name());
        fflush(stdout);
    }

    // Called after a failed assertion or a SUCCEED() invocation.
    void OnTestPartResult(const TestPartResult& test_part_result) override
    {
        fprintf(stdout, "%s in %s:%d\n%s\n",
            test_part_result.failed() ? "*** Failure" : "Success",
            test_part_result.file_name(), test_part_result.line_number(),
            test_part_result.summary());
        fflush(stdout);
    }

    // Called after a test ends.
    void OnTestEnd(const TestInfo& test_info) override
    {
        fprintf(stdout, "*** Test %s.%s ending.\n", test_info.test_suite_name(),
            test_info.name());
        fflush(stdout);
    }
};

TEST(SampleTest, foo) { }
TEST(SampleTest, goo) { }

TEST(ImageTest, foo) { }
TEST(ImageTest, goo)
{
    FAIL();
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();
    listeners.Append(new TersePrinter);

    // Google Test의 기본 프린터를 제거할 수 있습니다.
    delete listeners.Release(listeners.default_result_printer());

    return RUN_ALL_TESTS();
}
