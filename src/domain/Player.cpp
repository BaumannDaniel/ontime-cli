#include "Player.h"

#include <format>
#include <stdexcept>
#include <boost/uuid/uuid_generators.hpp>
#include <utility>

tone::Player::Player(
    std::string file_name,
    std::shared_ptr<ToneLogger> tone_logger
) : logger(std::move(tone_logger)){
    this->player_info = std::make_shared<PlayerInfo>(
        boost::uuids::random_generator()(),
        std::move(file_name),
        0,
        0,
        0);
}

tone::Player::~Player() {
    if (this->state != UN_INIT) {
        this->un_init();
    }
}

void tone::Player::play_callback(ma_device *p_device, void *p_output, const void *p_input, ma_uint32 frame_count) {
    auto config = static_cast<CallbackConfig *>(p_device->pUserData);
    auto *pDecoder = config->decoder;
    if (pDecoder == nullptr) return;
    ma_decoder_read_pcm_frames(pDecoder, p_output, frame_count, nullptr);
    auto player_info = config->player_info;
    ma_uint64 currentFrame;
    ma_decoder_get_cursor_in_pcm_frames(pDecoder, &currentFrame);
    player_info->file_current_pcm_frame = currentFrame;
    (void) p_input;
}


void tone::Player::init() {
    if (ma_decoder_init_file(player_info->file_name.c_str(), nullptr, &decoder) != MA_SUCCESS) {
        logger->log(std::format("Failed to init decoder for file: {}", player_info->file_name));
        throw std::runtime_error("Failed to initialize file decoder!");
    }
    this->device_config = ma_device_config_init(ma_device_type_playback);
    this->device_config.playback.format = decoder.outputFormat;
    this->device_config.playback.channels = decoder.outputChannels;
    this->device_config.sampleRate = decoder.outputSampleRate;
    this->device_config.dataCallback = play_callback;
    ma_uint64 pcm_length;
    ma_decoder_get_length_in_pcm_frames(&decoder, &pcm_length);
    this->player_info->frame_count = pcm_length;
    this->player_info->sample_rate = decoder.outputSampleRate;
    this->callback_config = {
        .decoder = &decoder,
        .player_info = player_info
    };
    this->device_config.pUserData = &callback_config;
    if (ma_device_init(nullptr, &device_config, &device) != MA_SUCCESS) {
        logger->log("Failed to init playback!");
        throw std::runtime_error("Failed to initialize playback device!");
    }
    logger->log("DefaultPlayer ready!");
    this->state = INIT;
}


void tone::Player::start() {
    ma_device_start(&device);
    logger->log("Playing!");
    this->state = STARTED;
    logger->log("Set state playing!");
}

void tone::Player::stop() {
    ma_device_stop(&device);
    this->state = STOPPED;
}

void tone::Player::un_init() {
    this->stop();
    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);
    this->player_info->file_current_pcm_frame = 0;
    this->player_info->frame_count = 0;
    this->player_info->sample_rate = 0;
    this->state = UN_INIT;
}

void tone::Player::change_file(std::string file_name) {
    this->un_init();
    this->player_info->file_name = std::move(file_name);
    this->init();
}


tone::DeviceState tone::Player::get_device_state() const {
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
    frame_count(n_pcm_frames),
    file_current_pcm_frame(current_pcm_frame),
    sample_rate(sample_rate) {
}

boost::uuids::uuid tone::PlayerInfo::get_id() const {
    return this->id;
}

std::string tone::PlayerInfo::get_file_name() const {
    return this->file_name;
}

uint64_t tone::PlayerInfo::get_number_of_pcm_frames() const {
    return this->frame_count;
}

uint64_t tone::PlayerInfo::get_current_pcm_frame_number() const {
    return this->file_current_pcm_frame;
}

u_int64_t tone::PlayerInfo::get_sample_rate() const {
    return this->sample_rate;
}