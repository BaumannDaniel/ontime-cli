#include "device_id_manager.h"

tone::ui::device_id_manager::device_id_manager() {
    available_ids = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
}

void tone::ui::device_id_manager::add_id_mapping(
    std::string ui_id,
    boost::uuids::uuid device_id,
    DeviceType device_type
) {
    available_ids.erase(ui_id);
    ui_to_device_id_map.insert_or_assign(ui_id, device_id);
    device_to_ui_id_map.insert_or_assign(device_id, ui_id);
    ui_id_to_device_type_map.insert_or_assign(ui_id, device_type);
}

void tone::ui::device_id_manager::remove_id_mapping_by_device_id(boost::uuids::uuid device_id) {
    std::string ui_id = get_ui_id(device_id);
    ui_to_device_id_map.erase(ui_id);
    ui_id_to_device_type_map.erase(ui_id);
    device_to_ui_id_map.erase(device_id);
    available_ids.insert(ui_id);
}


boost::uuids::uuid tone::ui::device_id_manager::get_device_id(std::string ui_id) {
    return ui_to_device_id_map.at(ui_id);
}

std::string tone::ui::device_id_manager::get_ui_id(boost::uuids::uuid device_id) {
    return device_to_ui_id_map.at(device_id);
}

std::string tone::ui::device_id_manager::get_available_ui_id() {
    return *available_ids.begin();
}

tone::ui::DeviceType tone::ui::device_id_manager::get_device_type_by_ui_id(std::string ui_id) {
    return ui_id_to_device_type_map.at(ui_id);
}
