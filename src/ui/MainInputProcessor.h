#pragma once
#include <string>

#include "DeviceFacade.h"
#include "logging.h"

namespace tone::ui {
    struct InputCommands {
        static constexpr std::string PLAY = "play";
        static constexpr std::string START = "start";
        static constexpr std::string STOP = "stop";
    };

    class MainInputProcessor {
        ToneLogger *logger;
        DeviceFacade *deviceFacade;

    public:
        MainInputProcessor(DeviceFacade *deviceFacade, ToneLogger *toneLogger);

        void process(std::string input) const;
    };
}
