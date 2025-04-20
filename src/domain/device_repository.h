#pragma once
#include <map>
#include <vector>

#include "player.h"
#include "recorder_i.h"

namespace tone {

    class IDeviceRepository {
    public:
        virtual ~IDeviceRepository() = default;

        virtual void addPlayer(std::shared_ptr<IPlayer> player) = 0;

        virtual void addRecorder(std::shared_ptr<IRecorder> recorder) = 0;

        virtual void removeDevice(boost::uuids::uuid device_id) = 0;

        virtual void startDevice(boost::uuids::uuid device_id) const = 0;

        virtual void stopDevice(boost::uuids::uuid device_id) const = 0;

        virtual void changeDeviceFile(boost::uuids::uuid device_id, std::string file_name) const = 0;

        virtual std::vector<std::shared_ptr<IPlayerInfo> > getPlayersInfo() const = 0;

        virtual std::vector<std::shared_ptr<IRecorderInfo> > getRecordersInfo() const = 0;
    };

    class DeviceRepository : public IDeviceRepository {
        std::map<boost::uuids::uuid, std::shared_ptr<IPlayer> > players{};
        std::map<boost::uuids::uuid, std::shared_ptr<IRecorder> > recorders{};

    public:
        void addPlayer(std::shared_ptr<IPlayer> player) override;

        void addRecorder(std::shared_ptr<IRecorder> recorder) override;

        void removeDevice(boost::uuids::uuid device_id) override;

        void startDevice(boost::uuids::uuid device_id) const override;

        void stopDevice(boost::uuids::uuid device_id) const override;

        void changeDeviceFile(boost::uuids::uuid device_id, std::string file_name) const override;

        std::vector<std::shared_ptr<IPlayerInfo> > getPlayersInfo() const override;

        std::vector<std::shared_ptr<IRecorderInfo> > getRecordersInfo() const override;
    };
}
