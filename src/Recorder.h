#pragma once
#include "DeviceState.h"

class Recorder {
public:
    DeviceState state = INIT;
    virtual ~Recorder() = default;
    virtual void record() = 0;
    virtual void pause() = 0;
    virtual void finish() = 0;
};
