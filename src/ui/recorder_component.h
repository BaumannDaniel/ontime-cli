#pragma once
#include <memory>
#include <string>
#include <ftxui/component/component_base.hpp>

#include "recorder_i.h"

namespace tone::ui {
    ftxui::Component createRecorderComponent(
        const std::string& ui_id,
        const std::shared_ptr<IRecorderInfo>& recorder_info
    );
}
