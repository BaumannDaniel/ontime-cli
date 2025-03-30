#include "MainInputProcessor.h"

#include <format>
#include <memory>
#include <utility>

#include "domain/Player.h"
#include "input.h"

tone::ui::MainInputProcessor::MainInputProcessor(
    std::shared_ptr<DeviceFacade> deviceFacade,
    std::shared_ptr<DeviceIdManager> device_id_mapper,
    std::shared_ptr<ToneLogger> toneLogger
) : logger(std::move(toneLogger)),
    deviceFacade(std::move(deviceFacade)),
    device_id_mapper(std::move(device_id_mapper)) {
}


void tone::ui::MainInputProcessor::process(std::string input) const {
    this->logger->log(std::format("MainInputProcessor - received input: {}", input));
    auto parsedInput = parseInput(std::move(input));
    if (parsedInput.empty()) return;
    if (parsedInput[0] == InputCommands::ADD) {
        if (parsedInput.size() < 3) return;
        if (parsedInput[1] == InputSubjects::PLAYER) {
            add_player(parsedInput[2]);
            return;
        }
    }
    if (parsedInput[0] == InputCommands::PLAY) {
        if (parsedInput.size() < 2) return;
        auto player_id = add_player(parsedInput[1]);
        deviceFacade->startPlayer(player_id);
        return;
    }
    if (parsedInput[0] == InputCommands::START) {
        if (parsedInput.size() < 2) return;
        const std::string& device_ui_id = parsedInput[1];
        DeviceType device_type = device_id_mapper->get_device_type_by_ui_id(device_ui_id);
        if (device_type != PLAYER) return;
        boost::uuids::uuid device_id = device_id_mapper->get_device_id(device_ui_id);
        deviceFacade->startPlayer(device_id);
    }
    if (parsedInput[0] == InputCommands::STOP) {
        if (parsedInput.size() < 2) return;
        const std::string& device_ui_id = parsedInput[1];
        DeviceType device_type = device_id_mapper->get_device_type_by_ui_id(device_ui_id);
        if (device_type != PLAYER) return;
        boost::uuids::uuid device_id = device_id_mapper->get_device_id(device_ui_id);
        deviceFacade->stopPlayer(device_id);
    }
    if (parsedInput[0] == InputCommands::REMOVE) {
        if (parsedInput.size() < 2) return;
        const std::string& device_ui_id = parsedInput[1];
        DeviceType device_type = device_id_mapper->get_device_type_by_ui_id(device_ui_id);
        if (device_type != PLAYER) return;
        boost::uuids::uuid device_id = device_id_mapper->get_device_id(device_ui_id);
        deviceFacade->removePlayer(device_id);
    }
}

boost::uuids::uuid tone::ui::MainInputProcessor::add_player(std::string file_name) const {
    auto player = std::make_shared<Player>(file_name, logger);
    deviceFacade->addPlayer(player);
    return player->get_player_info()->get_id();
}
