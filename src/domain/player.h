#pragma once
#include <memory>
#include <string>
#include <miniaudio.h>
#include <boost/uuid/uuid.hpp>
#include <atomic>

#include "device_state.h"
#include "i_player.h"
#include "logging.h"
#include "player.h"

namespace tone {
    class PlayerInfo;

    struct PlayerCallbackConfig {
        ma_decoder *decoder = nullptr;
        std::shared_ptr<PlayerInfo> player_info;
    };

    class Player : public IPlayer{
        std::mutex player_mutex;
        DeviceState state = UN_INIT;
        std::shared_ptr<ILogger> logger = nullptr;
        ma_device device{};
        ma_device_config device_config{};
        ma_decoder_config decoder_config{};
        ma_decoder decoder{};
        std::shared_ptr<PlayerInfo> player_info = nullptr;
        PlayerCallbackConfig player_callback_config;

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
        std::mutex player_info_mutex;
        const boost::uuids::uuid id;
        std::string file_name;
        std::atomic<u_int64_t> frame_count;
        std::atomic<u_int64_t> file_current_pcm_frame;
        std::atomic<u_int64_t> sample_rate;

    void setFilename(std::string file_name);

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

        std::string getFileName() override;

        uint64_t getNumberOfPcmFrames() const override;

        uint64_t getCurrentPcmFrameNumber() const override;

        u_int64_t getSampleRate() const override;
    };
}
