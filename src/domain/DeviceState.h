#pragma once

namespace tone {
    enum DeviceState {
        UNINIT,
        FAILED,
        INIT,
        FINISHED,
        STOPPED,
        RECORDING,
        STARTED
    };
}
