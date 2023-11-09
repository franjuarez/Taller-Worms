
#include "receiver.h"
#include "../game_src/game_lobby.h"
#include "../game_src/game_dynamic.h"
#include "../shared_src/protocol.h"
#include <unistd.h>

#include <iostream>

Receiver::Receiver(Protocol& protocol, Queue<Serializable*>& q, bool& keepTalking) 
: protocol(protocol), gameStatuses(q), keepTalking(keepTalking) {}

void Receiver::run() {
    try {
        // 1st get the GameLobby with the players team and the available maps
        // GameLobby lobby = protocol.receiveLobby();
        // gameStatuses.push(&lobby);
        // std::cout <<  lobby.getMapNames().at(0) << "\n";
        
        // 2nd get the map selected by the player

        GameMap* map = protocol.receiveMap();
        gameStatuses.push(map);

        // // 3rd start receiving the game status -> with the playing worm/team, 
        // // the map stays the same and the new dynamic objects -> worms, boxes, etc
        while (keepTalking) {
            GameDynamic* gameDynamic = protocol.receiveDynamic();
            gameStatuses.push(gameDynamic);
            // std::cout <<  gameDynamic->getProjectiles().at(0).getType() << "\n";
            // std::cout <<  gameDynamic->getProjectiles().at(0).getVelX() << "\n";
        }
    } catch (const ClosedSocket& e){
        keepTalking = false;
    } catch (const ClosedQueue& e){
        keepTalking = false;
    } catch (...){
        keepTalking = false;
    }
}

Receiver::~Receiver() {}
