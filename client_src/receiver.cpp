#include "receiver.h"
#include "../game_src/game_dynamic.h"
#include "../game_src/game_info.h"

#include "../shared_src/protocol.h"
#include <unistd.h>
#include "client_error.h"
#include <iostream>

Receiver::Receiver(Protocol& protocol, Queue<std::shared_ptr<Serializable>>& q, bool& keepTalking) 
: protocol(protocol), gameStatuses(q), keepTalking(keepTalking) {}

void Receiver::run() {
    try {
        while (keepTalking) {
            std::shared_ptr<Serializable> gameDynamic = protocol.receiveSerializable();
            gameStatuses.push(gameDynamic);
        }
    } catch (const ClosedSocket& e){
        gameStatuses.close();
        if (!keepTalking) {
            return;
        }
        keepTalking = false;
        return;
    } catch (const ClosedQueue& e){
        if (!keepTalking) {
            return;
        }
        keepTalking = false;
        return;
    } catch (std::exception& e){
        if (!keepTalking) {
            return;
        }
        keepTalking = false;
    }
}

Receiver::~Receiver() {}
