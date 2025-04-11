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

void tone::ui::DeviceIdManager::removeIdMappingByDeviceId(const boost::uuids::uuid& device_id) {
    const auto ui_id = getUiId(device_id);
    if (!ui_id.has_value()) return;
    ui_to_device_id_map.erase(ui_id.value());
    ui_id_to_device_type_map.erase(ui_id.value());
    device_to_ui_id_map.erase(device_id);
    available_ids.insert(ui_id.value());
}

std::optional<boost::uuids::uuid> tone::ui::DeviceIdManager::getDeviceId(const std::string& ui_id) const {
    if (!ui_id_to_device_type_map.contains(ui_id)) return {};
    return ui_to_device_id_map.at(ui_id);
}

std::optional<std::string> tone::ui::DeviceIdManager::getUiId(const boost::uuids::uuid& device_id) const {
    if (!device_to_ui_id_map.contains(device_id)) return {};
    return device_to_ui_id_map.at(device_id);
}

std::optional<std::string> tone::ui::DeviceIdManager::getAvailableUiId() const {
    return *available_ids.begin();
}

std::optional<tone::ui::DeviceType> tone::ui::DeviceIdManager::getDeviceTypeByUiId(const std::string& ui_id) const {
    if (!ui_id_to_device_type_map.contains(ui_id)) return {};
    return ui_id_to_device_type_map.at(ui_id);
}
