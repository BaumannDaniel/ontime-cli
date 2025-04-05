#pragma once
#include <map>
#include <set>
#include <boost/uuid/uuid.hpp>

namespace tone::ui {
    enum DeviceType {
        PLAYER
    };

    class DeviceIdManager {
        std::map<std::string, boost::uuids::uuid> ui_to_device_id_map;
        std::map<boost::uuids::uuid, std::string> device_to_ui_id_map;
        std::map<std::string, DeviceType> ui_id_to_device_type_map;
        std::set<std::string> available_ids;

    public:

        DeviceIdManager();

        void add_id_mapping(std::string ui_id, boost::uuids::uuid device_id, DeviceType device_type);

        void remove_id_mapping_by_device_id(boost::uuids::uuid device_id);

        boost::uuids::uuid get_device_id(std::string ui_id);

        std::string get_ui_id(boost::uuids::uuid device_id);

        std::string get_available_ui_id();

        DeviceType get_device_type_by_ui_id(std::string ui_id);

        static constexpr u_int16_t MAX_DEVICES = 10;
    };
}
