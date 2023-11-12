#include "lobby.h"
#include "game_loop.h"
#include "status_broadcaster.h"
#include "../game_src/game_lobby.h"

//Lobby::Lobby(Socket& skt, int AMOUNT_OF_PLAYERS) : , skt(skt), commandQueue(90) {
//    this->AMOUNT_OF_PLAYERS = AMOUNT_OF_PLAYERS;
//}

Lobby::Lobby(const std::string& hostname, int AMOUNT_OF_PLAYERS) : hostname(hostname), skt(hostname.c_str()), commandQueue(90) {
    this->AMOUNT_OF_PLAYERS = AMOUNT_OF_PLAYERS;
}

void Lobby::run() {

    // se deberian parsear los archivos con los mapas
    std::vector<std::string> maps = {"merge speedrun"};
    int idPlayer = 0;

    StatusBroadcaster statusBroadcaster;

    while(idPlayer < AMOUNT_OF_PLAYERS) {
        try {
            Socket peer = skt.accept();
            idPlayer++;
            GameLobby* playerLobby = new GameLobby(maps, idPlayer);
            Player* player = new Player(playerLobby, std::move(peer), commandQueue);
            // magic happens
            statusBroadcaster.addPlayer(idPlayer, player->getPlayerQueue());
            player->start();

            reapDead();
            players.push_back(player);
        } catch (...) {
            // pasan mas cosas 
        }
    }
    // momento eleccion Mapa

    // Inicializar el GameLoop 
    GameLoop gameLoop(commandQueue, statusBroadcaster);
    gameLoop.start();

    killAll();
}

void Lobby::reapDead() {}

void Lobby::killAll() {
    for (auto& player : players ) {
        if (player->isAlive()) {
            player->kill();
        }
        player->join();
        delete player;
    }
    players.clear();
}

Lobby::~Lobby() {}