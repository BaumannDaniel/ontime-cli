#include "app_state_holder.h"

#include <gtest/gtest.h>

namespace tone::test {
    class AppStateHolderTest : public testing::Test {
    protected:
        AppStateHolder app_state_holder;
    };

    TEST_F(AppStateHolderTest, exit$publishesExitState) {
        bool received_exit_state = false;
        app_state_holder.observeExit().subscribe([&received_exit_state](std::monostate _) {
            received_exit_state = true;
        });
        app_state_holder.exit();
        ASSERT_EQ(true, received_exit_state);
    }
}
