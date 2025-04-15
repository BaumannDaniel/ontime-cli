#pragma once

#include <rxcpp/rx.hpp>

namespace tone {
    class IAppStateHolder {
    public:
        virtual ~IAppStateHolder() = default;

        virtual rxcpp::observable<std::monostate> observeExit() = 0;

        virtual void exit() = 0;
    };

    class AppStateHolder : public IAppStateHolder {
        rxcpp::subjects::subject<std::monostate> exit_subject;

    public:
        rxcpp::observable<std::monostate> observeExit() override;

        void exit() override;
    };
}
