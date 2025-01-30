#pragma once
#include <string>
#include <miniaudio.h>

#include "Player.h"

struct InputFileConfig {
    std::string file;
};

class DefaultPlayer : Player {
    ma_device device;
    ma_device_config deviceConfig;
    ma_encoder_config encoderConfig;
    ma_encoder encoder;

    static void capture_callback(ma_device *pDevice, void *_, const void *pInput, ma_uint32 frameCount) {
        auto *pEncoder = static_cast<ma_encoder *>(pDevice->pUserData);
        if (pEncoder == nullptr) return;
        ma_encoder_write_pcm_frames(pEncoder, pInput, frameCount, nullptr);
    }

public:
    explicit DefaultRecorder(const OutputFileConfig& outputFileConfig);

    ~DefaultRecorder() override;

    void record() override;

    void pause() override;

    void finish() override;
};
