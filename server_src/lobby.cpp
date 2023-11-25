#include "lobby.h"
#include "game_loop.h"
#include "match_struct.h"
#include "matches_monitor.h"
#include "connecting_user.h"
#include "status_broadcaster.h"
#include <string>
#include "../game_src/constants_game.h"
#include "../game_src/worm_dto.h"
#include "../game_src/beam_dto.h"
#include "../game_src/game_map.h"

#include "player.h"

#include <memory>


Lobby::Lobby(const std::string& hostname, int numberOfPlayers, std::string mapName, bool* playing) 
: hostname(hostname), skt(hostname.c_str()), mapName(mapName), playing(playing) {
    this->numberOfPlayers = numberOfPlayers;
}

std::vector<WormDTO> Lobby::createWorms(std::vector<WormPosition> wormsPositions) {
    std::vector<WormDTO> worms;
    for(size_t i = 0; i < wormsPositions.size(); i++){
        WormDTO worm(i, STARTING_DIRECTON, STARTING_TEAM, CONFIG.getWormInitialHealth(),
         Position(wormsPositions[i].x, wormsPositions[i].y), STARTING_WEAPONS);
        worms.push_back(worm);
    }
    return worms;
}

std::vector<Team> Lobby::createTeams(std::vector<WormDTO>& worms) {
    std::vector<Team> teams;
    for(int id = 0; id < numberOfPlayers; id++){
        Team team(id);
        teams.push_back(team);
    }
    int currentTeam = 0;
    for(size_t i = 0; i < worms.size(); i++){
        teams[currentTeam].addWorm(worms[i].getId());
        worms[i].setTeam(currentTeam);
        currentTeam = (currentTeam + 1) % numberOfPlayers;
    }
    
    if(currentTeam == 0) return teams;

    for (; currentTeam < numberOfPlayers; currentTeam++){
        std::vector<int> teamWormsIDs = teams[currentTeam].getWormIDs();
        for(size_t i = 0; i < teamWormsIDs.size(); i++){
            worms[teamWormsIDs[i]].addHealth(CONFIG.getWormAdditionalHealth());
        }
    }

    return teams;
}
    
void Lobby::run() {
    MatchesMonitor matchesMonitor;
    int loops = 0;
    while (true) {
        Socket peer = skt.accept();
                    
        std::shared_ptr<InfoStruct>infoStruct = std::make_shared<InfoStruct>(std::move(peer));

        ConnectingUser* connectingUser = new ConnectingUser(infoStruct, matchesMonitor, playing, loops);
        connectingUser->start();
        connectingUsers.push_back(connectingUser);
        
        reapDead();
        loops++;
    }

    while (*playing) {
    
    }

    killAll();

}

void Lobby::reapDead() {
    connectingUsers.remove_if([](ConnectingUser* connectingUser) {
        if (!connectingUser->isActive()) {
            connectingUser->join();
            delete connectingUser;
            return true;
        } else {
            return false;
        }
    });
}

void Lobby::killAll() {
    for (auto& connectingUser : connectingUsers ) {
        if (connectingUser->isActive()) {
            connectingUser->kill();
        }
        connectingUser->join();
        delete connectingUser;
    }
    connectingUsers.clear();
}

Lobby::~Lobby() {
    // killAll();
}
