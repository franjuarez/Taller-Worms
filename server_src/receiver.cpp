#include "receiver.h"
#include "../shared_src/protocol.h"
#include "../game_src/select_map.h"
#include "../game_src/move.h"

Receiver::Receiver(Protocol& protocol, Queue<Command*>& commandsQueue, bool& talking) 
: protocol(protocol), commandsQueue(commandsQueue), talking(talking) {}

void Receiver::run() {
    while (true) {
        Command* command = protocol.receiveCommand();
        commandsQueue.push(command);
    }
}

Receiver::~Receiver() {}
