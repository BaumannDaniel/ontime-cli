#pragma once
#include <string>
#include <miniaudio.h>

#include "Player.h"

struct PlayerConfig {
    std::string file;
};

class DefaultPlayer : Player {
    ma_device device;
    ma_device_config deviceConfig;
    ma_decoder_config decoderConfig;
    ma_decoder decoder;

    static void play_callback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount) {
        auto *pDecoder = static_cast<ma_decoder *>(pDevice->pUserData);
        if (pDecoder == nullptr) return;
        ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, nullptr);
        (void) pInput;
    }

public:
    explicit DefaultPlayer(const PlayerConfig &inputFileConfig);

    ~DefaultPlayer() override;

    void play() override;

    void pause() override;

    void finish() override;
};
