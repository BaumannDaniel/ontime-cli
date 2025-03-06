#include "Player.h"

tone::DeviceState tone::Player::getDeviceState() {
    return this->state;
}

tone::PlayerInfo::PlayerInfo(
    boost::uuids::uuid player_id,
    std::string file_name,
    uint64_t file_length,
    uint64_t file_position
) : id(player_id),
    file_name(file_name),
    file_length(file_length),
    file_position(file_position) {
}

void tone::PlayerInfo::set_file_name(std::string file_name) {
    this->file_name = file_name;
}

void tone::PlayerInfo::set_file_length(uint64_t file_length) {
    this->file_length = file_length;
}

void tone::PlayerInfo::set_file_position(uint64_t file_position) {
    this->file_position = file_position;
}

boost::uuids::uuid tone::PlayerInfo::get_id() {
    return this->id;
}

std::string tone::PlayerInfo::get_file_name() {
    return this->file_name;
}

uint64_t tone::PlayerInfo::get_file_length() {
    return this->file_length;
}

uint64_t tone::PlayerInfo::get_file_position() {
    return this->file_position;
}
