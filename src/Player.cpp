#include "Player.h"

#include <utility>

tone::DeviceState tone::Player::getDeviceState() {
    return this->state;
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

