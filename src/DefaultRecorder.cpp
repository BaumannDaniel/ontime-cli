#include "DefaultRecorder.h"

#include <stdexcept>

DefaultRecorder::DefaultRecorder(const OutputFileConfig &outputFileConfig) {
    this->encoderConfig = ma_encoder_config_init(
                              ma_encoding_format_wav,
                              ma_format_f32,
                              2,
                              44100
                          );
    if (ma_encoder_init_file(outputFileConfig.file.c_str(), &encoderConfig, &encoder) != MA_SUCCESS) {
        throw std::runtime_error("Failed to intitialize file encoder!");
    }
    this->deviceConfig = ma_device_config_init(ma_device_type_capture);
    this->deviceConfig.capture.format = encoder.config.format;
    this->deviceConfig.capture.channels = encoder.config.channels;
    this->deviceConfig.sampleRate = encoder.config.sampleRate;
    this->deviceConfig.dataCallback = capture_callback;
    this->deviceConfig.pUserData = &encoder;
    if (ma_device_init(nullptr, &deviceConfig, &device) != MA_SUCCESS) {
        throw std::runtime_error("Failed to initialize recording device!");
    }
    this->state = READY;
}

DefaultRecorder::~DefaultRecorder() {
    if (this->state != FINISHED) {
        this->DefaultRecorder::finish();
    }
}

void DefaultRecorder::record() {
    ma_device_start(&device);
    this->state = RECORDING;
}

void DefaultRecorder::pause() {
    ma_device_stop(&device);
    this->state = PAUSED;
}

void DefaultRecorder::finish() {
    ma_device_uninit(&device);
    ma_encoder_uninit(&encoder);
    this->state = FINISHED;
}
