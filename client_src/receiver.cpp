
#include "receiver.h"
#include "../game_src/game_dynamic.h"
#include "../game_src/game_info.h"

#include "../shared_src/protocol.h"
#include <unistd.h>

#include <iostream>

Receiver::Receiver(Protocol& protocol, Queue<std::shared_ptr<Serializable>>& q, bool& keepTalking) 
: protocol(protocol), gameStatuses(q), keepTalking(keepTalking) {}

void Receiver::run() {
    try {
        // std::shared_ptr<Serializable>gameDynamic(protocol.receiveSerializable());
        // std::shared_ptr<GameInfo> gs = std::dynamic_pointer_cast<GameInfo>(gameDynamic);
        // std::cout << gs->getMatchesAvailable().size() << std::endl;

        while (keepTalking) {
            std::shared_ptr<Serializable>gameDynamic(protocol.receiveSerializable());
            gameStatuses.push(gameDynamic);
        }
    } catch (const ClosedSocket& e){
        keepTalking = false;
    } catch (const ClosedQueue& e){
        keepTalking = false;
    } catch (std::exception& e){
        std::cout << "Error in receiver: " << e.what() << std::endl;
        keepTalking = false;
    }
}

Receiver::~Receiver() {}
