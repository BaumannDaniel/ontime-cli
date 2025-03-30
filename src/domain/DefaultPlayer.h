#pragma once
#include <memory>
#include <string>
#include <miniaudio.h>

#include "logging.h"
#include "Player.h"

namespace tone {
    struct PlayerConfig {
        std::string file;
    };

    class DefaultPlayerInfo;

    struct CallbackConfig {
        ma_decoder *decoder = nullptr;
        std::shared_ptr<DefaultPlayerInfo> player_info;
    };

    class DefaultPlayer : public Player {
        boost::uuids::uuid id;
        std::shared_ptr<ToneLogger> logger = nullptr;
        std::string file_name;
        ma_device device{};
        ma_device_config deviceConfig{};
        ma_decoder_config decoderConfig{};
        ma_decoder decoder{};
        std::shared_ptr<DefaultPlayerInfo> player_info = nullptr;
        CallbackConfig callback_config;

        static void play_callback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount);

    public:
        DefaultPlayer(
            std::string file_name,
            std::shared_ptr<ToneLogger> toneLogger
        );

        ~DefaultPlayer() override;

        void init() override;

        void play() override;

        void pause() override;

        void finish() override;

        std::shared_ptr<PlayerInfo> get_player_info() override;
    };

    class DefaultPlayerInfo : public PlayerInfo {
    public:
        DefaultPlayerInfo(
            boost::uuids::uuid player_id,
            std::string file_name,
            uint64_t number_of_pcm_frames,
            uint64_t current_pcm_frame,
            u_int64_t sample_rate
        );

        friend class DefaultPlayer;
    };
}
