#include "Player.h"

#include <format>
#include <stdexcept>
#include <boost/uuid/uuid_generators.hpp>
#include <utility>

tone::Player::Player(
    std::string file_name,
    std::shared_ptr<ToneLogger> toneLogger
) : logger(std::move(toneLogger)),
    file_name(std::move(file_name)) {
    this->id = boost::uuids::random_generator()();
    this->player_info = std::make_shared<PlayerInfo>(
        id,
        this->file_name,
        0,
        0,
        0);
}

tone::Player::~Player() {
    if (this->state != FINISHED) {
        this->finish();
    }
}

void tone::Player::play_callback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount) {
    auto config = static_cast<CallbackConfig *>(pDevice->pUserData);
    auto *pDecoder = config->decoder;
    if (pDecoder == nullptr) return;
    ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, nullptr);
    auto player_info = config->player_info;
    ma_uint64 currentFrame;
    ma_decoder_get_cursor_in_pcm_frames(pDecoder, &currentFrame);
    player_info->set_current_pcm_frame_number(currentFrame);
    (void) pInput;
}


void tone::Player::init() {
    if (ma_decoder_init_file(file_name.c_str(), nullptr, &decoder) != MA_SUCCESS) {
        logger->log(std::format("Failed to init decoder for file: {}", file_name));
        throw std::runtime_error("Failed to initialize file decoder!");
    }
    this->deviceConfig = ma_device_config_init(ma_device_type_playback);
    this->deviceConfig.playback.format = decoder.outputFormat;
    this->deviceConfig.playback.channels = decoder.outputChannels;
    this->deviceConfig.sampleRate = decoder.outputSampleRate;
    this->deviceConfig.dataCallback = play_callback;
    ma_uint64 pcm_length;
    ma_decoder_get_length_in_pcm_frames(&decoder, &pcm_length);
    this->player_info->set_frame_count(pcm_length);
    this->player_info->set_sample_rate(decoder.outputSampleRate);
    this->callback_config = {
        .decoder = &decoder,
        .player_info = player_info
    };
    this->deviceConfig.pUserData = &callback_config;
    if (ma_device_init(nullptr, &deviceConfig, &device) != MA_SUCCESS) {
        logger->log("Failed to init playback!");
        throw std::runtime_error("Failed to initialize playback device!");
    }
    logger->log("DefaultPlayer ready!");
    this->state = READY;
}


void tone::Player::play() {
    ma_device_start(&device);
    logger->log("Playing!");
    this->state = PLAYING;
    logger->log("Set state playing!");
}

void tone::Player::pause() {
    ma_device_stop(&device);
    this->state = PAUSED;
}

void tone::Player::finish() {
    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);
    this->state = FINISHED;
}

tone::DeviceState tone::Player::getDeviceState() const {
    return this->state;
}

std::shared_ptr<tone::PlayerInfo> tone::Player::get_player_info() {
    return player_info;
}

tone::PlayerInfo::PlayerInfo(
    boost::uuids::uuid player_id,
    std::string file_name,
    uint64_t n_pcm_frames,
    uint64_t current_pcm_frame,
    u_int64_t sample_rate
) : id(player_id),
    file_name(std::move(file_name)),
    file_n_pcm_frames(n_pcm_frames),
    file_current_pcm_frame(current_pcm_frame),
    sample_rate(sample_rate) {
}

void tone::PlayerInfo::set_current_pcm_frame_number(uint64_t current_frame) {
    this->file_current_pcm_frame = current_frame;
}

void tone::PlayerInfo::set_frame_count(uint64_t frame_count) {
    this->file_n_pcm_frames = frame_count;
}

void tone::PlayerInfo::set_sample_rate(uint64_t sample_rate) {
    this->sample_rate = sample_rate;
}

boost::uuids::uuid tone::PlayerInfo::get_id() const {
    return this->id;
}

std::string tone::PlayerInfo::get_file_name() const {
    return this->file_name;
}

uint64_t tone::PlayerInfo::get_number_of_pcm_frames() const {
    return this->file_n_pcm_frames;
}

uint64_t tone::PlayerInfo::get_current_pcm_frame_number() const {
    return this->file_current_pcm_frame;
}

u_int64_t tone::PlayerInfo::get_sample_rate() const {
    return this->sample_rate;
}