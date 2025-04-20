#pragma once
#include <memory>
#include <string>

#include "app_state_holder.h"
#include "device_repository.h"
#include "device_id_manager.h"
#include "logging.h"

class ToneLogger;

namespace tone::ui {
    struct InputCommands {
        static constexpr std::string ADD = "add";
        static constexpr std::string REMOVE = "remove";
        static constexpr std::string PLAY = "play";
        static constexpr std::string START = "start";
        static constexpr std::string STOP = "stop";
        static constexpr std::string RESET = "reset";
        static constexpr std::string FILE = "file";
        static constexpr std::string EXIT = "exit";
    };

    struct InputSubjects {
        static constexpr std::string PLAYER = "player";
        static constexpr std::string RECORDER = "recorder";
    };

    class MainInputProcessor {
        std::shared_ptr<ILogger> logger;
        std::shared_ptr<IDeviceRepository> device_facade;
        std::shared_ptr<DeviceIdManager> device_id_mapper;
        std::shared_ptr<IAppStateHolder> app_state_holder;

        boost::uuids::uuid addPlayer(const std::string& file_name) const;

        boost::uuids::uuid addRecorder(const std::string& file_name) const;

    public:
        MainInputProcessor(
            std::shared_ptr<IDeviceRepository> device_facade,
            std::shared_ptr<DeviceIdManager> device_id_mapper,
            std::shared_ptr<IAppStateHolder> app_state_holder,
            std::shared_ptr<ILogger> logger
        );

        void process(std::string input) const;
    };
}
