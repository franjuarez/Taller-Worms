#include "sender.h"
#include "../game_src/commands/command.h"
#include "../game_src/constants_game.h"
#include <iostream>
#include "client_error.h"

Sender::Sender(Protocol& protocol, Queue<std::shared_ptr<Command>>& q, bool& keepTalking) : protocol(protocol), 
commandsQueue(q), keepTalking(keepTalking) {}

void Sender::run() {
    try {
        while (keepTalking) {
            std::shared_ptr<Command> command = commandsQueue.pop();
            command->send(protocol);    
        }
    } catch (const ClosedSocket& e){
        commandsQueue.close();
        if (!keepTalking) {
            return;
        }
        keepTalking = false;
    } catch (const ClosedQueue& e){
        if (!keepTalking) {
            return;
        }
        keepTalking = false;
    } catch (std::exception& e){
        if (!keepTalking) {
            return;
        }
        keepTalking = false;
    }
}

Sender::~Sender() {}