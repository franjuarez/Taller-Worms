#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "socket.h"
#include "../game_src/game_map.h"
#include "../game_src/game_dynamic.h"
#include "../game_src/game_lobby.h"
#include "../game_src/commands.h"

#include <iostream>
#include <vector>

struct ClosedSocket : public std::runtime_error {
    ClosedSocket() : std::runtime_error("Socket is closed") {} 
}; 


class Protocol {

private:
    Socket skt;
    bool was_closed = false;

    void sendUintEight(uint8_t);
    void sendUintSixteen(uint16_t);
    void sendUintThirtyTwo(uint32_t);
    void sendString(const std::string&);
    

    uint8_t receiveUintEight();
    uint16_t receiveUintSixteen();
    uint32_t receiveUintThirtyTwo();
    std::string receiveString();


    void sendBeam(Beam&);
    Beam receiveBeam(int id);
    void sendWorm(Worm&);
    Worm receiveWorm();
    void sendPosition(Position&);
    Position receivePosition();
    void sendMapNames(std::vector<std::string>&);
    std::vector<std::string> receiveMapNames();

    void checkClosed();

public:
    explicit Protocol(Socket&&);
    Protocol(const std::string&, const std::string&);

    void sendMap(GameMap&);
    GameMap receiveMap();

    void sendLobby(Game&);
    GameLobby receiveLobby();
    void sendDynamic(Game&);
    GameDynamic receiveDynamic();

    void sendCommand(Command&);
    Command receiveCommand();

    ~Protocol();

    void boom();

};
#endif
