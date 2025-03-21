#include "DefaultPlayer.h"

#include <format>
#include <stdexcept>
#include <boost/uuid/uuid_generators.hpp>
#include <utility>

tone::DefaultPlayer::DefaultPlayer(
    std::string file_name,
    std::shared_ptr<ToneLogger> toneLogger
) : logger(std::move(toneLogger)),
    file_name(std::move(file_name)) {
    this->id = boost::uuids::random_generator()();
}

tone::DefaultPlayer::~DefaultPlayer() {
    if (this->state != FINISHED) {
        this->DefaultPlayer::finish();
    }
}

void tone::DefaultPlayer::play_callback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount) {
    auto *pDecoder = static_cast<ma_decoder *>(pDevice->pUserData);
    if (pDecoder == nullptr) return;
    ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, nullptr);
    (void) pInput;
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
    ma_uint64 pcm_length;
    ma_decoder_get_length_in_pcm_frames(&decoder, &pcm_length);
    u_int64_t file_length = pcm_length / decoder.outputSampleRate;
    this->player_info = std::make_shared<DefaultPlayerInfo>(id, file_name, file_length, 1);
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

std::shared_ptr<tone::PlayerInfo> tone::DefaultPlayer::get_player_info() {
    return player_info;
}

tone::DefaultPlayerInfo::DefaultPlayerInfo(
    boost::uuids::uuid player_id,
    std::string file_name,
    uint64_t file_length,
    uint64_t file_position
) : PlayerInfo(player_id, file_name, file_length, file_position) {
}
