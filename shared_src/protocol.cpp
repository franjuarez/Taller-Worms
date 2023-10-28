#include "protocol.h"
#include "socket.h"
#include "constants.h"
#include "../game_src/game_map.h"
#include "../game_src/game_dynamic.h"
#include  "../game_src/worm.h"

#include <utility>
#include <arpa/inet.h>
#include <vector>  


Protocol::Protocol(Socket&& skt) : skt(std::move(skt)) { was_closed = false;}

Protocol::Protocol(const std::string& servname, const std::string& hostname ) :
skt(servname.c_str(), hostname.c_str()) {}

void Protocol::sendMaps(std::vector<GameMap>& allMaps) {
    checkClosed();
    sendUintEight(SEND_MAP);
    uint16_t nrOfMaps = allMaps.size();
    sendUintSixteen(nrOfMaps);

    for (int i = 0; i < allMaps.size(); i++) {
        sendMap(allMaps[i]);
    }
}

void Protocol::sendDynamic(GameDynamic& gameDynamic) {
    checkClosed();

    sendUintEight(SEND_DYNAMIC); 
    sendUintSixteen(gameDynamic.getNumberOfWorms());
    sendUintSixteen(gameDynamic.getWormPlayingID());

    std::vector<Worm*> worms = gameDynamic.getWorms();

    for (int i = 0; i < gameDynamic.getNumberOfWorms(); i++) {
        sendWorm(*worms[i]);
    }
}

GameDynamic Protocol::receiveDynamic() {
    checkClosed();
    uint8_t protocolCode = receiveUintEight();
    uint16_t numberOfWorms = receiveUintSixteen();
    uint16_t wormPlayingID = receiveUintSixteen();

    GameDynamic gameDynamic(wormPlayingID);
    for (int i = 0; i < numberOfWorms; i++) {
        Worm worm = receiveWorm();
        gameDynamic.addWorm(&worm);
    }
    return gameDynamic;
}

std::vector<GameMap> Protocol::receiveMaps() {
    checkClosed();
    std::vector<GameMap> allMaps;
    uint8_t protocolCode = receiveUintEight();
    uint16_t numberOfMaps = receiveUintSixteen();

    for (int i = 0; i < numberOfMaps; i++) {
        GameMap gameMap = receiveMap(i);
        allMaps.push_back(gameMap);
    }
    return allMaps;
}

void Protocol::sendPosition(Position& pos) {
    sendUintThirtyTwo(pos.getX());
    sendUintThirtyTwo(pos.getY());
}

Position Protocol::receivePosition() {
    uint16_t x = receiveUintThirtyTwo();
    uint16_t y = receiveUintThirtyTwo();
    return Position(x, y);
}

void Protocol::sendWorm(Worm& worm) {
    sendUintSixteen(worm.getId());
    sendUintSixteen(worm.getTeam());
    sendUintThirtyTwo(worm.getHealth());
    Position pos = worm.getPosition();
    sendPosition(pos);
}

Worm Protocol::receiveWorm() {
    uint16_t id = receiveUintSixteen();
    uint16_t team = receiveUintSixteen();
    uint32_t health = receiveUintThirtyTwo();
    Position pos = receivePosition();

    Worm worm(id, team, health, pos);
    return worm;
}

void Protocol::sendBeam(Beam& beam) {
    Position beamPosition1 = beam.getPosition1();
    sendPosition(beamPosition1);
    Position beamPosition2 = beam.getPosition2();
    sendPosition(beamPosition2);
    uint16_t beamLength = beam.getBeamLength();
    sendUintSixteen(beamLength);
}

void Protocol::sendMap(GameMap& gameMap) {
    checkClosed();
    sendString(gameMap.getMapName());
    uint16_t nrOfBeams = gameMap.getNumberOfBeams();
    sendUintSixteen(nrOfBeams);

    // for (int j = 0; j < nrOfBeams; j++) {
    //     sendBeam(gameMap.getBeam(j));
    // }
}

GameMap Protocol::receiveMap(int i) {
    checkClosed();
    std::string mapName = receiveString();
    GameMap gameMap(i, mapName);
    uint16_t numberOfBeams = receiveUintSixteen();

    for (int j = 0; j < numberOfBeams; j++) {
        Position beamPosition1 = receivePosition();
        Position beamPosition2 = receivePosition();
        uint16_t beamLength = receiveUintSixteen();
        Beam beam(j, beamLength, beamPosition1, beamPosition2);
        gameMap.addBeam(j, &beam);
    }

    return gameMap;
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
    skt.sendall(str.c_str(), str.size(), &was_closed);
    checkClosed();
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
    uint32_t lengthString = receiveUintSixteen();
    std::string str(lengthString, '\0');
    skt.recvall(str.data(), lengthString, &was_closed);
    checkClosed();
    return str;
}

void Protocol::checkClosed() {
    if (was_closed) 
        throw ClosedSocket();
}

void Protocol::boom() {
    was_closed = true;
    skt.shutdown(2);
    skt.close();
}


Protocol::~Protocol() {}