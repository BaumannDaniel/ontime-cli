#include "device_id_manager.h"

#include <boost/uuid/random_generator.hpp>
#include <gtest/gtest.h>

namespace tone::test {
    class DeviceIdManagerTest : public testing::Test {
    protected:
        ui::DeviceIdManager device_id_manager;
    };

    TEST_F(DeviceIdManagerTest, addIdMapping$addsMapping) {
        auto ui_id = device_id_manager.getAvailableUiId().value();
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
        auto ui_id = device_id_manager.getAvailableUiId().value();
        auto device_id = boost::uuids::random_generator()();
        auto device_type = ui::DeviceType::PLAYER;
        device_id_manager.addIdMapping(ui_id, device_id, device_type);
        device_id_manager.removeIdMappingByDeviceId(device_id);
        auto device_id_from_ui_id = device_id_manager.getDeviceId(ui_id);
        auto ui_id_from_device_id = device_id_manager.getUiId(device_id);
        auto device_type_from_ui_id = device_id_manager.getDeviceTypeByUiId(ui_id);
        EXPECT_FALSE(device_id_from_ui_id.has_value());
        EXPECT_FALSE(ui_id_from_device_id.has_value());
        EXPECT_FALSE(device_type_from_ui_id.has_value());
    }

    TEST_F(DeviceIdManagerTest, getDeviceId$returnsDeviceId) {
        auto ui_id = device_id_manager.getAvailableUiId().value();
        auto device_id = boost::uuids::random_generator()();
        auto device_type = ui::DeviceType::PLAYER;
        device_id_manager.addIdMapping(ui_id, device_id, device_type);
        auto device_id_from_ui_id = device_id_manager.getDeviceId(ui_id);
        EXPECT_EQ(device_id, device_id_from_ui_id);
    }

    TEST_F(DeviceIdManagerTest, getUiId$returnsUiId) {
        auto ui_id = device_id_manager.getAvailableUiId().value();
        auto device_id = boost::uuids::random_generator()();
        auto device_type = ui::DeviceType::PLAYER;
        device_id_manager.addIdMapping(ui_id, device_id, device_type);
        auto ui_id_from_device_id = device_id_manager.getUiId(device_id);
        EXPECT_EQ(ui_id, ui_id_from_device_id);
    }

    TEST_F(DeviceIdManagerTest, getDeviceTypeByUiId$returnsDeviceType) {
        auto ui_id = device_id_manager.getAvailableUiId().value();
        auto device_id = boost::uuids::random_generator()();
        auto device_type = ui::DeviceType::PLAYER;
        device_id_manager.addIdMapping(ui_id, device_id, device_type);
        auto device_type_from_ui_id = device_id_manager.getDeviceTypeByUiId(ui_id);
        EXPECT_EQ(device_type, device_type_from_ui_id);
    }
}
