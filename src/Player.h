#pragma once
#include "DeviceState.h"

class Player {
public:
    DeviceState state = INIT;
    virtual ~Player() = default;
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void finish() = 0;
};
