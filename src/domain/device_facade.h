#pragma once
#include <map>
#include <vector>

#include "player.h"

namespace tone {

    class IDeviceFacade {
    public:
        virtual ~IDeviceFacade() = default;

        virtual void addPlayer(std::shared_ptr<Player> player) = 0;

        virtual void removePlayer(boost::uuids::uuid player_id) = 0;

        virtual void startPlayer(boost::uuids::uuid player_id) const = 0;

        virtual void stopPlayer(boost::uuids::uuid player_id) const = 0;

        virtual void changePlayerFile(boost::uuids::uuid player_id, std::string file_name) const = 0;

        virtual std::vector<std::shared_ptr<PlayerInfo> > getPlayersInfo() const = 0;
    };

    class DeviceFacade : public IDeviceFacade {
        std::map<boost::uuids::uuid, std::shared_ptr<Player> > players{};

    public:
        void addPlayer(std::shared_ptr<Player> player) override;

        void removePlayer(boost::uuids::uuid player_id) override;

        void startPlayer(boost::uuids::uuid player_id) const override;

        void stopPlayer(boost::uuids::uuid player_id) const override;

        void changePlayerFile(boost::uuids::uuid player_id, std::string file_name) const override;

        std::vector<std::shared_ptr<PlayerInfo> > getPlayersInfo() const override;
    };
}
