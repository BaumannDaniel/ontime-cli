#pragma once

enum RecordingState {
    INIT,
    FAILURE,
    READY,
    STOPPED,
    PAUSED,
    RECORDING
};

class Recorder {
public:
    RecordingState state = INIT;
    virtual ~Recorder() = default;
    virtual void start() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
};
