#pragma once
#include "DeviceFacade.h"
#include "DeviceIdMapper.h"
#include "logging.h"
#include "Screen.h"

namespace tone::ui {
    ftxui::Component create_editor_screen(
        std::shared_ptr<DeviceFacade> device_facade,
        std::shared_ptr<DeviceIdMapper> device_id_mapper,
        std::shared_ptr<ToneLogger> tone_logger
    );
}
