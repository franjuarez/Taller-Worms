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
        sendString(allMaps[i].getMapName());
        uint16_t nrOfBeams = allMaps[i].getNumberOfBeams();
        sendUintSixteen(nrOfBeams);

        for (int j = 0; j < nrOfBeams; j++) {
            Position beamPosition1 = allMaps[i].getBeamPosition1(j);
            sendPosition(beamPosition1);
            Position beamPosition2 = allMaps[i].getBeamPosition2(j);
            sendPosition(beamPosition2);
            uint16_t beamLength = allMaps[i].getBeamLength(j);
            sendUintSixteen(beamLength);
        }
    }
}

void Protocol::sendDynamic(GameDynamic& gameDynamic) {
    checkClosed();

    sendUintEight(SEND_DYNAMIC); 
    sendUintSixteen(gameDynamic.getNumberOfWorms());
    sendUintSixteen(gameDynamic.getWormPlayingID());

    std::vector<Worm*> worms = gameDynamic.getWorms();

    for (int i = 0; i < gameDynamic.getNumberOfWorms(); i++) {
        sendUintSixteen(worms[i]->getId());
        sendUintSixteen(worms[i]->getTeam());
        sendUintThirtyTwo(worms[i]->getHealth());
        Position pos = worms[i]->getPosition();
        sendPosition(pos);
    }
}

GameDynamic Protocol::receiveDynamic() {
    checkClosed();
    uint8_t protocolCode = receiveUintEight();
    uint16_t numberOfWorms = receiveUintSixteen();
    uint16_t wormPlayingID = receiveUintSixteen();

    GameDynamic gameDynamic(wormPlayingID);
    for (int i = 0; i < numberOfWorms; i++) {
        uint16_t id = receiveUintSixteen();
        uint16_t team = receiveUintSixteen();
        uint32_t health = receiveUintThirtyTwo();
        Position pos = receivePosition();

        Worm worm(id, team, health, pos);
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