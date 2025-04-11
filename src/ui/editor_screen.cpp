#include "editor_screen.h"

#include <map>
#include <ftxui/component/component.hpp>
#include <utility>

#include "device_id_manager.h"
#include "player_component.h"


namespace tone::ui {
    class EditorScreenBase : public ftxui::ComponentBase {
        std::shared_ptr<ILogger> logger;
        std::shared_ptr<IDeviceRepository> device_facade;
        std::shared_ptr<DeviceIdManager> device_id_mapper;
        std::map<boost::uuids::uuid, ftxui::Component> player_components;

    public:
        EditorScreenBase(
            std::shared_ptr<IDeviceRepository> device_facade,
            std::shared_ptr<DeviceIdManager> device_id_mapper,
            std::shared_ptr<ILogger> logger
        );

        ftxui::Element Render() override;
    };
}

tone::ui::EditorScreenBase::EditorScreenBase(
    std::shared_ptr<IDeviceRepository> device_facade,
    std::shared_ptr<DeviceIdManager> device_id_mapper,
    std::shared_ptr<ILogger> logger
) : logger(std::move(logger)),
    device_facade(std::move(device_facade)),
    device_id_mapper(std::move(device_id_mapper)) {
}

ftxui::Element tone::ui::EditorScreenBase::Render() {
    auto players_info = device_facade->getPlayersInfo();
    std::set<boost::uuids::uuid> current_player_ids;
    for (const auto &player_info: players_info) {
        auto player_id = player_info->getId();
        current_player_ids.insert(player_id);
        if (player_components.contains(player_id)) continue;
        auto player_ui_id = device_id_mapper->getAvailableUiId();
        auto player_component = createPlayerComponent(player_ui_id, player_info);
        player_components.insert({player_id, player_component});
        device_id_mapper->addIdMapping(player_ui_id, player_id, PLAYER);
    }
    for (const auto& player : player_components) {
        if (!current_player_ids.contains(player.first)) {
            player_components.erase(player.first);
            device_id_mapper->removeIdMappingByDeviceId(player.first);
        }
    }
    std::vector<ftxui::Element> player_elements;
    for (const auto& player: player_components) {
        player_elements.push_back(player.second->Render());
    }
    return vbox(player_elements);
}

ftxui::Component tone::ui::createEditorScreen(
    std::shared_ptr<IDeviceRepository> device_facade,
    std::shared_ptr<DeviceIdManager> device_id_mapper,
    std::shared_ptr<ILogger> logger
) {
    return ftxui::Make<EditorScreenBase>(device_facade, device_id_mapper, logger);
}
