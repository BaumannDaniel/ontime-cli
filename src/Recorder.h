#pragma once

enum RecordingState {
    INIT,
    FAILURE,
    READY,
    FINISHED,
    PAUSED,
    RECORDING
};

class Recorder {
public:
    RecordingState state = INIT;
    virtual ~Recorder() = default;
    virtual void record() = 0;
    virtual void pause() = 0;
    virtual void finish() = 0;
};
