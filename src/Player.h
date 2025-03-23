#pragma once

#include <string>
#include <boost/uuid/uuid.hpp>

#include "DeviceState.h"

namespace tone {
    class PlayerInfo;

    class Player {
    protected:
        DeviceState state = UNINIT;

    public:
        virtual DeviceState getDeviceState();

        virtual ~Player() = default;

        virtual std::shared_ptr<PlayerInfo> get_player_info() = 0;

        virtual void init() = 0;

        virtual void play() = 0;

        virtual void pause() = 0;

        virtual void finish() = 0;
    };

    class PlayerInfo {
        boost::uuids::uuid id;
        std::string file_name;
        uint64_t file_n_pcm_frames;
        uint64_t file_current_pcm_frame;
        u_int64_t sample_rate;

    protected:
        void set_frame_count(uint64_t frame_count);
        void set_current_pcm_frame_number(uint64_t current_frame);
        void set_sample_rate(uint64_t sample_rate);

    public:
        PlayerInfo(
            boost::uuids::uuid player_id,
            std::string file_name,
            uint64_t n_pcm_frames,
            uint64_t current_pcm_frame,
            u_int64_t sample_rate
        );

        boost::uuids::uuid get_id() const;

        std::string get_file_name() const;

        uint64_t get_number_of_pcm_frames() const;

        uint64_t get_current_pcm_frame_number() const;

        u_int64_t get_sample_rate() const;

    };
}
