
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
    std::cout << "Reciever running\n";

    // 1ero get the GameLobby with the players team and the available maps
    try {   

        
        GameLobby lobby = protocol.receiveLobby();
        gameStatuses.push(lobby);

        std::cout << lobby.getMapNames()[0] + '\n';

        // 2do get the map selected by the player
        // GameMap map = protocol.receiveMap();
        // GameStatus gameStatus(true, map, GameDynamic(NO_WORM_PLAYING));
        // gameStatuses.push(gameStatus);

        // // 3rd start receiving the game status -> with the playing worm/team, 
        // // the map stays the same and the new dynamic objects -> worms, boxes, etc

        // while (true) {
        //     GameDynamic gameDynamic = protocol.receiveDynamic();
        //     GameStatus gameStatus(true, map, gameDynamic);
        //     gameStatuses.push(gameStatus);
        // }
    } catch (const std::exception& err) {
        std::cerr << err.what() << '\n';
        // std::cout << "explote :( ";

    }
}

Receiver::~Receiver() {}
