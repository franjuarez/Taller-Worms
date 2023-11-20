
#include "receiver.h"
#include "../game_src/game_dynamic.h"
#include "../shared_src/protocol.h"
#include <unistd.h>

#include <iostream>

Receiver::Receiver(Protocol& protocol, Queue<std::shared_ptr<Serializable>>& q, bool& keepTalking) 
: protocol(protocol), gameStatuses(q), keepTalking(keepTalking) {}

void Receiver::run() {
    try {
        while (keepTalking) {
            std::shared_ptr<Serializable>gameDynamic(protocol.receiveSerializable());
            gameStatuses.push(gameDynamic);
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
