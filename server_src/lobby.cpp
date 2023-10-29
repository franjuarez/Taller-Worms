#include "lobby.h"

Lobby::Lobby(Socket& skt) : skt(skt) {}

void Lobby::start() {

    // se deberian parsear los archivos con los mapas
    std::vector<std::string> maps = {};
    int idPlayer = 0;
    while(true) {
        try {
            Socket peer = skt.accept();
            idPlayer++;
            GameLobby gameLobby(maps, idPlayer);
            Player* player = new Player(gameLobby, std::move(peer));
            // magic happens

            reapDead();
            players.push_back(player);
        } catch (...) {
            // pasan mas cosas 
        }
    }

    killAll();
}

void Lobby::reapDead() {}

void Lobby::killAll() {}

Lobby::~Lobby() {}