#pragma once

enum PlayerState {
    INIT,
    FAILURE,
    READY,
    FINISHED,
    PAUSED,
    PLAYING
};

class Player {
public:
    PlayerState state = INIT;
    virtual ~Player() = default;
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void finish() = 0;
};
