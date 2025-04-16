#pragma once
#include <memory>
#include <string>
#include <miniaudio.h>
#include <boost/uuid/uuid.hpp>

#include "device_state.h"
#include "i_player.h"
#include "logging.h"
#include "player.h"

namespace tone {
    class PlayerInfo;

    struct CallbackConfig {
        ma_decoder *decoder = nullptr;
        std::shared_ptr<PlayerInfo> player_info;
    };

    class Player : public IPlayer{
        DeviceState state = UN_INIT;
        std::shared_ptr<ILogger> logger = nullptr;
        ma_device device{};
        ma_device_config device_config{};
        ma_decoder_config decoder_config{};
        ma_decoder decoder{};
        std::shared_ptr<PlayerInfo> player_info = nullptr;
        CallbackConfig callback_config;

        static void playCallback(ma_device *p_device, void *p_output, const void *p_input, ma_uint32 frame_count);

    public:
        Player(
            std::string file_name,
            std::shared_ptr<ILogger> logger
        );

        ~Player() override;

        void init() override;

        void start() override;

        void stop() override;

        void unInit() override;

        void changeFile(std::string file_name) override;

        DeviceState getDeviceState() const override;

        std::shared_ptr<IPlayerInfo> getPlayerInfo() const override;
    };

    class PlayerInfo : public IPlayerInfo{
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

        friend class Player;

        boost::uuids::uuid getId() const override;

        std::string getFileName() const override;

        uint64_t getNumberOfPcmFrames() const override;

        uint64_t getCurrentPcmFrameNumber() const override;

        u_int64_t getSampleRate() const override;
    };
}
