#include "lobby.h"
#include "status_broadcaster.h"

Lobby::Lobby(Socket& skt) : skt(skt) {}

void Lobby::run() {

    // se deberian parsear los archivos con los mapas
    std::vector<std::string> maps = {"Trying",};
    int idPlayer = 0;

    // Deberia el GameLoop ser una nueva thread? Sino? 
    // Deberia GaameLoop inicializar Lobby??? 

    Queue<Command> commandQueue;
    StatusBroadcaster statusBroadcaster;
    while(true) {
        try {
            Socket peer = skt.accept();
            idPlayer++;
            GameLobby playerLobby(maps, idPlayer);
            Player* player = new Player(playerLobby, std::move(peer), commandQueue, statusBroadcaster);
            // magic happens

            player->start();

            reapDead();
            players.push_back(player);
        } catch (...) {
            // pasan mas cosas 
        }
    }

    // Inicializar el GameLoop 

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