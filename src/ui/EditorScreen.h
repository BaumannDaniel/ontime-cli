#pragma once
#include "DeviceFacade.h"
#include "logging.h"
#include "Screen.h"

namespace tone::ui {
    ftxui::Component editor_screen(std::shared_ptr<DeviceFacade> device_facade, std::shared_ptr<ToneLogger> tone_logger);
}
