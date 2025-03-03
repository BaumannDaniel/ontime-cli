#pragma once
#include "Screen.h"

namespace tone::ui {
    class EditorScreen : Screen {
    public:
        void start() override;

        void stop() override;

        ftxui::Component render() override;
    };
}
