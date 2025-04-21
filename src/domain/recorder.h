#pragma once
#include <string>
#include <miniaudio.h>

#include "device_state.h"
#include "logging.h"
#include "recorder_i.h"

namespace tone {
    class RecorderInfo;

    struct RecorderCallbackConfig {
        ma_encoder *encoder = nullptr;
        std::shared_ptr<RecorderInfo> recorder_info;
    };

    class Recorder : public IRecorder {
        DeviceState state = UN_INIT;
        std::shared_ptr<ILogger> logger = nullptr;
        std::shared_ptr<RecorderInfo> recorder_info = nullptr;
        ma_device device{};
        ma_device_config deviceConfig{};
        ma_encoder_config encoderConfig{};
        ma_encoder encoder{};
        RecorderCallbackConfig recorder_callback_config{};

        static void capture_callback(ma_device *p_device, void *p_output, const void *p_input, ma_uint32 frame_count);

    public:
        Recorder(
            std::string file_name,
            std::shared_ptr<ILogger> logger
        );

        ~Recorder() override;

        void init() override;

        void start() override;

        void stop() override;

        void unInit() override;

        std::shared_ptr<IRecorderInfo> getRecorderInfo() const override;
    };

    class RecorderInfo : public IRecorderInfo {
        boost::uuids::uuid id;
        std::string file_name;
        uint64_t frame_count;
        u_int64_t sample_rate;

    public:
        RecorderInfo(
            boost::uuids::uuid recorder_id,
            std::string file_name,
            uint64_t number_of_pcm_frames,
            u_int64_t sample_rate
        );

        friend class Recorder;

        boost::uuids::uuid getId() const override;

        std::string getFileName() const override;

        uint64_t getNumberOfPcmFrames() const override;

        u_int64_t getSampleRate() const override;
    };
}
