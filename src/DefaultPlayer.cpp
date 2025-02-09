#include "DefaultPlayer.h"

#include <format>
#include <stdexcept>

DefaultPlayer::DefaultPlayer(const PlayerConfig &inputFileConfig, ToneLogger *toneLogger) {
    if (ma_decoder_init_file(inputFileConfig.file.c_str(), nullptr, &decoder) != MA_SUCCESS) {
        toneLogger->log(std::format("Failed to init decoder for file: {}", inputFileConfig.file));
        throw std::runtime_error("Failed to initialize file decoder!");
    }
    this->deviceConfig = ma_device_config_init(ma_device_type_playback);
    this->deviceConfig.playback.format = decoder.outputFormat;
    this->deviceConfig.playback.channels = decoder.outputChannels;
    this->deviceConfig.sampleRate = decoder.outputSampleRate;
    this->deviceConfig.dataCallback = play_callback;
    CallbackConfig callbackConfig = {
        .decoder = &decoder,
        .logger = toneLogger
    };
    this->deviceConfig.pUserData = &decoder;
    if (ma_device_init(nullptr, &deviceConfig, &device) != MA_SUCCESS) {
        toneLogger->log("Failed to init playback!");
        throw std::runtime_error("Failed to initialize playback device!");
    }
    logger = toneLogger;
    logger->log("Device ready!");
    this->state = READY;
}

DefaultPlayer::~DefaultPlayer() {
    if (this->state != FINISHED) {
        this->DefaultPlayer::finish();
    }
}

void DefaultPlayer::play() {
    logger->log("Start playing!");
    ma_device_start(&device);
    logger->log("Playing!");
    this->state = PLAYING;
    logger->log("Set state playing!");
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
