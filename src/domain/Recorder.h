#pragma once
#include "DeviceState.h"

namespace tone {
    class Recorder {
    public:
        DeviceState state = UNINIT;
        virtual ~Recorder() = default;
        virtual void record() = 0;
        virtual void pause() = 0;
        virtual void finish() = 0;
    };
}