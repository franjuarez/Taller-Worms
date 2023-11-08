#include "protocol.h"
#include "../game_src/game_dynamic.h"
#include "../game_src/select_map.h"
#include  "../game_src/move.h"
#include  "../game_src/jump.h"

#include "../game_src/game_lobby.h"
#include "../game_src/commands.h"
#include "../game_src/game_map.h"


#include <utility>
#include <arpa/inet.h>
#include <vector>  


Protocol::Protocol(Socket&& skt) : skt(std::move(skt)) {}

Protocol::Protocol(const std::string& hostname, const std::string& servname) :
skt(hostname.c_str(), servname.c_str()) {}

void Protocol::sendLobby(GameLobby* lobby) {
    checkClosed();
    sendUintEight(SEND_LOBBY);
    sendUintEight(lobby->getTeam());
    sendMapNames(lobby->getMapNames());
}

GameLobby Protocol::receiveLobby() {
    checkClosed();
    uint8_t protocolCode = receiveUintEight();
    uint16_t team = receiveUintEight();
    std::vector<std::string> mapNames = receiveMapNames();
    GameLobby lobby(mapNames, team);
    return lobby;
}

// void Protocol::sendMap(GameMap& gameMap) {
//     checkClosed();
//     sendString(gameMap.getMapName());
//     uint8_t nrOfBeams = gameMap.getNumberOfBeams();
//     sendUintEight(nrOfBeams);

//     std::vector<Beam> beams = gameMap.getBeams(0);
//     for (int j = 0; j < nrOfBeams; j++) {
//         sendBeam(beams[j]);
//     }
// }

// GameMap Protocol::receiveMap() {
//     checkClosed();
//     std::string mapName = receiveString();
//     uint8_t numberOfBeams = receiveUintEight();

//     std::vector<Beam> beams;
//     for (int j = 0; j < numberOfBeams; j++) {
//         Beam beam = receiveBeam(j);
//         beams.push_back(beam);
//     }
//     GameMap gameMap(numberOfBeams, mapName, beams);
//     return gameMap;
// }

void Protocol::sendDynamic(GameDynamic* dynamic) {
    checkClosed();

    sendUintEight(SEND_DYNAMIC); 
    sendUintSixteen(dynamic->getNumberOfWorms());
    sendUintSixteen(dynamic->getWormPlayingID());

    std::vector<WormDTO> worms = dynamic->getWorms();

    for (int i = 0; i < dynamic->getNumberOfWorms(); i++) {
        sendWorm(worms[i]);
    }
}

GameDynamic* Protocol::receiveDynamic() {
    checkClosed();
    uint8_t protocolCode = receiveUintEight();
    uint16_t numberOfWorms = receiveUintSixteen();
    uint16_t wormPlayingID = receiveUintSixteen();

    std::vector<WormDTO> worms;
    for (int i = 0; i < numberOfWorms; i++) {
        WormDTO worm = receiveWorm();
        worms.push_back(worm);
    }
    return new GameDynamic(wormPlayingID, worms);
}

void Protocol::sendSelectMap(SelectMap* selectMap) {
    checkClosed();
    sendUintEight(SEND_COMMAND_SELECT);
    sendUintEight(selectMap->getTeam());
    sendString(selectMap->getMapName());
}

void Protocol::sendMove(Move* move) {
    checkClosed();
    sendUintEight(SEND_COMMAND_MOVE);   
    sendUintEight(move->getID());
    sendUintEight(move->getDir());
}

void Protocol::sendJump(Jump* jump) {
    checkClosed();
    sendUintEight(SEND_COMMAND_JUMP);   
    sendUintEight(jump->getID());
    sendUintEight(jump->getDir());
}

Command* Protocol::receiveCommand() {
    checkClosed();
    uint8_t protocolCode = receiveUintEight();
    if (protocolCode == SEND_COMMAND_MOVE) {
        return receiveMove();
    } else if (protocolCode == SEND_COMMAND_SELECT) {
        return receiveSelectMap();
    } else if (protocolCode == SEND_COMMAND_JUMP) {
        return receiveJump();
    }
    throw std::runtime_error("Invalid Command");
}

// -------------------------Private--------------------------------

void Protocol::sendPosition(Position& pos) {
    sendFloat(pos.getX());
    sendFloat(pos.getY());
}

Position Protocol::receivePosition() {
    float x = receiveFloat();
    float y = receiveFloat();
    return Position(x, y);
}


SelectMap* Protocol::receiveSelectMap() {
    checkClosed();
    uint8_t player = receiveUintEight();
    std::string mapName = receiveString();
    return new SelectMap(NO_WORM_PLAYING, player, mapName);
}

Move* Protocol::receiveMove() {
    checkClosed(); 
    uint8_t wormId = receiveUintEight();
    uint8_t dir = receiveUintEight();
    return new Move(wormId, dir);
}

Jump* Protocol::receiveJump() {
    checkClosed(); 
    uint8_t wormId = receiveUintEight();
    uint8_t dir = receiveUintEight();
    return new Jump(wormId, dir);
}

void Protocol::sendMapNames(std::vector<std::string>& allMaps) {
    checkClosed();
    sendUintSixteen(allMaps.size());
    for (int i = 0; i < allMaps.size(); i++) {
        sendString(allMaps[i]);
    }
}

std::vector<std::string> Protocol::receiveMapNames() {
    checkClosed();
    uint16_t nrOfMaps = receiveUintSixteen();
    std::vector<std::string> allMaps;
    for (int i = 0; i < nrOfMaps; i++) {
        std::string mapName = receiveString();
        allMaps.push_back(mapName);
    }
    return allMaps;
}

void Protocol::sendWorm(WormDTO& worm) {
    sendUintSixteen(worm.getId());
    sendUintSixteen(worm.getTeam());
    sendUintThirtyTwo(worm.getHealth());
    Position pos = worm.getPosition();
    sendPosition(pos);
}

WormDTO Protocol::receiveWorm() {
    uint16_t id = receiveUintSixteen();
    uint16_t team = receiveUintSixteen();
    uint32_t health = receiveUintThirtyTwo();
    Position pos = receivePosition();

    WormDTO worm(id, team, health, pos);
    return worm;
}

void Protocol::sendBeam(BeamDTO& beam) {
    Position beamPosition1 = beam.getPosition1();
    sendPosition(beamPosition1);
    Position beamPosition2 = beam.getPosition2();
    sendPosition(beamPosition2);
    uint8_t beamLength = beam.getBeamLength();
    sendUintEight(beamLength);
}

BeamDTO Protocol::receiveBeam(int id) {
    Position beamPosition1 = receivePosition();
    Position beamPosition2 = receivePosition();
    uint8_t beamLength = receiveUintEight();
    BeamDTO beam(id, beamLength, beamPosition1, beamPosition2);
    return beam;
}


void Protocol::sendFloat(float num) {
    skt.sendall(&num, sizeof(num), &was_closed);
    checkClosed();
}

void Protocol::sendUintEight(uint8_t num) {
    skt.sendall(&num, sizeof(num), &was_closed);
    checkClosed();
}

void Protocol::sendUintSixteen(uint16_t num) {
    uint16_t numHtons = htons(num);
    skt.sendall(&numHtons, sizeof(numHtons), &was_closed);
    checkClosed();
}

void Protocol::sendUintThirtyTwo(uint32_t num) {
    uint32_t numHtonl = htonl(num);
    skt.sendall(&numHtonl, sizeof(numHtonl), &was_closed);
    checkClosed();
}

void Protocol::sendString(const std::string& str) {
    sendUintSixteen(str.size());
    skt.sendall(str.c_str(), str.size(), &was_closed);
    checkClosed();
}

float Protocol::receiveFloat() {
    float num;  
    skt.recvall(&num, sizeof(num), &was_closed);
    checkClosed();
    return num;
}

uint8_t Protocol::receiveUintEight() {
    uint8_t num;
    skt.recvall(&num, sizeof(num), &was_closed);
    checkClosed();
    return num;
}

uint16_t Protocol::receiveUintSixteen() {
    uint16_t num;
    skt.recvall(&num, sizeof(num), &was_closed);
    checkClosed();
    return ntohs(num);
}

uint32_t Protocol::receiveUintThirtyTwo() {
    uint32_t num;
    skt.recvall(&num, sizeof(num), &was_closed);
    checkClosed();
    return ntohl(num);
}


std::string Protocol::receiveString() {
    uint16_t lengthString = receiveUintSixteen();
    std::string str(lengthString, '\0');
    skt.recvall((void*)str.data(), lengthString, &was_closed);
    checkClosed();
    return str;
}

void Protocol::checkClosed() {
    if (was_closed) 
        throw ClosedSocket();
}

void Protocol::boom() {
    was_closed = true;
    skt.shutdown(SHUT_RDWR);
    skt.close();
}

Protocol::~Protocol() {}