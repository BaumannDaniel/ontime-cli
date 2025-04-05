#include "main_input_processor.h"

#include <format>
#include <memory>
#include <utility>

#include "player.h"
#include "input.h"

tone::ui::main_input_processor::main_input_processor(
    std::shared_ptr<device_facade> device_facade,
    std::shared_ptr<device_id_manager> device_id_mapper,
    std::shared_ptr<ToneLogger> tone_logger
) : logger(std::move(tone_logger)),
    device_facade(std::move(device_facade)),
    device_id_mapper(std::move(device_id_mapper)) {
}


void tone::ui::main_input_processor::process(std::string input) const {
    this->logger->log(std::format("MainInputProcessor - received input: {}", input));
    auto parsedInput = parse_input(std::move(input));
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
        device_facade->start_player(player_id);
        return;
    }
    if (parsedInput[0] == InputCommands::START) {
        if (parsedInput.size() < 2) return;
        const std::string& device_ui_id = parsedInput[1];
        DeviceType device_type = device_id_mapper->get_device_type_by_ui_id(device_ui_id);
        if (device_type != PLAYER) return;
        boost::uuids::uuid device_id = device_id_mapper->get_device_id(device_ui_id);
        device_facade->start_player(device_id);
    }
    if (parsedInput[0] == InputCommands::STOP) {
        if (parsedInput.size() < 2) return;
        const std::string& device_ui_id = parsedInput[1];
        DeviceType device_type = device_id_mapper->get_device_type_by_ui_id(device_ui_id);
        if (device_type != PLAYER) return;
        boost::uuids::uuid device_id = device_id_mapper->get_device_id(device_ui_id);
        device_facade->stop_player(device_id);
    }
    if (parsedInput[0] == InputCommands::REMOVE) {
        if (parsedInput.size() < 2) return;
        const std::string& device_ui_id = parsedInput[1];
        DeviceType device_type = device_id_mapper->get_device_type_by_ui_id(device_ui_id);
        if (device_type != PLAYER) return;
        boost::uuids::uuid device_id = device_id_mapper->get_device_id(device_ui_id);
        device_facade->remove_player(device_id);
    }
    if (parsedInput[0] == InputCommands::FILE) {
        if (parsedInput.size() < 3) return;
        const std::string& device_ui_id = parsedInput[1];
        DeviceType device_type = device_id_mapper->get_device_type_by_ui_id(device_ui_id);
        if (device_type != PLAYER) return;
        boost::uuids::uuid device_id = device_id_mapper->get_device_id(device_ui_id);
        const auto& file = parsedInput[2];
        device_facade->change_player_file(device_id, file);
    }
}

boost::uuids::uuid tone::ui::main_input_processor::add_player(std::string file_name) const {
    auto player = std::make_shared<player>(file_name, logger);
    device_facade->add_player(player);
    return player->get_player_info()->get_id();
}
