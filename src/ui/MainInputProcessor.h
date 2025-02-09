#pragma once
#include <string>

#include "logging.h"

namespace tone::ui {
    class MainInputProcessor {
        ToneLogger *logger;

    public:
        explicit MainInputProcessor(ToneLogger *toneLogger);

        void process(std::string input) const;
    };
}
