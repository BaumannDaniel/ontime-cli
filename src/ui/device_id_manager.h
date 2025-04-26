#pragma once
#include <map>
#include <set>
#include <shared_mutex>
#include <boost/uuid/uuid.hpp>

namespace tone::ui {
    enum DeviceType {
        PLAYER,
        RECORDER
    };

    class DeviceIdManager {
        std::shared_mutex device_id_manager_mutex;
        std::map<std::string, boost::uuids::uuid> ui_to_device_id_map;
        std::map<boost::uuids::uuid, std::string> device_to_ui_id_map;
        std::map<std::string, DeviceType> ui_id_to_device_type_map;
        std::set<std::string> available_ids;

    public:

        DeviceIdManager();

        void addIdMapping(std::string ui_id, boost::uuids::uuid device_id, DeviceType device_type);

        void removeIdMappingByDeviceId(const boost::uuids::uuid& device_id);

        std::optional<boost::uuids::uuid> getDeviceId(const std::string& ui_id) const;

        std::optional<std::string> getUiId(const boost::uuids::uuid& device_id) const;

        std::optional<std::string> getAvailableUiId() const;

        std::optional<DeviceType> getDeviceTypeByUiId(const std::string& ui_id) const;

        static constexpr u_int16_t MAX_DEVICES = 10;
    };
}
