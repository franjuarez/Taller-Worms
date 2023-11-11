#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "socket.h"
#include "constants.h"
#include "../game_src/serializable.h"
#include  "../game_src/worm_dto.h"
#include  "../game_src/beam_dto.h"
#include  "../game_src/weapons_dto.h"
#include  "../game_src/position.h"

#include <iostream>
#include <vector>

class GameLobby; class GameDynamic; class GameMap;
class Command; class Move; class Jump; class Attack;

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


    void sendBeams(std::vector<BeamDTO> beams);
    std::vector<BeamDTO> receiveBeams();

    void sendWorms(std::vector<WormDTO> worms);
    std::vector<WormDTO> receiveWorms();

    void sendWeapons(std::vector<WeaponDTO> proyectiles);
    std::vector<WeaponDTO> receiveWeapons();

    void sendPosition(Position position);
    Position receivePosition();

    void sendMapNames(std::vector<std::string>& mapNames);
    std::vector<std::string> receiveMapNames();

    void sendWeaponsMap(std::map<int, int> weapons);
    std::map<int, int> receiveWeaponsMap();


    Move* receiveMove();
    Jump* receiveJump();
    Attack* receiveAttack();
    void checkClosed();

public:

    explicit Protocol(Socket&& skt);
    Protocol(const std::string& hostname, const std::string& servname);

    void sendMap(GameMap* map);
    GameMap* receiveMap();

    void sendDynamic(GameDynamic* dynamic);
    GameDynamic* receiveDynamic();

    void sendMove(Move* move);

    void sendJump(Jump* jump);

    void sendAttack(Attack* attack);
    

    // void sendCommand(Command&);
    Command* receiveCommand();

    ~Protocol();

    void boom();

};
#endif
