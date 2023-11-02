#include "sender.h"

Sender::Sender(int id, Protocol& protocol, Queue<Game>& playerQueue, bool& talking) 
: id(id), protocol(protocol), playerQueue(playerQueue), talking(talking) {}

void Sender::run() {
    Game gameLobby = playerQueue.pop();
    protocol.sendLobby(gameLobby);
    while (1) {
        Game game = playerQueue.pop();
        protocol.sendDynamic(game);
    }
}

Sender::~Sender() {}
