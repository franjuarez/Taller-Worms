
#include "receiver.h"
#include "../game_src/game.h"
#include "../game_src/game_lobby.h"
#include "../game_src/game_map.h"
#include "../game_src/game_dynamic.h"
#include "../game_src/game_status.h"
#include "../shared_src/protocol.h"
#include "../shared_src/constants.h"

#include <iostream>

Receiver::Receiver(Protocol& protocol, Queue<Game>& q) 
: protocol(protocol), gameStatuses(q) {}

void Receiver::run() {
    

    
    try {
        // 1st get the GameLobby with the players team and the available maps
        GameLobby lobby = protocol.receiveLobby();
        gameStatuses.push(lobby);

        // 2nd get the map selected by the player
        
        // GameMap map = protocol.receiveMap();
        // gameStatuses.push(map);

        // std::cout << map.getMapName() << "\n";
        // std::cout << map.getNumberOfBeams() << "\n";
        // std::cout << map.getBeams(0).at(0).getPosition2().getX() << "\n";

        // // 3rd start receiving the game status -> with the playing worm/team, 
        // // the map stays the same and the new dynamic objects -> worms, boxes, etc
        while (true) {
            GameDynamic gameDynamic = protocol.receiveDynamic();
            gameStatuses.push(gameDynamic);

            std::cout <<  gameDynamic.getWorms().at(0).getPosition().getX() << "\n";
            std::cout <<  gameDynamic.getWorms().at(0).getPosition().getY() << "\n";
            std::cout <<  gameDynamic.getWorms().at(1).getPosition().getX() << "\n";
            std::cout <<  gameDynamic.getWorms().at(1).getPosition().getY() << "\n";
            // std::cout <<  gameDynamic.getWormPlayingID() << "\n";
        }
    } catch (const std::exception& err) {
        std::cerr << err.what() << '\n';
    }
}

Receiver::~Receiver() {}
