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

        void addIdMapping(std::string ui_id, boost::uuids::uuid device_id, DeviceType device_type);

        void removeIdMappingByDeviceId(boost::uuids::uuid device_id);

        boost::uuids::uuid getDeviceId(std::string ui_id);

        std::string getUiId(boost::uuids::uuid device_id);

        std::string getAvailableUiId();

        DeviceType getDeviceTypeByUiId(std::string ui_id);

        static constexpr u_int16_t MAX_DEVICES = 10;
    };
}
