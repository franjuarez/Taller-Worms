#include "sender.h"

Sender::Sender(int id, Protocol& protocol, StatusBroadcaster& statusBroadcaster, bool& talking) 
: id(id), protocol(protocol), statusBroadcaster(statusBroadcaster), talking(talking) {}

void Sender::run() {
    Game gameLobby = statusBroadcaster.getGame(id);
    protocol.sendLobby(gameLobby);
    while (1) {
        // Game game = statusBroadcaster.getGame(id);
        // protocol.sendDynamic(game);
    }
}

Sender::~Sender() {}

