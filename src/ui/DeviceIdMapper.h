#pragma once
#include <map>
#include <boost/uuid/uuid.hpp>

namespace tone::ui {
    class DeviceIdMapper {
        std::map<std::string, boost::uuids::uuid> ui_to_device_id_map;
        std::map<boost::uuids::uuid, std::string> device_to_ui_id_map;

    public:
        void add_id_mapping(std::string ui_id, boost::uuids::uuid device_id);

        boost::uuids::uuid get_device_id(std::string ui_id);

        std::string get_ui_id(boost::uuids::uuid device_id);
    };
}
