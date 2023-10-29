#include "sender.h"

Sender::Sender(Protocol& protocol, Queue<Game>& q) :
 protocol(protocol), playerQueue(q) {}

void Sender::run() {
    // Game gameLobby = playerQueue.pop();
    // protocol.sendLobby(gameLobby);
    while (1) {}
}

Sender::~Sender() {}

