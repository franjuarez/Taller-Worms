#include "sender.h"
#include "../game_src/game_dynamic.h"
#include "../game_src/game_map.h"


Sender::Sender(Protocol& protocol, Queue<Serializable*>& playerQueue, bool& talking) 
: protocol(protocol), playerQueue(playerQueue), talking(talking) {}

void Sender::run() {
    try {
        while (talking) {
            Serializable* gameStatus = playerQueue.pop();
            gameStatus->send(protocol);
        }   
    } catch (ClosedQueue& e) {
        std::cout << "Sender: Cerrada la queue\n";
    } catch (ClosedSocket& e) {
        std::cout << "Sender: cerrado el socket\n";
    } catch (std::exception& e) {
        std::cout << "error inesperado! " << e.what() << std::endl;
    }
}

Sender::~Sender() {}
