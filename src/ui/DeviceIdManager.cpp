#include "DeviceIdManager.h"

tone::ui::DeviceIdManager::DeviceIdManager() {
    available_ids = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
}

void tone::ui::DeviceIdManager::add_id_mapping(std::string ui_id, boost::uuids::uuid device_id) {
    available_ids.erase(ui_id);
    ui_to_device_id_map.insert_or_assign(ui_id, device_id);
    device_to_ui_id_map.insert_or_assign(device_id, ui_id);
}

boost::uuids::uuid tone::ui::DeviceIdManager::get_device_id(std::string ui_id) {
    return ui_to_device_id_map.at(ui_id);
}

std::string tone::ui::DeviceIdManager::get_ui_id(boost::uuids::uuid device_id) {
    return device_to_ui_id_map.at(device_id);
}

std::string tone::ui::DeviceIdManager::get_available_ui_id() {
    return *available_ids.begin();
}


