#include "main_input_processor.h"

#include <format>
#include <memory>
#include <utility>
#include <boost/algorithm/string/case_conv.hpp>

#include "player.h"
#include "input.h"

tone::ui::MainInputProcessor::MainInputProcessor(
    std::shared_ptr<IDeviceRepository> device_facade,
    std::shared_ptr<DeviceIdManager> device_id_mapper,
    std::shared_ptr<IAppStateHolder> app_state_holder,
    std::shared_ptr<ILogger> logger
) : logger(std::move(logger)),
    device_facade(std::move(device_facade)),
    device_id_mapper(std::move(device_id_mapper)),
    app_state_holder(std::move(app_state_holder)) {
}

void tone::ui::MainInputProcessor::process(std::string input) const {
    this->logger->log(std::format("MainInputProcessor - received input: {}", input));
    const auto parsedInput = parseInput(std::move(input));
    if (parsedInput.empty()) return;
    auto command = parsedInput[0];
    boost::to_lower(command);
    if (command == InputCommands::EXIT) {
        app_state_holder->exit();
        return;
    }
    if (command == InputCommands::ADD) {
        if (parsedInput.size() < 3) return;
        auto subject = parsedInput[1];
        boost::to_lower(subject);
        if (subject == InputSubjects::PLAYER) {
            addPlayer(parsedInput[2]); // NOLINT
        }
        return;
    }
    if (command == InputCommands::PLAY) {
        if (parsedInput.size() < 2) return;
        auto player_id = addPlayer(parsedInput[1]);
        device_facade->startPlayer(player_id);
        return;
    }
    if (command == InputCommands::START) {
        if (parsedInput.size() < 2) return;
        auto subject_ui_id = parsedInput[1];
        boost::to_lower(subject_ui_id);
        DeviceType device_type = device_id_mapper->getDeviceTypeByUiId(subject_ui_id).value();
        if (device_type != PLAYER) return;
        boost::uuids::uuid device_id = device_id_mapper->getDeviceId(subject_ui_id).value();
        device_facade->startPlayer(device_id);
        return;
    }
    if (command == InputCommands::STOP) {
        if (parsedInput.size() < 2) return;
        auto subject_ui_id = parsedInput[1];
        boost::to_lower(subject_ui_id);
        DeviceType device_type = device_id_mapper->getDeviceTypeByUiId(subject_ui_id).value();
        if (device_type != PLAYER) return;
        boost::uuids::uuid device_id = device_id_mapper->getDeviceId(subject_ui_id).value();
        device_facade->stopPlayer(device_id);
        return;
    }
    if (command == InputCommands::REMOVE) {
        if (parsedInput.size() < 2) return;
        auto subject_ui_id = parsedInput[1];
        boost::to_lower(subject_ui_id);
        DeviceType device_type = device_id_mapper->getDeviceTypeByUiId(subject_ui_id).value();
        if (device_type != PLAYER) return;
        boost::uuids::uuid device_id = device_id_mapper->getDeviceId(subject_ui_id).value();
        device_facade->removePlayer(device_id);
        return;
    }
    if (command == InputCommands::FILE) {
        if (parsedInput.size() < 3) return;
        auto subject_ui_id = parsedInput[1];
        boost::to_lower(subject_ui_id);
        DeviceType device_type = device_id_mapper->getDeviceTypeByUiId(subject_ui_id).value();
        if (device_type != PLAYER) return;
        boost::uuids::uuid device_id = device_id_mapper->getDeviceId(subject_ui_id).value();
        const auto &file = parsedInput[2];
        device_facade->changePlayerFile(device_id, file);
    }
}

boost::uuids::uuid tone::ui::MainInputProcessor::addPlayer(const std::string &file_name) const {
    const auto player = std::make_shared<Player>(file_name, logger);
    device_facade->addPlayer(player);
    return player->getPlayerInfo()->getId();
}
