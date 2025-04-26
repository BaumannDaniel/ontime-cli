#include "player.h"

#include <format>
#include <stdexcept>
#include <boost/uuid/uuid_generators.hpp>
#include <utility>

tone::Player::Player(
    std::string file_name,
    std::shared_ptr<ILogger> logger
) : logger(std::move(logger)),
    player_info(std::make_shared<PlayerInfo>(
            boost::uuids::random_generator()(),
            std::move(file_name),
            0,
            0,
            0)
    ) {
}

tone::Player::~Player() {
    this->Player::unInit();
}

void tone::Player::playCallback(ma_device *p_device, void *p_output, const void *p_input, ma_uint32 frame_count) {
    auto config = static_cast<PlayerCallbackConfig *>(p_device->pUserData);
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
    std::lock_guard lock(player_mutex);
    if (this->state != UN_INIT) {
        return;
    }
    if (ma_decoder_init_file(player_info->file_name.c_str(), nullptr, &decoder) != MA_SUCCESS) {
        logger->log(std::format("Failed to init decoder for file: {}", player_info->file_name));
        throw std::runtime_error("Failed to initialize file decoder!");
    }
    this->device_config = ma_device_config_init(ma_device_type_playback);
    this->device_config.playback.format = decoder.outputFormat;
    this->device_config.playback.channels = decoder.outputChannels;
    this->device_config.sampleRate = decoder.outputSampleRate;
    this->device_config.dataCallback = playCallback;
    ma_uint64 pcm_length;
    ma_decoder_get_length_in_pcm_frames(&decoder, &pcm_length);
    this->player_info->frame_count = pcm_length;
    this->player_info->sample_rate = decoder.outputSampleRate;
    this->player_callback_config = {
        .decoder = &decoder,
        .player_info = player_info
    };
    this->device_config.pUserData = &player_callback_config;
    if (ma_device_init(nullptr, &device_config, &device) != MA_SUCCESS) {
        logger->log("Failed to init playback!");
        throw std::runtime_error("Failed to initialize playback device!");
    }
    logger->log("DefaultPlayer ready!");
    this->state = INIT;
}


void tone::Player::start() {
    std::lock_guard lock(player_mutex);
    if (this->state == STARTED || this->state == UN_INIT) {
        return;
    }
    ma_device_start(&device);
    logger->log("Playing!");
    this->state = STARTED;
    logger->log("Set state playing!");
}

void tone::Player::stop() {
    std::lock_guard lock(player_mutex);
    if (this->state == STOPPED || this->state == UN_INIT) {
        return;
    }
    ma_device_stop(&device);
    this->state = STOPPED;
}

void tone::Player::unInit() {
    this->stop();
    std::lock_guard lock(player_mutex);
    if (this->state == UN_INIT) {
        return;
    }
    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);
    this->player_info->file_current_pcm_frame = 0;
    this->player_info->frame_count = 0;
    this->player_info->sample_rate = 0;
    this->state = UN_INIT;
}

void tone::Player::changeFile(std::string file_name) {
    this->unInit();
    this->player_info->setFilename(std::move(file_name));
    this->init();
}


tone::DeviceState tone::Player::getDeviceState() const {
    return this->state;
}

std::shared_ptr<tone::IPlayerInfo> tone::Player::getPlayerInfo() const {
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

void tone::PlayerInfo::setFilename(std::string file_name) {
    std::unique_lock lock(player_info_mutex);
    this->file_name = std::move(file_name);
}


boost::uuids::uuid tone::PlayerInfo::getId() const {
    return this->id;
}

std::string tone::PlayerInfo::getFileName() const {
    std::shared_lock lock(player_info_mutex);
    return this->file_name;
}

uint64_t tone::PlayerInfo::getNumberOfPcmFrames() const {
    return this->frame_count;
}

uint64_t tone::PlayerInfo::getCurrentPcmFrameNumber() const {
    return this->file_current_pcm_frame;
}

u_int64_t tone::PlayerInfo::getSampleRate() const {
    return this->sample_rate;
}
