#include <stdexcept>

#include "recorder.h"

#include <boost/uuid/random_generator.hpp>

tone::Recorder::Recorder(
    std::string file_name,
    std::shared_ptr<ILogger> logger
) : logger(std::move(logger)),
    recorder_info(
        std::make_shared<RecorderInfo>(
            boost::uuids::random_generator()(),
            std::move(file_name),
            0,
            0,
            44100
        )
    ) {
}

tone::Recorder::~Recorder() {
    if (this->state != UN_INIT) {
        this->Recorder::unInit();
    }
}

void tone::Recorder::capture_callback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount) {
    (void) pOutput;
    auto *pEncoder = static_cast<ma_encoder *>(pDevice->pUserData);
    if (pEncoder == nullptr) return;
    ma_encoder_write_pcm_frames(pEncoder, pInput, frameCount, nullptr);
}

void tone::Recorder::init() {
    this->encoderConfig = ma_encoder_config_init(
        ma_encoding_format_wav,
        ma_format_f32,
        2,
        this->recorder_info->sample_rate
    );
    if (ma_encoder_init_file(this->recorder_info->getFileName().c_str(), &encoderConfig, &encoder) != MA_SUCCESS) {
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
    this->state = INIT;
}

void tone::Recorder::start() {
    ma_device_start(&device);
    this->state = STARTED;
}

void tone::Recorder::stop() {
    ma_device_stop(&device);
    this->state = STOPPED;
}

void tone::Recorder::unInit() {
    this->stop();
    ma_device_uninit(&device);
    ma_encoder_uninit(&encoder);
    this->state = UN_INIT;
}

std::shared_ptr<tone::IRecorderInfo> tone::Recorder::getRecorderInfo() const {
    return this->recorder_info;
}

