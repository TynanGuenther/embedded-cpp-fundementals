#include <gtest/gtest.h>
#include "raii_guard.hpp"

TEST(ScopeGuardTest, CallsCleanupOnScopeExit) {
    bool cleanupCalled = false;
    {
	ScopeGuard guard([&]() { cleanupCalled = true; });
	EXPECT_FALSE(cleanupCalled);
    }

    EXPECT_TRUE(cleanupCalled);
}

TEST(ScopeGuardTest, CallsCleanuponEarlyReturn) {
    bool cleanupCalled = false;

    auto earlyReturn = [&]() {
	ScopeGuard guard([&]() { cleanupCalled = true; });
	return;
    };

    earlyReturn();
    EXPECT_TRUE(cleanupCalled);
}
