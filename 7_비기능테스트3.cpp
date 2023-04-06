// 7_비기능테스트3.cpp
#include <iostream>
#include <string>

// $ g++ 7_비기능테스트3.cpp -lgtest -L. -I ./googletest/googletest/include/ -pthread -DGTEST_LEAK_TEST

#ifdef GTEST_LEAK_TEST
#define DECLARE_GTEST_LEAK_TEST()         \
    static int alloc;                     \
                                          \
    void* operator new(size_t size)       \
    {                                     \
        ++alloc;                          \
        return malloc(size);              \
    }                                     \
                                          \
    void operator delete(void* p, size_t) \
    {                                     \
        free(p);                          \
        --alloc;                          \
    }

#define IMPLEMENTS_GTEST_LEAK_TEST(classname) \
    int classname::alloc = 0;
#else

#define DECLARE_GTEST_LEAK_TEST()
#define IMPLEMENTS_GTEST_LEAK_TEST(classname)

#endif

//----

class Image {
    std::string url;

public:
    Image(const std::string& s)
        : url(s)
    {
    }

    void Draw() const
    {
        std::cout << "Draw Image: " << url << std::endl;
    }

    DECLARE_GTEST_LEAK_TEST()
};

IMPLEMENTS_GTEST_LEAK_TEST(Image)

void DrawImage(const std::string& url)
{
    Image* image = new Image(url);
    image->Draw();

    new Image(url);
    new Image(url);

    // delete image;
}

//----
#include <gtest/gtest.h>

// DrawImage를 수행할 때, Image 객체의 메모리 해지가
// 제대로 되는지 여부를 검증하고 싶다.
#if 0
TEST(ImageTest, DrawImage)
{
    int alloc = Image::alloc;
    DrawImage("https://a.com/a.jpg");
    int diff = Image::alloc - alloc;
    EXPECT_EQ(diff, 0) << diff << " object(s) leaked";
}
#endif

// 사용자 정의 테스트 스위트 클래스를 통해
// 메모리 누수를 검증하고자 합니다.
#if 0
class ImageTest : public testing::Test {
protected:
    int alloc = 0;
    void SetUp() override
    {
#ifdef GTEST_LEAK_TEST
        alloc = Image::alloc;
#endif
    }

    void TearDown() override
    {
#ifdef GTEST_LEAK_TEST
        int diff = Image::alloc - alloc;
        EXPECT_EQ(diff, 0) << diff << " object(s) leaked";
#endif
    }
};

TEST_F(ImageTest, DrawImage)
{
    DrawImage("https://a.com/a.jpg");
}
#endif

class LeakTest : public testing::Test {
protected:
    int alloc = 0;
    void SetUp() override
    {
#ifdef GTEST_LEAK_TEST
        alloc = Image::alloc;
#endif
    }

    void TearDown() override
    {
#ifdef GTEST_LEAK_TEST
        int diff = Image::alloc - alloc;
        EXPECT_EQ(diff, 0) << diff << " object(s) leaked";
#endif
    }
};
//----
// 주의 사항
class ImageTest : public LeakTest {
public:
    void SetUp() override
    {
        LeakTest::SetUp(); // !!
    }
    void TearDown() override
    {
        LeakTest::TearDown(); // !!
    }
};

TEST_F(ImageTest, DrawImage)
{
    DrawImage("https://a.com/a.jpg");
}