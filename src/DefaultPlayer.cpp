#include "DefaultPlayer.h"

#include <format>
#include <stdexcept>
#include <boost/uuid/uuid_generators.hpp>

tone::DefaultPlayer::DefaultPlayer(
    boost::uuids::uuid player_id,
    std::string file_name,
    std::shared_ptr<ToneLogger> &toneLogger
) : id(player_id),
    file_name(file_name),
    logger(toneLogger) {
}

tone::DefaultPlayer::~DefaultPlayer() {
    if (this->state != FINISHED) {
        this->DefaultPlayer::finish();
    }
}

void tone::DefaultPlayer::init() {
    if (ma_decoder_init_file(file_name.c_str(), nullptr, &decoder) != MA_SUCCESS) {
        logger->log(std::format("Failed to init decoder for file: {}", file_name));
        throw std::runtime_error("Failed to initialize file decoder!");
    }
    this->deviceConfig = ma_device_config_init(ma_device_type_playback);
    this->deviceConfig.playback.format = decoder.outputFormat;
    this->deviceConfig.playback.channels = decoder.outputChannels;
    this->deviceConfig.sampleRate = decoder.outputSampleRate;
    this->deviceConfig.dataCallback = play_callback;
    this->deviceConfig.pUserData = &decoder;
    if (ma_device_init(nullptr, &deviceConfig, &device) != MA_SUCCESS) {
        logger->log("Failed to init playback!");
        throw std::runtime_error("Failed to initialize playback device!");
    }
    logger->log("DefaultPlayer ready!");
    this->state = READY;
}


void tone::DefaultPlayer::play() {
    ma_device_start(&device);
    logger->log("Playing!");
    this->state = PLAYING;
    logger->log("Set state playing!");
}

void tone::DefaultPlayer::pause() {
    ma_device_stop(&device);
    this->state = PAUSED;
}

void tone::DefaultPlayer::finish() {
    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);
    this->state = FINISHED;
}

tone::PlayerInfo tone::DefaultPlayer::get_player_info() {
    ma_uint64 pcm_length;
    ma_decoder_get_length_in_pcm_frames(&decoder, &pcm_length);
    u_int64_t file_length = pcm_length / decoder.outputSampleRate;
    return {id, file_name, file_length, 1};
}
