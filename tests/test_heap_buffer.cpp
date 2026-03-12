#include <gtest/gtest.h>
#include "heap_buffer.hpp"

TEST(HeapBufferTest, CopyIsDeep) {
    HeapBuffer<int> a(4);
    // write to a, copy to b, modify a, verify b is unchanged
}

TEST(HeapBufferTest, MoveTransfersOwnership) {
    HeapBuffer<int> a(4);
    HeapBuffer<int> b = std::move(a);
    // verify a is in valid empty state
}

TEST(HeapBufferTest, SelfAssignmentDoesNotCrash) {
    HeapBuffer<int> a(4);
    a = std::move(a);   // should not crash or corrupt
}
