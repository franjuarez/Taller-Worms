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
        // std::cout << "Sender: Se ha cerrado la conexion\n";
        statusBroadcaster.deletePlayer(playerID);
        talking = false;
    } catch (const ClosedQueue& e){
        // std::cout << "Sender: Se ha cerrado la queue\n";
        statusBroadcaster.deletePlayer(playerID);
        talking = false;
    } catch (std::exception& e){
        std::cout << "Error in receiver: " << e.what() << std::endl;
        statusBroadcaster.deletePlayer(playerID);
        talking = false;
    }
}

ServerSender::~ServerSender() {}
