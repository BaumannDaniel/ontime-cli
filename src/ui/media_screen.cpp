#include "media_screen.h"

#include <map>
#include <ftxui/component/component.hpp>
#include <utility>

#include "device_id_manager.h"
#include "player_component.h"
#include "recorder_component.h"


namespace tone::ui {
    class MediaScreenBase : public ftxui::ComponentBase {
        std::shared_ptr<ILogger> logger;
        std::shared_ptr<IDeviceRepository> device_facade;
        std::shared_ptr<DeviceIdManager> device_id_mapper;
        std::map<boost::uuids::uuid, ftxui::Component> device_components;

    public:
        MediaScreenBase(
            std::shared_ptr<IDeviceRepository> device_facade,
            std::shared_ptr<DeviceIdManager> device_id_mapper,
            std::shared_ptr<ILogger> logger
        );

        ftxui::Element Render() override;
    };
}

tone::ui::MediaScreenBase::MediaScreenBase(
    std::shared_ptr<IDeviceRepository> device_facade,
    std::shared_ptr<DeviceIdManager> device_id_mapper,
    std::shared_ptr<ILogger> logger
) : logger(std::move(logger)),
    device_facade(std::move(device_facade)),
    device_id_mapper(std::move(device_id_mapper)) {
}

ftxui::Element tone::ui::MediaScreenBase::Render() {
    auto players_info = device_facade->getPlayersInfo();
    auto recorders_info = device_facade->getRecordersInfo();
    std::set<boost::uuids::uuid> current_device_ids;
    for (const auto &player_info: players_info) {
        auto player_id = player_info->getId();
        current_device_ids.insert(player_id);
        if (device_components.contains(player_id)) continue;
        auto player_ui_id = device_id_mapper->getAvailableUiId();
        auto player_component = createPlayerComponent(player_ui_id.value(), player_info);
        device_components.insert({player_id, player_component});
        device_id_mapper->addIdMapping(player_ui_id.value(), player_id, PLAYER);
    }
    for (const auto &recorder_info: recorders_info) {
        auto recorder_id = recorder_info->getId();
        current_device_ids.insert(recorder_id);
        if (device_components.contains(recorder_id)) continue;
        auto recorder_ui_id = device_id_mapper->getAvailableUiId();
        auto recorder_component = createRecorderComponent(recorder_ui_id.value(), recorder_info);
        device_components.insert({recorder_id, recorder_component});
        device_id_mapper->addIdMapping(recorder_ui_id.value(), recorder_id, RECORDER);
    }
    for (const auto& device : device_components) {
        if (!current_device_ids.contains(device.first)) {
            device_components.erase(device.first);
            device_id_mapper->removeIdMappingByDeviceId(device.first);
        }
    }
    std::vector<ftxui::Element> player_elements;
    for (const auto& device: device_components) {
        player_elements.push_back(device.second->Render());
    }
    return vbox(player_elements);
}

ftxui::Component tone::ui::createMediaScreen(
    const std::shared_ptr<IDeviceRepository>& device_facade,
    const std::shared_ptr<DeviceIdManager>& device_id_mapper,
    const std::shared_ptr<ILogger>& logger
) {
    return ftxui::Make<MediaScreenBase>(device_facade, device_id_mapper, logger);
}
