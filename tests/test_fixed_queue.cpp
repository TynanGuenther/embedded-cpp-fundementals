#include <gtest/gtest.h>
#include "fixed_queue.hpp"

// ─── Basic push/pop ───────────────────────────────────────────────────────────

TEST(FixedQueueTest, PushAndPopSingleElement) {
    FixedQueue<int, 4> q;
    EXPECT_TRUE(q.push(42));

    int val = 0;
    EXPECT_TRUE(q.pop(val));
    EXPECT_EQ(val, 42);
}

TEST(FixedQueueTest, PreservesOrder) {
    FixedQueue<int, 4> q;
    q.push(1);
    q.push(2);
    q.push(3);

    int val = 0;
    q.pop(val); EXPECT_EQ(val, 1);
    q.pop(val); EXPECT_EQ(val, 2);
    q.pop(val); EXPECT_EQ(val, 3);
}

// ─── Boundary conditions ──────────────────────────────────────────────────────

TEST(FixedQueueTest, PushToFullReturnsFalse) {
    FixedQueue<int, 3> q;
    EXPECT_TRUE(q.push(1));
    EXPECT_TRUE(q.push(2));
    EXPECT_TRUE(q.push(3));
    EXPECT_FALSE(q.push(4));
}

TEST(FixedQueueTest, PopFromEmptyReturnsFalse) {
    FixedQueue<int, 4> q;
    int val = 0;
    EXPECT_FALSE(q.pop(val));
    EXPECT_EQ(val, 0);
}

TEST(FixedQueueTest, FullAndEmptyFlags) {
    FixedQueue<int, 2> q;

    EXPECT_TRUE(q.empty());
    EXPECT_FALSE(q.full());

    q.push(1);
    EXPECT_FALSE(q.empty());
    EXPECT_FALSE(q.full());

    q.push(2);
    EXPECT_FALSE(q.empty());
    EXPECT_TRUE(q.full());

    int val = 0;
    q.pop(val);
    EXPECT_FALSE(q.empty());
    EXPECT_FALSE(q.full());
}

// ─── Capacity ─────────────────────────────────────────────────────────────────

TEST(FixedQueueTest, CapacityMatchesTemplateParam) {
    FixedQueue<int, 8> q;
    EXPECT_EQ(q.capacity(), 8u);
}

TEST(FixedQueueTest, CapacityIsCompileTimeConstant) {
    FixedQueue<int, 8> q;
    // If capacity() is truly constexpr this will compile
    // If it's not, this line is a compile error
    static_assert(decltype(q)::capacity_v == 8, "capacity must be compile-time");
}

// ─── Wrap-around (the tricky one) ────────────────────────────────────────────

TEST(FixedQueueTest, WrapsAroundCorrectly) {
    FixedQueue<int, 3> q;

    q.push(1);
    q.push(2);
    q.push(3);   // full

    int val = 0;
    q.pop(val);  // pop 1, now head has wrapped
    q.push(4);   // should fill the slot left by 1

    q.pop(val); EXPECT_EQ(val, 2);
    q.pop(val); EXPECT_EQ(val, 3);
    q.pop(val); EXPECT_EQ(val, 4);
}

TEST(FixedQueueTest, FillEmptyFillAgain) {
    FixedQueue<int, 2> q;
    int val = 0;

    q.push(10); q.push(20);
    q.pop(val); q.pop(val);   // empty it completely

    EXPECT_TRUE(q.empty());
    EXPECT_TRUE(q.push(30));
    EXPECT_TRUE(q.push(40));
    EXPECT_FALSE(q.push(50));  // full again

    q.pop(val); EXPECT_EQ(val, 30);
    q.pop(val); EXPECT_EQ(val, 40);
}

// ─── Different types ──────────────────────────────────────────────────────────

TEST(FixedQueueTest, WorksWithFloat) {
    FixedQueue<float, 4> q;
    q.push(3.14f);

    float val = 0.0f;
    q.pop(val);
    EXPECT_FLOAT_EQ(val, 3.14f);
}

TEST(FixedQueueTest, WorksWithUint8) {
    FixedQueue<uint8_t, 4> q;
    q.push(255);

    uint8_t val = 0;
    q.pop(val);
    EXPECT_EQ(val, 255);
}
