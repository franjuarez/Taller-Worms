#include "protocol.h"

#include "../game_src/commands/command.h"
#include  "../game_src/commands/move.h"
#include  "../game_src/commands/jump.h"
#include "../game_src/commands/launch_bazooka.h"
#include "../game_src/commands/teleport.h"
#include "../game_src/commands/hit_upclose.h"
#include "../game_src/commands/throw_grenade.h"

#include "../game_src/serializable.h"
#include "../game_src/game_dynamic.h"
#include "../game_src/game_map.h"


#include <utility>
#include <arpa/inet.h>
#include <vector>  


Protocol::Protocol(Socket&& skt) : skt(std::move(skt)) {}

Protocol::Protocol(const std::string& hostname, const std::string& servname) :
skt(hostname.c_str(), servname.c_str()) {}


void Protocol::sendMap(GameMap* gameMap) {
    checkClosed();
    sendUintEight(SEND_MAP); 
    sendUintEight(gameMap->getTeam());
    sendString(gameMap->getMapName());
    sendWorms(gameMap->getWorms());
    sendBeams(gameMap->getBeams());
}

GameMap* Protocol::receiveMap() {
    uint8_t team = receiveUintEight();
    std::string mapName = receiveString();
    std::vector<WormDTO> worms = receiveWorms();
    std::vector<BeamDTO> beams = receiveBeams();
    return new GameMap(team, mapName, beams, worms);
}


void Protocol::sendDynamic(GameDynamic* dynamic) {
    checkClosed();
    sendUintEight(SEND_DYNAMIC); 
    sendChar(dynamic->getWormPlayingID());
    sendChar(dynamic->getWinnerTeam());
    sendWorms(dynamic->getWorms());
    sendWeapons(dynamic->getExplosives());
}

GameDynamic* Protocol::receiveDynamic() {
    checkClosed();
    char wormPlayingID = receiveChar();
    char winnerTeam = receiveChar();
    std::vector<WormDTO> worms = receiveWorms();
    std::unordered_map<int, ExplosivesDTO> weapons = receiveWeapons();
    return new GameDynamic(wormPlayingID, winnerTeam, worms, weapons);
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

void Protocol::sendLaunchRocket(LaunchRocket* attack) {
    checkClosed();
    sendUintEight(SEND_COMMAND_ROCKET);   
    sendUintEight(attack->getType());
    sendUintEight(attack->getID());
    sendUintEight(attack->getDir());
    sendFloat(attack->getAngle());
    sendFloat(attack->getPower());
}

void Protocol::sendThrowGrenade(ThrowGrenade* attack) {
    checkClosed();
    sendUintEight(SEND_COMMAND_GRENADE);   
    sendUintEight(attack->getType());
    sendUintEight(attack->getID());
    sendUintEight(attack->getDir());
    sendFloat(attack->getAngle());
    sendFloat(attack->getPower());
    sendUintEight(attack->getTimer());
}

void Protocol::sendTeleport(Teleport* teleport) {
    checkClosed();
    sendUintEight(SEND_COMMAND_TELEPORT);
    sendUintEight(teleport->getID());
    sendPosition(Position(teleport->getX(), teleport->getY()));
}

void Protocol::sendHitUpclose(HitUpclose* hitUpclose) {
    checkClosed();
    sendUintEight(SEND_COMMAND_HIT_UPCLOSE);
    sendUintEight(hitUpclose->getID());
}

Serializable* Protocol::receiveSerializable() {
    checkClosed();
    uint8_t protocolCode = receiveUintEight();
    if (protocolCode == SEND_MAP) {
        return receiveMap();
    } else if (protocolCode == SEND_DYNAMIC) {
        return receiveDynamic();
    }
    throw std::runtime_error("Invalid Serializable");
}

Command* Protocol::receiveCommand() {
    checkClosed();
    uint8_t protocolCode = receiveUintEight();
    if (protocolCode == SEND_COMMAND_MOVE) {
        return receiveMove();
    } else if (protocolCode == SEND_COMMAND_JUMP) {
        return receiveJump();
    } else if (protocolCode == SEND_COMMAND_ROCKET) {
        return receiveLaunchRocket();
    } else if (protocolCode == SEND_COMMAND_TELEPORT) {
        return receiveTeoleport();
    } else if (protocolCode == SEND_COMMAND_HIT_UPCLOSE) {
        return receiveHitUpclose();
    } else if (protocolCode == SEND_COMMAND_GRENADE) {
        return receiveThrowGrenade();
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

LaunchRocket* Protocol::receiveLaunchRocket() {
    checkClosed();
    uint8_t type = receiveUintEight();
    uint8_t wormId = receiveUintEight();
    uint8_t dir = receiveUintEight();
    float angle = receiveFloat();
    float power = receiveFloat();
    return new LaunchRocket(type, wormId, dir, angle, power);
}

ThrowGrenade* Protocol::receiveThrowGrenade() {
    checkClosed();
    uint8_t type = receiveUintEight();
    uint8_t wormId = receiveUintEight();
    uint8_t dir = receiveUintEight();
    float angle = receiveFloat();
    float power = receiveFloat();
    int timer = receiveUintEight();
    return new ThrowGrenade(type, wormId, dir, angle, power, timer);
}

Teleport* Protocol::receiveTeoleport() {
    checkClosed();
    uint8_t wormId = receiveUintEight();
    Position pos = receivePosition();
    return new Teleport(wormId, pos);
}

HitUpclose* Protocol::receiveHitUpclose() {
    checkClosed();
    uint8_t wormId = receiveUintEight();
    return new HitUpclose(wormId);
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

void Protocol::sendWeapons(std::unordered_map<int, ExplosivesDTO> weapons) {
    sendUintEight(weapons.size());
    for (auto& weapon : weapons ) {
        sendUintEight(weapon.second.getType());
        sendUintEight(weapon.first);
        sendFloat(weapon.second.getVelX());
        sendFloat(weapon.second.getVelY());
        sendPosition(Position(weapon.second.getX(), weapon.second.getY()));
    }
}

std::unordered_map<int, ExplosivesDTO> Protocol::receiveWeapons() {
   uint8_t numberOfExplosives = receiveUintEight();
   std::unordered_map<int, ExplosivesDTO> weapons;
   for (int i = 0; i < numberOfExplosives; i++) {
       int type = receiveUintEight();
       int id = receiveUintEight();
       float velX = receiveFloat();
       float velY = receiveFloat();
       Position pos = receivePosition();
       weapons.emplace(id, ExplosivesDTO(type, id, pos, velX, velY));  
   }
   return weapons;
}



void Protocol::sendWorms(std::vector<WormDTO> worms) {
    sendUintEight(worms.size());
    for (int i = 0; i < worms.size(); i++) {
        sendUintEight(worms[i].getId());
        sendUintEight(worms[i].getDir());
        sendUintEight(worms[i].getTeam());
        sendUintEight(worms[i].getHealth());
        sendPosition(Position(worms[i].getX(), worms[i].getY()));
        sendWeaponsMap(worms[i].getWeapons());
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
        std::vector<int> weapons = receiveWeaponsMap();
        WormDTO worm(id, dir, team, health, pos, weapons);
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

void Protocol::sendWeaponsMap(std::vector<int> weapons) {
    sendUintEight(weapons.size());
    for (int i = 0; i < weapons.size(); i++) {
        sendChar(weapons[i]);
    }
}

std::vector<int> Protocol::receiveWeaponsMap() {
    uint8_t weaponQuantity = receiveUintEight();
    std::vector<int>  weaponsMap;
    for (int i = 0; i < weaponQuantity; i++) {
        char amunition = receiveChar();
        weaponsMap.push_back(amunition);
    }
    return weaponsMap;
}

void Protocol::sendFloat(float num) {
    skt.sendall(&num, sizeof(num), &was_closed);
    checkClosed();
    // arreglar la falopeada de hacer htons y castear
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


void Protocol::sendChar(char c) {
    skt.sendall(&c, sizeof(c), &was_closed);
    checkClosed();
}

char Protocol::receiveChar() {
    char c;
    skt.recvall(&c, sizeof(c), &was_closed);
    checkClosed();
    return c;
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