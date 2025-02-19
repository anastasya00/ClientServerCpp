#include <gtest/gtest.h>

#include <src/libhandler/handler.hpp>

class HandlerStringTest : public ::testing::Test {
    protected:
        handler::HandlerString handler_;
        std::string str = "924999929921";
};

TEST_F(HandlerStringTest, TestSortAndReplace) {
    handler_.sortAndReplace(str);
    std::string expected = "9999999КВКВКВКВ1";
    EXPECT_EQ(str, expected);
}

TEST_F(HandlerStringTest, TestCalcSumElem) {
    handler_.sortAndReplace(str);
    int expected = handler_.calcSumElem(str);
    EXPECT_EQ(expected, 64);
}

TEST_F(HandlerStringTest, TestCheckStringLength) {
    bool expected = handler_.checkStringLength("64");
    EXPECT_TRUE(expected);
}
