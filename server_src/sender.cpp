#include "sender.h"

Sender::Sender(int id, Protocol& protocol, Queue<Serializable>& playerQueue, bool& talking) 
: id(id), protocol(protocol), playerQueue(playerQueue), talking(talking) {}

void Sender::run() {
    Serializable* gameLobbyS = &playerQueue.pop();
    GameLobby& gameLobby = dynamic_cast<GameLobby&>(*gameLobbyS);
    gameLobby.send(protocol);
    while (1) {
        // Serializable game = playerQueue.pop();
        // protocol.sendDynamic(game);
    }
}

Sender::~Sender() {}
