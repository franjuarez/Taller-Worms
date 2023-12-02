#include "sender.h"
#include "../game_src/commands/command.h"
#include "../game_src/constants_game.h"
#include <iostream>

Sender::Sender(Protocol& protocol, Queue<std::shared_ptr<Command>>& q, bool& keepTalking) : protocol(protocol), 
commandsQueue(q), keepTalking(keepTalking) {}

void Sender::run() {
    try {
        while (keepTalking) {
            std::shared_ptr<Command> command = commandsQueue.pop();
            command->send(protocol);    
        }
    } catch (const ClosedSocket& e){
        keepTalking = false;
        throw ClientClosed();
    } catch (const ClosedQueue& e){
        keepTalking = false;
        throw ClientClosed();
    } catch (std::exception& e){
        std::cout << "Error in receiver: " << e.what() << std::endl;
        keepTalking = false;
        throw ClientClosed();
    }
}

Sender::~Sender() {}