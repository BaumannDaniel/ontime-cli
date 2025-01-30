#include "DefaultPlayer.h"

#include <stdexcept>

DefaultPlayer::DefaultPlayer(const PlayerConfig &inputFileConfig) {
    if (ma_decoder_init_file(inputFileConfig.file.c_str(), nullptr, &decoder) != MA_SUCCESS) {
        throw std::runtime_error("Failed to initialize file decoder!");
    }
    this->deviceConfig = ma_device_config_init(ma_device_type_playback);
    this->deviceConfig.playback.format = decoder.outputFormat;
    this->deviceConfig.playback.channels = decoder.outputChannels;
    this->deviceConfig.sampleRate = decoder.outputSampleRate;
    this->deviceConfig.dataCallback = play_callback;
    this->deviceConfig.pUserData = &decoder;
    if (ma_device_init(nullptr, &deviceConfig, &device) != MA_SUCCESS) {
        throw std::runtime_error("Failed to initialize playback device!");
    }
    this->state = READY;
}

DefaultPlayer::~DefaultPlayer() {
    if (this->state != FINISHED) {
        this->DefaultPlayer::finish();
    }
}

void DefaultPlayer::play() {
    ma_device_start(&device);
    this->state = PLAYING;
}

void DefaultPlayer::pause() {
    ma_device_stop(&device);
    this->state = PAUSED;
}

void DefaultPlayer::finish() {
    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);
    this->state = FINISHED;
}
