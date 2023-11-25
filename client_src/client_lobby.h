#ifndef CLIENT_LOBBY_H
#define CLIENT_LOBBY_H

#include "../shared_src/socket.h"
#include "../shared_src/protocol.h"

class ClientLobby {    

public:
    Protocol prot;

    ClientLobby(const std::string& hostname, const std::string& servname);

    void run();

    void showMatches();

    ~ClientLobby();


};

#endif