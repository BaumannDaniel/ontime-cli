#pragma once
#include <boost/uuid/uuid.hpp>

namespace tone {
    class IRecorderInfo {
    public:
        virtual ~IRecorderInfo() = default;

        virtual boost::uuids::uuid getId() const = 0;

        virtual std::string getFileName() const = 0;

        virtual uint64_t getNumberOfPcmFrames() const = 0;

        virtual uint64_t getCurrentPcmFrameNumber() const = 0;

        virtual u_int64_t getSampleRate() const = 0;
    };

    class IRecorder {
    public:
        virtual ~IRecorder() = default;

        virtual void init() = 0;

        virtual void start() = 0;

        virtual void stop() = 0;

        virtual void unInit() = 0;

        virtual std::shared_ptr<IRecorderInfo> getRecorderInfo() const = 0;
    };
}
