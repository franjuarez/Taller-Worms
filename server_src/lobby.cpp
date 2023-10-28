#include "lobby.h"

Lobby::Lobby(Socket& skt) : skt(skt) {}

void Lobby::start() {
    int idPlayer = 0;
    while(true) {
        Socket peer = skt.accept();
        Player* player = new Player(idPlayer, std::move(peer));
        // magic happens
        players.push_back(player);
    }
}

Lobby::~Lobby() {}