#include "protocol.h"

#include "../game_src/commands.h"
#include "../game_src/select_map.h"
#include  "../game_src/move.h"
#include  "../game_src/jump.h"

#include "../game_src/game_lobby.h"
#include "../game_src/game_dynamic.h"
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

GameLobby* Protocol::receiveLobby() {
    checkClosed();
    uint8_t protocolCode = receiveUintEight();
    uint8_t team = receiveUintEight();
    std::vector<std::string> mapNames = receiveMapNames();
    return new GameLobby(mapNames, team);
}

void Protocol::sendMap(GameMap* gameMap) {
    checkClosed();
    sendUintEight(SEND_MAP); 
    sendString(gameMap->getMapName());

    sendWorms(gameMap->getWorms());

    sendBeams(gameMap->getBeams());
}

GameMap* Protocol::receiveMap() {
    uint8_t protocolCode = receiveUintEight();
    std::string mapName = receiveString();
    std::vector<WormDTO> worms = receiveWorms();
    std::vector<BeamDTO> beams = receiveBeams();
    return new GameMap(mapName, beams, worms);
}


void Protocol::sendDynamic(GameDynamic* dynamic) {
    checkClosed();
    sendUintEight(SEND_DYNAMIC); 
    sendUintEight(dynamic->getWormPlayingID());
    sendWorms(dynamic->getWorms());
    sendProjectiles(dynamic->getProjectiles());
}

GameDynamic* Protocol::receiveDynamic() {
    checkClosed();
    uint8_t protocolCode = receiveUintEight();
    uint8_t wormPlayingID = receiveUintEight();

    std::vector<WormDTO> worms = receiveWorms();
    std::vector<ProjectileDTO> projectiles = receiveProjectiles();
    return new GameDynamic(wormPlayingID, worms, projectiles);
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

void Protocol::sendPosition(Position pos) {
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

void Protocol::sendProjectiles(std::vector<ProjectileDTO> projectiles) {
    sendUintEight(projectiles.size());
    for (int i = 0; i < projectiles.size(); i++) {
        sendUintEight(projectiles[i].getType());
        sendFloat(projectiles[i].getVelX());
        sendFloat(projectiles[i].getVelY());
        sendPosition(Position(projectiles[i].getX(), projectiles[i].getY()));
    }
}

std::vector<ProjectileDTO> Protocol::receiveProjectiles() {
    uint8_t numberOfProjectiles = receiveUintEight();
    std::vector<ProjectileDTO> projectiles;
    for (int i = 0; i < numberOfProjectiles; i++) {
        int type = receiveUintEight();
        float velX = receiveFloat();
        float velY = receiveFloat();
        Position pos = receivePosition();
        ProjectileDTO projectile(type, pos, velX, velY);
        projectiles.push_back(projectile);    
    }
    return projectiles;
}


void Protocol::sendWorms(std::vector<WormDTO> worms) {
    sendUintEight(worms.size());
    for (int i = 0; i < worms.size(); i++) {
        sendUintEight(worms[i].getId());
        sendUintEight(worms[i].getDir());
        sendUintEight(worms[i].getTeam());
        sendUintEight(worms[i].getHealth());
        sendPosition(Position(worms[i].getX(), worms[i].getY()));
    }

}

std::vector<WormDTO> Protocol::receiveWorms() {
    uint8_t numberOfWorms = receiveUintEight();
    std::vector<WormDTO> worms; 
    for (int i = 0; i < numberOfWorms; i++) {
        uint8_t id = receiveUintEight();
        uint8_t dir = receiveUintEight();
        uint8_t team = receiveUintEight();
        uint8_t health = receiveUintEight();
        Position pos = receivePosition();
        WormDTO worm(id, dir, team, health, pos);
        worms.push_back(worm);
    }
    return worms;
}

void Protocol::sendBeams(std::vector<BeamDTO> beams) {
    sendUintEight(beams.size());
    for (int i = 0; i < beams.size(); i++) {
        sendUintEight(beams[i].getBeamLength());
        sendFloat(beams[i].getAngle());
        sendPosition(Position(beams[i].getX(), beams[i].getY()));
    }
}

std::vector<BeamDTO> Protocol::receiveBeams() {
    uint8_t numberOfBeams = receiveUintEight();
    std::vector<BeamDTO> beams; 
    for (int i = 0; i < numberOfBeams; i++) {
        uint8_t beamLength = receiveUintEight();
        float angle = receiveFloat();
        Position beamPosition1 = receivePosition();
        BeamDTO beam(beamLength, beamPosition1, angle);
        beams.push_back(beam);
    }
    return beams;
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