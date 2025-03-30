#pragma once
#include <ftxui/component/component_base.hpp>

#include "domain/DeviceFacade.h"
#include "DeviceIdManager.h"
#include "domain/logging.h"

namespace tone::ui {
    ftxui::Component create_editor_screen(
        std::shared_ptr<DeviceFacade> device_facade,
        std::shared_ptr<DeviceIdManager> device_id_mapper,
        std::shared_ptr<ToneLogger> tone_logger
    );
}
