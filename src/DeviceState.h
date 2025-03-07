#pragma once

namespace tone {
    enum DeviceState {
        UNINIT,
        FAILED,
        READY,
        FINISHED,
        PAUSED,
        RECORDING,
        PLAYING
    };
}
