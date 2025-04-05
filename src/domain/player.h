#pragma once
#include <memory>
#include <string>
#include <miniaudio.h>
#include <boost/uuid/uuid.hpp>

#include "device_state.h"
#include "logging.h"
#include "player.h"

namespace tone {
    class PlayerInfo;

    struct CallbackConfig {
        ma_decoder *decoder = nullptr;
        std::shared_ptr<PlayerInfo> player_info;
    };

    class player {
        device_state state = UN_INIT;
        std::shared_ptr<ToneLogger> logger = nullptr;
        ma_device device{};
        ma_device_config device_config{};
        ma_decoder_config decoder_config{};
        ma_decoder decoder{};
        std::shared_ptr<PlayerInfo> player_info = nullptr;
        CallbackConfig callback_config;

        static void play_callback(ma_device *p_device, void *p_output, const void *p_input, ma_uint32 frame_count);

    public:
        player(
            std::string file_name,
            std::shared_ptr<ToneLogger> tone_logger
        );

        ~player();

        void init();

        void start();

        void stop();

        void un_init();

        void change_file(std::string file_name);

        device_state get_device_state() const;

        std::shared_ptr<PlayerInfo> get_player_info();
    };

    class PlayerInfo {
        boost::uuids::uuid id;
        std::string file_name;
        uint64_t frame_count;
        uint64_t file_current_pcm_frame;
        u_int64_t sample_rate;

    public:
        PlayerInfo(
            boost::uuids::uuid player_id,
            std::string file_name,
            uint64_t number_of_pcm_frames,
            uint64_t current_pcm_frame,
            u_int64_t sample_rate
        );

        friend class player;

        boost::uuids::uuid get_id() const;

        std::string get_file_name() const;

        uint64_t get_number_of_pcm_frames() const;

        uint64_t get_current_pcm_frame_number() const;

        u_int64_t get_sample_rate() const;
    };
}
