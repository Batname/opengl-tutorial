#include <gtest/gtest.h>
#include <iostream>

class MyString {
public:
    explicit MyString(int size) : size(size) {};
private:
    int size;
};

TEST(FOR_EACH_LOOP, Miscellanea) {
    int v1[] = { 1, 2, 3, 4 };
    bool found = false;
    
    for (auto value : v1) {
        if (value == 4) found = true;
    }
    
    EXPECT_TRUE(found);
}

TEST(EXPLICIT, Miscellanea) {
//     MyString m1 = 'B'; // error
    MyString m(10); // ok
}

TEST(STATIC_CAST, Miscellanea) {
    int i = 10.0f;
    float f = static_cast<float>(i);
    std::cout << f << std::endl;
}
