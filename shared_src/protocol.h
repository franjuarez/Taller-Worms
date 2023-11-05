#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "socket.h"
#include "../game_src/game.h"
#include "../game_src/serializable.h"
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

    void sendFloat(float);
    float receiveFloat();
    void sendUintEight(uint8_t num);
    uint8_t receiveUintEight();
    void sendUintSixteen(uint16_t num);
    uint16_t receiveUintSixteen();
    void sendUintThirtyTwo(uint32_t num);
    uint32_t receiveUintThirtyTwo();
    void sendString(const std::string& str);
    std::string receiveString();


    void sendBeam(Beam& beam);
    Beam receiveBeam(int id);
    void sendWorm(Worm& worm);
    Worm receiveWorm();
    void sendPosition(Position& position);
    Position receivePosition();
    void sendMapNames(std::vector<std::string>& mapNames);
    std::vector<std::string> receiveMapNames();

    void checkClosed();

public:
    explicit Protocol(Socket&& skt);
    Protocol(const std::string& hostname, const std::string& servname);

    void sendMap(GameMap&);
    GameMap receiveMap();

    void sendLobby(GameLobby lobby);
    GameLobby receiveLobby();
    void sendDynamic(GameDynamic dynamic);
    GameDynamic receiveDynamic();

    void sendCommand(Command&);
    Command receiveCommand();

    ~Protocol();

    void boom();

};
#endif
