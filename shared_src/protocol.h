#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "socket.h"
#include "../game_src/game_map.h"
#include "../game_src/game_dynamic.h"


#include <iostream>
#include <vector>

struct ClosedSocket : public std::runtime_error {
    ClosedSocket() : std::runtime_error("Socket is closed") {} 
}; 


class Protocol {

private:
    Socket skt;
    bool was_closed;

    void sendUintEight(uint8_t);
    void sendUintSixteen(uint16_t);
    void sendUintThirtyTwo(uint32_t);
    void sendString(const std::string&);
    

    uint8_t receiveUintEight();
    uint16_t receiveUintSixteen();
    uint32_t receiveUintThirtyTwo();
    std::string receiveString();

    void sendMap(GameMap&);
    GameMap receiveMap(int i);
    void sendBeam(Beam&);
    Beam receiveBeam();
    void sendWorm(Worm&);
    Worm receiveWorm();
    void sendPosition(Position&);
    Position receivePosition();

    void checkClosed();

public:
    explicit Protocol(Socket&&);
    Protocol(const std::string&, const std::string&);

    void sendMaps(std::vector<GameMap>&);
    std::vector<GameMap> receiveMaps();

    void sendDynamic(GameDynamic&);
    GameDynamic receiveDynamic();

    ~Protocol();

    void boom();

};
#endif
