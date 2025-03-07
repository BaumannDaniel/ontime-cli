#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <miniaudio.h>

#include "logging.h"
#include "Player.h"

namespace tone {
    struct PlayerConfig {
        std::string file;
    };

    class DefaultPlayer : public Player {
        boost::uuids::uuid id;
        std::shared_ptr<ToneLogger> logger;
        std::string file_name;
        ma_device device{};
        ma_device_config deviceConfig{};
        ma_decoder_config decoderConfig{};
        ma_decoder decoder{};

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

        PlayerInfo get_player_info() override;
    };
}
