#ifndef CLIENT_LOBBY_H
#define CLIENT_LOBBY_H

#include "../shared_src/socket.h"
#include "../shared_src/protocol.h"

struct InfoStruct;

class ClientLobby {
    
    std::shared_ptr<InfoStruct> infoStruct;

public:

    ClientLobby(std::shared_ptr<InfoStruct> infoStruct);

    void run();

    void showMatches();

    ~ClientLobby();
};

#endif
