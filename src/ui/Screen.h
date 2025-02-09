#pragma once
#include <ftxui/component/component_base.hpp>

namespace tone::ui {
    class Screen {
    public:
        virtual ~Screen() = default;
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual ftxui::Component render() = 0;
    };
}
