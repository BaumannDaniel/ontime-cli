#pragma once
#include <boost/uuid/uuid.hpp>

#include "device_state.h"

namespace tone {
    class IPlayerInfo {
    public:
        virtual ~IPlayerInfo() = default;

        virtual boost::uuids::uuid getId() const = 0;

        virtual std::string getFileName() = 0;

        virtual uint64_t getNumberOfPcmFrames() const = 0;

        virtual uint64_t getCurrentPcmFrameNumber() const = 0;

        virtual u_int64_t getSampleRate() const = 0;
    };

    class IPlayer {
    public:
        virtual ~IPlayer() = default;

        virtual void init() = 0;

        virtual void start() = 0;

        virtual void stop() = 0;

        virtual void unInit() = 0;

        virtual void changeFile(std::string file_name) = 0;

        virtual DeviceState getDeviceState() const = 0;

        virtual std::shared_ptr<IPlayerInfo> getPlayerInfo() const = 0;
    };
}
