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
#include "../shared_src/socket.h"
#include "../shared_src/info_struct.h"
#include "player.h"

#include <memory>
#include <utility>
#include <arpa/inet.h>


Lobby::Lobby(const std::string& hostname, int numberOfPlayers, std::string mapName, bool* playing) 
: hostname(hostname), skt(hostname.c_str()), mapName(mapName), playing(playing) {
    this->numberOfPlayers = numberOfPlayers;
}
    
void Lobby::run() {
    MatchesMonitor matchesMonitor;

    try {
        while (true) {
            Socket peer = skt.accept();
                        
            std::shared_ptr<InfoStruct>infoStruct = std::make_shared<InfoStruct>(std::move(peer));

            ConnectingUser* connectingUser = new ConnectingUser(infoStruct, matchesMonitor, playing);
            connectingUser->start();
            connectingUsers.push_back(connectingUser);
            
            reapDead();
        }
    } catch (const LibError& e) {
        matchesMonitor.closeMatches();
    }
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

void Lobby::stop() {
    skt.shutdown(SHUT_RDWR);
    skt.close();
    killAll();
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

Lobby::~Lobby() { }
