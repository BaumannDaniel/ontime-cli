#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "config.h" // NOLINT
#include "main_input_processor.h"


#include "device_id_manager.h"
#include "player.h"
#include "../util/device_facade_mock.h"
#include "../util/logger_mock.h"

namespace tone::test {
    class MainInputProcessorTest : public testing::Test {
    protected:
        std::shared_ptr<ui::DeviceIdManager> device_id_manager;
        std::shared_ptr<MockLogger> logger;
        std::shared_ptr<MockDeviceFacade> device_facade;
        ui::MainInputProcessor main_input_processor;

        MainInputProcessorTest()
            : device_id_manager(std::make_shared<ui::DeviceIdManager>()),
              logger(std::make_shared<MockLogger>()),
              device_facade(std::make_shared<MockDeviceFacade>()),
              main_input_processor(
                  ui::MainInputProcessor(device_facade, device_id_manager, logger)
              ) {
        }
    };

    TEST_F(MainInputProcessorTest, process000addsPlayerToDeviceFacade) {
        std::string input = "add player /testPath/test.mp3";
        auto facade = device_facade.get();
        EXPECT_CALL(*facade, addPlayer(testing::_)).Times(1);
        main_input_processor.process(input);
    }
}
