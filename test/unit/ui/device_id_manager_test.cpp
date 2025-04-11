#include "device_id_manager.h"

#include <boost/uuid/random_generator.hpp>
#include <gtest/gtest.h>

namespace tone::test {
    class DeviceIdManagerTest : public testing::Test {
    protected:
        ui::DeviceIdManager device_id_manager;
    };

    TEST_F(DeviceIdManagerTest, addIdMapping$addsMapping) {
        std::string ui_id = device_id_manager.getAvailableUiId();
        auto device_id = boost::uuids::random_generator()();
        auto device_type = ui::DeviceType::PLAYER;
        device_id_manager.addIdMapping(ui_id, device_id, device_type);
        auto device_id_from_ui_id = device_id_manager.getDeviceId(ui_id);
        auto ui_id_from_device_id = device_id_manager.getUiId(device_id);
        auto device_type_from_ui_id = device_id_manager.getDeviceTypeByUiId(ui_id);
        EXPECT_EQ(device_id, device_id_from_ui_id);
        EXPECT_EQ(ui_id, ui_id_from_device_id);
        EXPECT_EQ(device_type, device_type_from_ui_id);
    }

    TEST_F(DeviceIdManagerTest, removeIdMappingByDeviceId$removesMapping) {
        std::string ui_id = device_id_manager.getAvailableUiId();
        auto device_id = boost::uuids::random_generator()();
        auto device_type = ui::DeviceType::PLAYER;
        device_id_manager.addIdMapping(ui_id, device_id, device_type);
        auto device_id_from_ui_id = device_id_manager.getDeviceId(ui_id);
        auto ui_id_from_device_id = device_id_manager.getUiId(device_id);
        auto device_type_from_ui_id = device_id_manager.getDeviceTypeByUiId(ui_id);
        EXPECT_EQ(device_id, device_id_from_ui_id);
        EXPECT_EQ(ui_id, ui_id_from_device_id);
        EXPECT_EQ(device_type, device_type_from_ui_id);
    }
}
