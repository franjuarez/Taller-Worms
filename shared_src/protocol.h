#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "socket.h"
#include "constants.h"
#include "../game_src/serializable.h"
#include  "../game_src/worm_dto.h"
#include  "../game_src/beam_dto.h"
#include  "../game_src/position.h"

#include <iostream>
#include <vector>

class GameLobby;
class GameDynamic;
class GameMap;
class SelectMap;
class Move;
class Command;

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


    void sendBeam(BeamDTO& beam);
    BeamDTO receiveBeam(int id);
    void sendWorm(WormDTO& worm);
    WormDTO receiveWorm();
    void sendPosition(Position& position);
    Position receivePosition();
    void sendMapNames(std::vector<std::string>& mapNames);
    std::vector<std::string> receiveMapNames();


    Move* receiveMove();
    SelectMap* receiveSelectMap();
    void checkClosed();

public:

    // Agregar los send de los Commands.

    explicit Protocol(Socket&& skt);
    Protocol(const std::string& hostname, const std::string& servname);

    // void sendMap(GameMap&);
    // GameMap receiveMap();

    void sendLobby(GameLobby* lobby);
    GameLobby receiveLobby();

    void sendDynamic(GameDynamic* dynamic);
    GameDynamic* receiveDynamic();

    void sendSelectMap(SelectMap* selectMap);
    

    void sendMove(Move* move);
    

    // void sendCommand(Command&);
    Command* receiveCommand();

    ~Protocol();

    void boom();

};
#endif
