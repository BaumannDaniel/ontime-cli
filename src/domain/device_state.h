#pragma once

namespace tone {
    enum device_state {
        UN_INIT,
        FAILED,
        INIT,
        FINISHED,
        STOPPED,
        RECORDING,
        STARTED
    };
}
