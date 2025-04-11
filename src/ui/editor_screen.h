#pragma once
#include <ftxui/component/component_base.hpp>

#include "device_repository.h"
#include "device_id_manager.h"
#include "logging.h"

namespace tone::ui {
    ftxui::Component createEditorScreen(
        std::shared_ptr<IDeviceRepository> device_facade,
        std::shared_ptr<DeviceIdManager> device_id_mapper,
        std::shared_ptr<ILogger> tone_logger
    );
}
