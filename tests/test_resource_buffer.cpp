#include <gtest/gtest.h>
#include "resource_buffer.hpp"

TEST(ReourceBufferTest, WriteAndRead) {
    ResourceBuffer<uint8_t, 64> buf;
    EXPECT_TRUE(buf.write(0,0xFF));

    uint8_t val = 0;
    EXPECT_TRUE(buf.read(0, val));
    EXPECT_EQ(val, 0xFF);
}

TEST(ResourceBufferTest, OutOfBoundsWriteReturnsFalse) {
    ResourceBuffer<uint8_t, 64> buf;
    EXPECT_FALSE(buf.write(64, 0xFF));
}

TEST(ResourceBufferTest, OutOfBoundsReadReturnsFalse) {
    ResourceBuffer<uint8_t, 64> buf;
    uint8_t val = 0;
    EXPECT_FALSE(buf.read(64, val));
    EXPECT_EQ(val, 0);
}

TEST(ResourceBufferTest, CopyIsDeep) {
    ResourceBuffer<uint8_t, 64> a;
    a.write(0, 42);

    ResourceBuffer<uint8_t, 64> b = a;
    a.write(0, 99);

    uint8_t val = 0;
    b.read(0, val);
    EXPECT_EQ(val, 42);
}
TEST(ResourceBufferTest, MoveIsValid) {
    ResourceBuffer<uint8_t, 64> a;
    a.write(0, 42);

    ResourceBuffer<uint8_t, 64> b = std::move(a);

    uint8_t val = 0;
    b.read(0, val);
    EXPECT_EQ(val, 42);
}

TEST(ResourceBufferTest, CapacityIsCorrect) {
    ResourceBuffer<uint8_t, 64> buf;
    EXPECT_EQ(buf.capacity(), 64u);
}

TEST(ResourceBufferTest, CapacityIsCompileTimeConstant) {
    static_assert(ResourceBuffer<uint8_t, 64>::capacity() == 64, "capacity must be compile-time");
}

TEST(ResourceBufferTest, WorksWithDifferentTypes) {
    ResourceBuffer<float, 8> buf;
    EXPECT_TRUE(buf.write(0, 3.14f));

    float val = 0.0f;
    EXPECT_TRUE(buf.read(0, val));
    EXPECT_FLOAT_EQ(val, 3.14f);
}
