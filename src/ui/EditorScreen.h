#pragma once
#include "DeviceFacade.h"
#include "logging.h"
#include "Screen.h"

namespace tone::ui {
    class EditorScreen : Screen {
        std::shared_ptr<ToneLogger> logger;
        DeviceFacade *device_facade;
        ftxui::Component root_container;
    public:
        EditorScreen(DeviceFacade *device_facade, std::shared_ptr<ToneLogger> tone_logger);
        void start() override;

        void stop() override;

        ftxui::Component render() override;
    };
}
