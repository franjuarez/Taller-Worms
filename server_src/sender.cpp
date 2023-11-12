#include "sender.h"
#include "../game_src/game_lobby.h"
#include "../game_src/game_dynamic.h"
#include "../game_src/game_map.h"


ServerSender::ServerSender(int id, Protocol& protocol, Queue<Serializable*>& playerQueue, bool& talking) 
: id(id), protocol(protocol), playerQueue(playerQueue), talking(talking) {}

void ServerSender::run() {
    try {
        // Serializable* gameLobbyS = playerQueue.pop();
        // GameLobby* gameLobby = dynamic_cast<GameLobby*>(gameLobbyS);
        // gameLobby->send(protocol);
        Serializable* gameMapS = playerQueue.pop();
        GameMap* gameMap = dynamic_cast<GameMap*>(gameMapS);
        gameMap->send(protocol);

        while (talking) {
            Serializable* gameLobbySS = playerQueue.pop();
            GameDynamic* gameDynamic = dynamic_cast<GameDynamic*>(gameLobbySS);
            gameDynamic->send(protocol);
        }
    } catch (ClosedQueue& e) {
        std::cout << "ServerSender: Cerrada la queue\n";
    } catch (ClosedSocket& e) {
        std::cout << "ServerSender: cerrado el socket\n";
    } catch (std::exception& e) {
        std::cout << "error inesperado! " << e.what() << std::endl;
    }
}

ServerSender::~ServerSender() {}
