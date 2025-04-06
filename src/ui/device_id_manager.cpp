#include "device_id_manager.h"

tone::ui::DeviceIdManager::DeviceIdManager() {
    available_ids = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
}

void tone::ui::DeviceIdManager::addIdMapping(
    std::string ui_id,
    boost::uuids::uuid device_id,
    DeviceType device_type
) {
    available_ids.erase(ui_id);
    ui_to_device_id_map.insert_or_assign(ui_id, device_id);
    device_to_ui_id_map.insert_or_assign(device_id, ui_id);
    ui_id_to_device_type_map.insert_or_assign(ui_id, device_type);
}

void tone::ui::DeviceIdManager::removeIdMappingByDeviceId(boost::uuids::uuid device_id) {
    std::string ui_id = getUiId(device_id);
    ui_to_device_id_map.erase(ui_id);
    ui_id_to_device_type_map.erase(ui_id);
    device_to_ui_id_map.erase(device_id);
    available_ids.insert(ui_id);
}


boost::uuids::uuid tone::ui::DeviceIdManager::getDeviceId(std::string ui_id) {
    return ui_to_device_id_map.at(ui_id);
}

std::string tone::ui::DeviceIdManager::getUiId(boost::uuids::uuid device_id) {
    return device_to_ui_id_map.at(device_id);
}

std::string tone::ui::DeviceIdManager::getAvailableUiId() {
    return *available_ids.begin();
}

tone::ui::DeviceType tone::ui::DeviceIdManager::getDeviceTypeByUiId(std::string ui_id) {
    return ui_id_to_device_type_map.at(ui_id);
}
