#include "protocol.h"

#include "../game_src/commands/command.h"
#include  "../game_src/commands/move.h"
#include  "../game_src/commands/jump.h"
#include "../game_src/commands/launch_bazooka.h"
#include "../game_src/commands/remote_operated.h"
#include "../game_src/commands/hit_upclose.h"
#include "../game_src/commands/throw_grenade.h"
#include "../game_src/commands/cheats.h"
#include "../game_src/commands/match_command.h"
#include "../game_src/commands/drop_dynamite.h"


#include "../game_src/serializable.h"
#include "../game_src/game_dynamic.h"
#include "../game_src/game_map.h"
#include "../game_src/game_info.h"


#include <utility>
#include <arpa/inet.h>
#include <vector>  


Protocol::Protocol(Socket&& skt) : skt(std::move(skt)) {}

Protocol::Protocol(const std::string& hostname, const std::string& servname) :
skt(hostname.c_str(), servname.c_str()) {}

// Protocol::Protocol(const Protocol& protocol) : skt(protocol.getSocket()) {}

void Protocol::sendAllOk(int okCode) {
    checkClosed();
    sendUintEight(SEND_ALL_OK);
    sendUintEight(okCode);
}

int Protocol::receiveAllOk() {
    checkClosed();
    uint8_t protocolCode = receiveUintEight();
    return receiveUintEight();
}

void Protocol::sendMap(GameMap* gameMap) {
    checkClosed();
    sendUintEight(SEND_MAP); 
    sendUintEight(gameMap->getTeam());
    sendUintEight(gameMap->getNumberTeams());
    sendString(gameMap->getMapName());
    sendWorms(gameMap->getWorms());
    sendBeams(gameMap->getBeams());
}

GameMap* Protocol::receiveMap() {
    uint8_t team = receiveUintEight();
    uint8_t numberTeams = receiveUintEight();
    std::string mapName = receiveString();
    std::unordered_map<int, WormDTO> worms = receiveWorms();
    std::vector<BeamDTO> beams = receiveBeams();
    return new GameMap(team, numberTeams, mapName, beams, worms);
}


void Protocol::sendDynamic(GameDynamic* dynamic) {
    checkClosed();
    sendUintEight(SEND_DYNAMIC); 
    sendChar(dynamic->getWormPlayingID());
    sendChar(dynamic->getWinnerTeam());
    sendUintSixteen(dynamic->getTimer());
    sendWorms(dynamic->getWorms());
    sendWeapons(dynamic->getExplosives());
    sendSupplyBox(dynamic->getSupplyBox());
    sendVectorInt(dynamic->getTeamsHealth());
    sendUintEight(dynamic->getStatus());
}

GameDynamic* Protocol::receiveDynamic() {
    checkClosed();
    char wormPlayingID = receiveChar();
    char winnerTeam = receiveChar();
    uint16_t timer = receiveUintSixteen();
    std::unordered_map<int, WormDTO> worms = receiveWorms();
    std::unordered_map<int, ExplosivesDTO> weapons = receiveWeapons();
    std::unordered_map<int, SupplyBoxDTO> supplies = receiveSupplyBox();
    std::vector<uint32_t> teamsHealth = receiveVectorInt();
    uint8_t status = receiveUintEight();
    return new GameDynamic(wormPlayingID, status, winnerTeam, timer, worms, weapons, supplies, teamsHealth);
}

void Protocol::sendInfo(GameInfo* info) {
    checkClosed();
    sendUintEight(SEND_INFO);
    std::map<std::string, std::string> matchesAvailable = info->getMatchesAvailable();
    sendUintEight(matchesAvailable.size());
    for (auto& match: matchesAvailable) {
        sendString(match.first);
        sendString(match.second);
    }
}

GameInfo* Protocol::receiveInfo() {
    checkClosed();
    std::map<std::string, std::string> matchesAvailable;
    int sizeMap = receiveUintEight();
    for (int i=0; i < sizeMap; i++) {
        std::string matchName = receiveString();
        std::string mapName = receiveString();
        matchesAvailable[matchName] = mapName;
    }
    return new GameInfo(matchesAvailable);
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

void Protocol::sendTeleport(RemoteOperated* teleport) {
    checkClosed();
    sendUintEight(SEND_COMMAND_REMOTE_OPERATED);
    sendUintEight(teleport->getID());
    sendUintEight(teleport->getType());
    sendPosition(Position(teleport->getX(), teleport->getY()));
}

void Protocol::sendHitUpclose(HitUpclose* hitUpclose) {
    checkClosed();
    sendUintEight(SEND_COMMAND_HIT_UPCLOSE);
    sendUintEight(hitUpclose->getID());
    sendUintEight(hitUpclose->getDir());
}

void Protocol::sendCheats(Cheats* cheat) {
    checkClosed();
    sendUintEight(SEND_COMMAND_CHEAT);
    sendUintEight(cheat->getID());
    sendUintEight(cheat->getCheatID());
}

void Protocol::sendMatchCommand(MatchCommand* matchCommand) {
    checkClosed();
    sendUintEight(SEND_COMMAND_MATCH);
    sendUintEight(matchCommand->getType());
    sendUintEight(matchCommand->getNrPlayers());
    sendString(matchCommand->getMatchName());
    sendString(matchCommand->getMapName());
}

void Protocol::sendDynamite(DropDynamite* dropDynamite) {
    checkClosed();
    sendUintEight(SEND_COMMAND_DYNAMITE);
    sendUintEight(dropDynamite->getID());
    sendUintEight(dropDynamite->getTimer());
}

void Protocol::sendSerializable(Serializable* serializable) {
    int type = serializable->getSerType();
    if (type == GAME_DYNAMIC) {
        sendDynamic(dynamic_cast<GameDynamic*>(serializable));
    } else if (type == GAME_MAP) {
        sendMap(dynamic_cast<GameMap*>(serializable));
    } else if (type == GAME_INFO) {
        sendInfo(dynamic_cast<GameInfo*>(serializable));
    }
}

std::shared_ptr<Serializable> Protocol::receiveSerializable() {
    checkClosed();
    uint8_t protocolCode = receiveUintEight();
    if (protocolCode == SEND_MAP) {
        return std::shared_ptr<Serializable>(receiveMap());
    } else if (protocolCode == SEND_DYNAMIC) {
        return std::shared_ptr<Serializable>(receiveDynamic());
    } else if (protocolCode == SEND_INFO) {
        return std::shared_ptr<Serializable>(receiveInfo());
    }
    throw std::runtime_error("Invalid Serializable");
}


void Protocol::sendCommand(Command* command) {
    int type = command->getComType();

    if (type == COMMAND_CHEAT) {
        sendCheats(dynamic_cast<Cheats*>(command));
    } else if (type == COMMAND_GRENADE) {
        sendThrowGrenade(dynamic_cast<ThrowGrenade*>(command));
    } else if (type == COMMAND_JUMP) {
        sendJump(dynamic_cast<Jump*>(command));
    } else if (type == COMMAND_MATCH) {
        sendMatchCommand(dynamic_cast<MatchCommand*>(command));
    } else if (type == COMMAND_MOVE) {
        sendMove(dynamic_cast<Move*>(command));
    } else if (type == COMMAND_ROCKET) {
        sendLaunchRocket(dynamic_cast<LaunchRocket*>(command));
    } else if (type == COMMAND_REMOTE_OPERATED) {
        sendTeleport(dynamic_cast<RemoteOperated*>(command));
    } else if (type == COMMAND_HIT_UPCLOSE) {
        sendHitUpclose(dynamic_cast<HitUpclose*>(command));
    } else if (type == COMMAND_DYNAMITE) {
        sendDynamite(dynamic_cast<DropDynamite*>(command));
    }
}

std::shared_ptr<Command> Protocol::receiveCommand() {
    checkClosed();
    uint8_t protocolCode = receiveUintEight();
    if (protocolCode == SEND_COMMAND_MOVE) {
        return receiveMove();
    } else if (protocolCode == SEND_COMMAND_JUMP) {
        return receiveJump();
    } else if (protocolCode == SEND_COMMAND_ROCKET) {
        return receiveLaunchRocket();
    } else if (protocolCode == SEND_COMMAND_REMOTE_OPERATED) {
        return receiveTeoleport();
    } else if (protocolCode == SEND_COMMAND_HIT_UPCLOSE) {
        return receiveHitUpclose();
    } else if (protocolCode == SEND_COMMAND_GRENADE) {
        return receiveThrowGrenade();
    } else if (protocolCode == SEND_COMMAND_CHEAT) {
        return receiveCheats();
    } else if (protocolCode == SEND_COMMAND_MATCH) {
        return receiveMatchCommand();
    } else if (protocolCode == SEND_COMMAND_DYNAMITE) {
        return receiveDynamite();
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


std::shared_ptr<Move> Protocol::receiveMove() {
    checkClosed(); 
    uint8_t wormId = receiveUintEight();
    uint8_t dir = receiveUintEight();
    return std::make_shared<Move>(Move(wormId, dir));
}

std::shared_ptr<Jump> Protocol::receiveJump() {
    checkClosed(); 
    uint8_t wormId = receiveUintEight();
    uint8_t dir = receiveUintEight();
    return std::make_shared<Jump>(Jump(wormId, dir));
}

std::shared_ptr<LaunchRocket> Protocol::receiveLaunchRocket() {
    checkClosed();
    uint8_t type = receiveUintEight();
    uint8_t wormId = receiveUintEight();
    uint8_t dir = receiveUintEight();
    float angle = receiveFloat();
    float power = receiveFloat();
    return std::make_shared<LaunchRocket>(LaunchRocket(type, wormId, dir, angle, power));
}

std::shared_ptr<ThrowGrenade> Protocol::receiveThrowGrenade() {
    checkClosed();
    uint8_t type = receiveUintEight();
    uint8_t wormId = receiveUintEight();
    uint8_t dir = receiveUintEight();
    float angle = receiveFloat();
    float power = receiveFloat();
    int timer = receiveUintEight();
    return std::make_shared<ThrowGrenade>(ThrowGrenade(type, wormId, dir, angle, power, timer));
}

std::shared_ptr<RemoteOperated> Protocol::receiveTeoleport() {
    checkClosed();
    uint8_t wormId = receiveUintEight();
    uint8_t type = receiveUintEight();
    Position pos = receivePosition();
    return std::make_shared<RemoteOperated>(RemoteOperated(wormId, type, pos));
}

std::shared_ptr<HitUpclose> Protocol::receiveHitUpclose() {
    checkClosed();
    uint8_t wormId = receiveUintEight();
    uint8_t dir = receiveUintEight();
    return std::make_shared<HitUpclose>(HitUpclose(wormId, dir));
}

std::shared_ptr<Cheats> Protocol::receiveCheats() {
    checkClosed();
    uint8_t wormId = receiveUintEight();
    uint8_t cheatId = receiveUintEight();
    return std::make_shared<Cheats>(Cheats(wormId, cheatId));
}

std::shared_ptr<MatchCommand> Protocol::receiveMatchCommand() {
    checkClosed();
    uint8_t selectType = receiveUintEight();
    uint8_t nrPlayers = receiveUintEight();
    std::string matchName = receiveString();
    std::string maphName = receiveString();
    return std::make_shared<MatchCommand>(MatchCommand(selectType, nrPlayers, matchName, maphName));
}

std::shared_ptr<DropDynamite> Protocol::receiveDynamite() {
    checkClosed();
    uint8_t wormID = receiveUintEight();
    uint8_t timer = receiveUintEight();
    return std::make_shared<DropDynamite>(DropDynamite(wormID, timer));
}

void Protocol::sendVectorStr(std::vector<std::string> allMaps) {
    checkClosed();
    sendUintSixteen(allMaps.size());
    for (int i = 0; i < allMaps.size(); i++) {
        sendString(allMaps[i]);
    }
}

std::vector<std::string> Protocol::receiveVectorStr() {
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


void Protocol::sendSupplyBox(std::unordered_map<int, SupplyBoxDTO> supplyBoxes) {
    sendUintEight(supplyBoxes.size());
    for (auto& supplyBox : supplyBoxes) {
        sendUintEight(supplyBox.first);
        sendUintEight(supplyBox.second.getContent());
        sendUintEight(supplyBox.second.isFalling());
        sendPosition(Position(supplyBox.second.getX(), supplyBox.second.getY()));
    }
}


std::unordered_map<int, SupplyBoxDTO> Protocol::receiveSupplyBox() {
    uint8_t supplyBoxSize = receiveUintEight();
    std::unordered_map<int, SupplyBoxDTO> supplyBoxes;
    for (int i = 0; i < supplyBoxSize; i++) {
        int id = receiveUintEight();
        int content = receiveUintEight();
        int falling = receiveUintEight();
        Position pos = receivePosition();
        supplyBoxes.emplace(id, SupplyBoxDTO(id, content, falling, pos));
    }
    return supplyBoxes;
}


void Protocol::sendWorms(std::unordered_map<int, WormDTO> worms) {
    sendUintEight(worms.size());
    for (auto& worm : worms) {
        sendUintEight(worm.first);
        sendUintEight(worm.second.getDir());
        sendUintEight(worm.second.getTeam());
        sendUintEight(worm.second.getHealth());
        sendFloat(worm.second.getVelX());
        sendFloat(worm.second.getVelY());
        sendUintEight(worm.second.isOnGround());
        sendUintEight(worm.second.getCurrentAction());
        sendPosition(Position(worm.second.getX(), worm.second.getY()));
        sendWeaponsMap(worm.second.getWeapons());
    }

}

std::unordered_map<int, WormDTO> Protocol::receiveWorms() {
    uint8_t numberOfWorms = receiveUintEight();
    std::unordered_map<int, WormDTO> worms; 
    for (int i = 0; i < numberOfWorms; i++) {
        uint8_t id = receiveUintEight();
        uint8_t dir = receiveUintEight();
        uint8_t team = receiveUintEight();
        uint8_t health = receiveUintEight();
        float velX = receiveFloat();
        float velY = receiveFloat();
        uint8_t onGround = receiveUintEight();
        uint8_t currentAction = receiveUintEight();
        Position pos = receivePosition();
        std::vector<int> weapons = receiveWeaponsMap();
        worms.emplace(id, WormDTO(id, dir, team, health, velX, velY, onGround, currentAction, pos, weapons));
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

void Protocol::sendVectorInt(std::vector<uint32_t> vector) {
    sendUintEight(vector.size());
    for (int i = 0; i < vector.size(); i++) {
        sendUintThirtyTwo(vector[i]);
    }
}

std::vector<uint32_t> Protocol::receiveVectorInt() {
    uint8_t vectorSize = receiveUintEight();
    std::vector<uint32_t> vector;
    for (int i = 0; i < vectorSize; i++) {
        uint32_t number = receiveUintThirtyTwo();
        vector.push_back(number);
    }
    return vector;
}

void Protocol::sendFloat(float num) {
    uint32_t num32 = *reinterpret_cast<uint32_t*>(&num);
    sendUintThirtyTwo(num32);
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
    uint32_t num32 = receiveUintThirtyTwo();
    float num = *reinterpret_cast<float*>(&num32); 
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