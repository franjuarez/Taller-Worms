#include "server_sender.h"
#include "../game_src/game_dynamic.h"
#include "../game_src/game_map.h"


ServerSender::ServerSender(Protocol& protocol, Queue<Serializable*>& playerQueue, bool& talking) 
: protocol(protocol), playerQueue(playerQueue), talking(talking) {}

void ServerSender::run() {
    try {
        while (talking) {
            Serializable* gameStatus = playerQueue.pop();
            gameStatus->send(protocol);
        }   
    } catch (ClosedQueue& e) {
        std::cout << "ServerSender: Cerrada la queue\n";
    } catch (ClosedSocket& e) {
        std::cout << "ServerSender: cerrado el socket\n";
    } catch (std::exception& e) {
        std::cout << "error inesperado! " << e.what() << std::endl;
    }
}

ServerSender::~ServerSender() {}
