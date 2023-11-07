#include "sender.h"
#include "../game_src/game_lobby.h"
#include "../game_src/game_dynamic.h"


Sender::Sender(int id, Protocol& protocol, Queue<Serializable*>& playerQueue, bool& talking) 
: id(id), protocol(protocol), playerQueue(playerQueue), talking(talking) {}

void Sender::run() {
    try {
        Serializable* gameLobbyS = playerQueue.pop();
        GameLobby* gameLobby = dynamic_cast<GameLobby*>(gameLobbyS);
        gameLobby->send(protocol);

        while (1) {
            Serializable* gameLobbySS = playerQueue.pop();
            GameDynamic* gameDynamic = dynamic_cast<GameDynamic*>(gameLobbySS);
            gameDynamic->send(protocol);
        }
    } catch (...) {
        std::cout << "y mira tu casteo esta como el culo\n";
    }
}

Sender::~Sender() {}
