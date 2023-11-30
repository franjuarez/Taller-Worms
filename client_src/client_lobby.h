#ifndef CLIENT_LOBBY_H
#define CLIENT_LOBBY_H

#include "../shared_src/socket.h"
#include "../shared_src/protocol.h"

struct InfoStruct;

class ClientLobby {
    
    std::shared_ptr<InfoStruct> infoStruct;

public:

    ClientLobby(const std::string& hostname, const std::string& servname);

    void run();

    void showMatches();

    int createNewMatch(int nrPlayers, std::string matchName, std::string mapName);

    int joinMatch(std::string matchName);

    void refresh();

    void startGame();

    std::map<std::string, std::string> getAvailableMatches();

    ~ClientLobby();
};

#endif
