
#include "receiver.h"
#include "../game_src/game_dynamic.h"
#include "../shared_src/protocol.h"
#include <unistd.h>

#include <iostream>

Receiver::Receiver(Protocol& protocol, Queue<Serializable*>& q, bool& keepTalking) 
: protocol(protocol), gameStatuses(q), keepTalking(keepTalking) {}

void Receiver::run() {
    try {
        while (keepTalking) {
            Serializable* gameDynamic = protocol.receiveSerializable();
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
