#include "server_sender.h"
#include "../game_src/game_dynamic.h"
#include "../game_src/game_map.h"


ServerSender::ServerSender(Protocol& protocol, Queue<std::shared_ptr<Serializable>>& playerQueue, bool& talking) 
: protocol(protocol), playerQueue(playerQueue), talking(talking) {}

void ServerSender::run() {
    try {
        while (talking) {
            std::shared_ptr<Serializable> gameStatus = playerQueue.pop();
            gameStatus->send(protocol);
        }   
    } catch (const ClosedSocket& e){
        std::cout << "Sender: Se ha cerrado la conexion\n";
        talking = false;
    } catch (const ClosedQueue& e){
        std::cout << "Sender: Se ha cerrado la queue\n";
        talking = false;
    } catch (std::exception& e){
        std::cout << "Error in receiver: " << e.what() << std::endl;
        talking = false;
    }
}

ServerSender::~ServerSender() {}
