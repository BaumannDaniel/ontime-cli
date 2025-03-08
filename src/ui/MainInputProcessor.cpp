#include "MainInputProcessor.h"

#include <format>
#include <iostream>
#include <memory>
#include <utility>

#include "DefaultPlayer.h"
#include "input.h"

tone::ui::MainInputProcessor::MainInputProcessor(
    DeviceFacade *deviceFacade,
    std::shared_ptr<ToneLogger>& toneLogger
) : logger(toneLogger),
    deviceFacade(deviceFacade) {
}


void tone::ui::MainInputProcessor::process(std::string input) const {
    this->logger->log(std::format("MainInputProcessor - received input: {}", input));
    auto parsedInput = parseInput(std::move(input));
    if (parsedInput.empty()) return;
    if (parsedInput[0] == InputCommands::PLAY) {
        if (parsedInput.size() < 2) return;
        auto *player = new DefaultPlayer(
            parsedInput[1],
            logger
        );
        player->init();
        auto playerId = deviceFacade->addPlayer(player);
        deviceFacade->startPlayer(playerId);
        return;
    }
    if (parsedInput[0] == InputCommands::START) {
        if (parsedInput.size() < 2) return;
        uint64_t playerId = stoi(parsedInput[1]);
        deviceFacade->startPlayer(playerId);
    }
    if (parsedInput[0] == InputCommands::STOP) {
        if (parsedInput.size() < 2) return;
        uint64_t playerId = stoi(parsedInput[1]);
        deviceFacade->pausePlayer(playerId);
    }
}
