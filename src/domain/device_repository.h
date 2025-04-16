#pragma once
#include <map>
#include <vector>

#include "player.h"

namespace tone {

    class IDeviceRepository {
    public:
        virtual ~IDeviceRepository() = default;

        virtual void addPlayer(std::shared_ptr<IPlayer> player) = 0;

        virtual void removePlayer(boost::uuids::uuid player_id) = 0;

        virtual void startPlayer(boost::uuids::uuid player_id) const = 0;

        virtual void stopPlayer(boost::uuids::uuid player_id) const = 0;

        virtual void changePlayerFile(boost::uuids::uuid player_id, std::string file_name) const = 0;

        virtual std::vector<std::shared_ptr<IPlayerInfo> > getPlayersInfo() const = 0;
    };

    class DeviceRepository : public IDeviceRepository {
        std::map<boost::uuids::uuid, std::shared_ptr<IPlayer> > players{};

    public:
        void addPlayer(std::shared_ptr<IPlayer> player) override;

        void removePlayer(boost::uuids::uuid player_id) override;

        void startPlayer(boost::uuids::uuid player_id) const override;

        void stopPlayer(boost::uuids::uuid player_id) const override;

        void changePlayerFile(boost::uuids::uuid player_id, std::string file_name) const override;

        std::vector<std::shared_ptr<IPlayerInfo> > getPlayersInfo() const override;
    };
}
