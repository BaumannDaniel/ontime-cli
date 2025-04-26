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
            44100
        )
    ) {
}

tone::Recorder::~Recorder() {
    this->Recorder::unInit();
}

void tone::Recorder::capture_callback(ma_device *p_device, void *p_output, const void *p_input, ma_uint32 frame_count) {
    auto config = static_cast<RecorderCallbackConfig *>(p_device->pUserData);
    (void) p_output;
    auto *encoder = config->encoder;
    if (encoder == nullptr) return;
    ma_encoder_write_pcm_frames(encoder, p_input, frame_count, nullptr);
    auto recorder_info = config->recorder_info;
    recorder_info->frame_count += frame_count;
}

void tone::Recorder::init() {
    std::lock_guard lock(recorder_mutex);
    if (this->state != UN_INIT) {
        return;
    }
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
    this->recorder_callback_config = {
        .encoder = &encoder,
        .recorder_info = this->recorder_info
    };
    this->deviceConfig.pUserData = &recorder_callback_config;
    if (ma_device_init(nullptr, &deviceConfig, &device) != MA_SUCCESS) {
        throw std::runtime_error("Failed to initialize recording device!");
    }
    this->state = INIT;
}

void tone::Recorder::start() {
    std::lock_guard lock(recorder_mutex);
    if (this->state == STARTED || this->state == UN_INIT) {
        return;
    }
    ma_device_start(&device);
    this->state = STARTED;
}

void tone::Recorder::stop() {
    std::lock_guard lock(recorder_mutex);
    if (this->state == STOPPED || this->state == UN_INIT) {
        return;
    }
    ma_device_stop(&device);
    this->state = STOPPED;
}

void tone::Recorder::unInit() {
    this->stop();
    std::lock_guard lock(recorder_mutex);
    if (this->state == UN_INIT) {
        return;
    }
    ma_device_uninit(&device);
    ma_encoder_uninit(&encoder);
    this->state = UN_INIT;
}

std::shared_ptr<tone::IRecorderInfo> tone::Recorder::getRecorderInfo() const {
    return this->recorder_info;
}

tone::RecorderInfo::RecorderInfo(
    boost::uuids::uuid recorder_id,
    std::string file_name,
    uint64_t n_pcm_frames,
    u_int64_t sample_rate
) : id(recorder_id),
    file_name(std::move(file_name)),
    frame_count(n_pcm_frames),
    sample_rate(sample_rate) {
}

boost::uuids::uuid tone::RecorderInfo::getId() const {
    return this->id;
}

std::string tone::RecorderInfo::getFileName() const {
    return this->file_name;
}

uint64_t tone::RecorderInfo::getNumberOfPcmFrames() const {
    return this->frame_count;
}

u_int64_t tone::RecorderInfo::getSampleRate() const {
    return this->sample_rate;
}
