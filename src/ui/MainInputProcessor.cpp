#include "MainInputProcessor.h"

#include <format>
#include <iostream>
#include <utility>

#include "DefaultPlayer.h"
#include "input.h"

tone::ui::MainInputProcessor::MainInputProcessor(ToneLogger *toneLogger) {
    logger = toneLogger;
}


void tone::ui::MainInputProcessor::process(std::string input) const {
    this->logger->log(std::format("Received input: {}", input));
    auto parsedInput = parseInput(std::move(input));
    if (parsedInput.empty()) return;
    if (parsedInput[0] == "play") {
        if (parsedInput.size() < 2) return;
        auto player = new DefaultPlayer(
            {
                .file = parsedInput[1]
            },
            logger
        );
        this->logger->log(parsedInput[1]);
        this->logger->log("Starting player");
        player->play();
    }
}
