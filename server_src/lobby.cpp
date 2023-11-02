#include "lobby.h"
#include "game_loop.h"
#include "status_broadcaster.h"
#include "../game_src/game.h"
#include "../game_src/game_lobby.h"

Lobby::Lobby(Socket& skt) : skt(skt) {}

void Lobby::run() {

    // se deberian parsear los archivos con los mapas
    std::vector<std::string> maps = {"joaco no sabe pensar nombres de mapas"};
    int idPlayer = 0;

    // Deberia el GameLoop ser una nueva thread? Sino? 
    // Deberia GaameLoop inicializar Lobby??? 

    Queue<Command> commandQueue;
    StatusBroadcaster statusBroadcaster;
    while (idPlayer < 1) {        
        while(idPlayer < 1) {
            try {
                Socket peer = skt.accept();
                idPlayer++;
                GameLobby playerLobby(maps, idPlayer);
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
        // Inicializar el GameLoop 
        GameLoop gameLoop(commandQueue, statusBroadcaster);
        gameLoop.start();
    }

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