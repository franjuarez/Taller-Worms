#include "server_sender.h"
#include "../game_src/game_dynamic.h"
#include "../game_src/game_map.h"


ServerSender::ServerSender(Protocol& protocol, StatusBroadcaster& statusBroadcaster, bool& talking, int playerID) 
: protocol(protocol), statusBroadcaster(statusBroadcaster), talking(talking), playerID(playerID) {}

void ServerSender::run() {
    try {
        while (talking) {
            std::shared_ptr<Serializable> gameStatus = statusBroadcaster.getGame(playerID);
            gameStatus->send(protocol);
        }   
    } catch (const ClosedSocket& e){
        statusBroadcaster.deletePlayer(playerID);
        talking = false;
    } catch (const ClosedQueue& e){
        statusBroadcaster.deletePlayer(playerID);
        talking = false;
    } catch (std::exception& e){
        statusBroadcaster.deletePlayer(playerID);
        talking = false;
    }
}

ServerSender::~ServerSender() {}
