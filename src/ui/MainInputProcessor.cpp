#include "MainInputProcessor.h"

#include <format>
#include <iostream>
#include <memory>
#include <utility>

#include "DefaultPlayer.h"
#include "input.h"

tone::ui::MainInputProcessor::MainInputProcessor(
    std::shared_ptr<DeviceFacade> deviceFacade,
    std::shared_ptr<ToneLogger> toneLogger
) : logger(std::move(toneLogger)),
    deviceFacade(std::move(deviceFacade)) {
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
    /*if (parsedInput[0] == InputCommands::START) {
        if (parsedInput.size() < 2) return;
        uint64_t playerId = stoi(parsedInput[1]);
        deviceFacade->startPlayer(playerId);
    }
    if (parsedInput[0] == InputCommands::STOP) {
        if (parsedInput.size() < 2) return;
        uint64_t playerId = stoi(parsedInput[1]);
        deviceFacade->pausePlayer(playerId);
    }*/
}

boost::uuids::uuid tone::ui::MainInputProcessor::add_player(std::string file_name) const {
    auto player = std::make_shared<DefaultPlayer>(file_name, logger);
    deviceFacade->addPlayer(player);
    return player->get_player_info()->get_id();
}

