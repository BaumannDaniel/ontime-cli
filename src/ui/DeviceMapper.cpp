#include "DeviceIdMapper.h"

void tone::ui::DeviceIdMapper::add_id_mapping(std::string ui_id, boost::uuids::uuid device_id) {
    ui_to_device_id_map.insert_or_assign(ui_id, device_id);
    device_to_ui_id_map.insert_or_assign(device_id, ui_id);
}

boost::uuids::uuid tone::ui::DeviceIdMapper::get_device_id(std::string ui_id) {
    return ui_to_device_id_map.at(ui_id);
}

std::string tone::ui::DeviceIdMapper::get_ui_id(boost::uuids::uuid device_id) {
    return device_to_ui_id_map.at(device_id);
}

