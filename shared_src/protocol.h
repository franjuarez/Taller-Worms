#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "socket.h"
#include "constants.h"
#include  "../game_src/worm_dto.h"
#include  "../game_src/beam_dto.h"
#include  "../game_src/explosives_dto.h"
#include  "../game_src/position.h"

#include <iostream>
#include <vector>
#include <unordered_map>

class GameDynamic; class GameMap; class Serializable;
class Command; class Move; class Jump; class LaunchRocket;
class Teleport; class HitUpclose; class ThrowGrenade;

struct ClosedSocket : public std::runtime_error {
    ClosedSocket() : std::runtime_error("Socket is closed") {} 
}; 


class Protocol {

private:
    Socket skt;
    bool was_closed = false;

    void sendFloat(float num);
    float receiveFloat();

    void sendUintEight(uint8_t num);
    uint8_t receiveUintEight();

    void sendUintSixteen(uint16_t num);
    uint16_t receiveUintSixteen();

    void sendUintThirtyTwo(uint32_t num);
    uint32_t receiveUintThirtyTwo();

    void sendString(const std::string& str);
    std::string receiveString();

    void sendChar(char c);
    char receiveChar();


    void sendBeams(std::vector<BeamDTO> beams);
    std::vector<BeamDTO> receiveBeams();

    void sendWorms(std::vector<WormDTO> worms);
    std::vector<WormDTO> receiveWorms();

    void sendWeapons(std::unordered_map<int, ExplosivesDTO> explosives);
    std::unordered_map<int, ExplosivesDTO> receiveWeapons();

    void sendPosition(Position position);
    Position receivePosition();

    void sendMapNames(std::vector<std::string>& mapNames);
    std::vector<std::string> receiveMapNames();

    void sendWeaponsMap(std::vector<int> weapons);
    std::vector<int> receiveWeaponsMap();

    GameMap* receiveMap();
    GameDynamic* receiveDynamic();

    Move* receiveMove();
    Jump* receiveJump();
    LaunchRocket* receiveLaunchRocket();
    ThrowGrenade* receiveThrowGrenade();
    Teleport* receiveTeoleport();
    HitUpclose* receiveHitUpclose();

    void checkClosed();

public:

    explicit Protocol(Socket&& skt);
    Protocol(const std::string& hostname, const std::string& servname);

    void sendMap(GameMap* map);

    void sendDynamic(GameDynamic* dynamic);
    
    Serializable* receiveSerializable();

    void sendMove(Move* move);

    void sendJump(Jump* jump);

    void sendLaunchRocket(LaunchRocket* attack);

    void sendThrowGrenade(ThrowGrenade* throwGrenade);

    void sendTeleport(Teleport* teleport);
    
    void sendHitUpclose(HitUpclose* hitUpclose);

    Command* receiveCommand();

    ~Protocol();

    void boom();

};
#endif
