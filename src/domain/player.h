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

    class Player {
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

        virtual ~Player();

        virtual void init();

        virtual void start();

        virtual void stop();

        virtual void unInit();

        virtual void changeFile(std::string file_name);

        virtual DeviceState getDeviceState() const;

        virtual std::shared_ptr<PlayerInfo> getPlayerInfo();
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

        friend class Player;

        boost::uuids::uuid getId() const;

        std::string getFileName() const;

        uint64_t getNumberOfPcmFrames() const;

        uint64_t getCurrentPcmFrameNumber() const;

        u_int64_t getSampleRate() const;
    };
}
