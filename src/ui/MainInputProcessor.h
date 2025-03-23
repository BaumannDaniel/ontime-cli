#pragma once
#include <memory>
#include <string>

#include "DeviceFacade.h"
#include "logging.h"

namespace tone::ui {
    struct InputCommands {
        static constexpr std::string ADD = "add";
        static constexpr std::string PLAY = "play";
        static constexpr std::string START = "start";
        static constexpr std::string STOP = "stop";
        static constexpr std::string RESET = "reset";
    };

    struct InputSubjects {
        static constexpr std::string PLAYER = "player";
    };

    class MainInputProcessor {
        std::shared_ptr<ToneLogger> logger;
        std::shared_ptr<DeviceFacade> deviceFacade;

        boost::uuids::uuid add_player(std::string file_name) const;

    public:
        MainInputProcessor(std::shared_ptr<DeviceFacade> deviceFacade, std::shared_ptr<ToneLogger> toneLogger);

        void process(std::string input) const;
    };
}
