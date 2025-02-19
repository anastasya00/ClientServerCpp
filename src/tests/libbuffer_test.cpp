#include <gtest/gtest.h>
#include <thread>
#include <chrono>

#include <src/libclient/libbuffer/buffer.hpp>

class BufferTest : public ::testing::Test {
    protected:
        buffer::Buffer buff;
};

TEST_F(BufferTest, TestSetData) {
    buff.setData("924999929921");
    EXPECT_TRUE(buff.getReady());
}

TEST_F(BufferTest, TestGetData) {
    std::thread writer([&]() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        buff.setData("924999929921");
    });

    std::string expected = buff.getData();
    EXPECT_EQ(expected, "924999929921");
    writer.join();
}

TEST_F(BufferTest, TestClearData) {
    buff.setData("924999929921");
    buff.clearData();
    EXPECT_FALSE(buff.getReady());
    if (buff.getReady()) {
        EXPECT_TRUE(buff.getData().empty());
    }
}