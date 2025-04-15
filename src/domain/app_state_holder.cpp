#include "app_state_holder.h"

rxcpp::observable<std::monostate> tone::AppStateHolder::observeExit() {
    return exit_subject.get_observable();
}

void tone::AppStateHolder::exit() {
    exit_subject.get_subscriber().on_next(std::monostate{});
}
