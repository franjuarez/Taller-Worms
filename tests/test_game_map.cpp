
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <vector>
#include "../shared_src/protocol.h"
#include "../shared_src/socket.h"
#include "../game_src/beam_dto.h"
#include "../game_src/worm_dto.h"
#include "../game_src/game_map.h"
#include "../game_src/serializable.h"

Socket mockServerS("1233");
Protocol mockClient("localhost", "1233");
Socket peer = mockServerS.accept();
Protocol mockServer(std::move(peer));

std::string mapName = "small";
int numTeams = 2;
std::vector<BeamDTO> beams;
std::unordered_map<int, WormDTO> worms = {};


TEST_CASE("Testing sending a GameMap") {
    Position pos(9.7, 11.0);
    Position pos2(9.89, 9.1);


    WormDTO w2(2, 0, 1, 100, 0.9, 4.0, 1, 0, pos, {});
    WormDTO w1(1, 1, 2,  0, 0.0, 0.333, 0, 0, pos2, {});
    worms.emplace(2, w2);
    worms.emplace(1, w1);

    beams.push_back(BeamDTO(6, Position(10.0f, 10.0f), 0));
    beams.push_back(BeamDTO(3, Position(16.0f, 8.0f), 0));
    beams.push_back(BeamDTO(3, Position(16.0f, 25.0f), 0));

    GameMap* gameMapSent = new GameMap(1, numTeams, mapName, beams, worms);

    gameMapSent->send(mockServer);
    std::shared_ptr<Serializable>serializableReceived(mockClient.receiveSerializable());
    std::shared_ptr<GameMap> gameMapReceived = std::dynamic_pointer_cast<GameMap>(serializableReceived);

    REQUIRE(gameMapReceived->getTeam() == gameMapSent->getTeam());
    REQUIRE(gameMapReceived->getMapName() == gameMapSent->getMapName());
    REQUIRE(gameMapReceived->getNumberTeams() == gameMapSent->getNumberTeams());
    REQUIRE(gameMapReceived->getNumberOfBeams() == gameMapSent->getNumberOfBeams());
    REQUIRE(gameMapReceived->getNumberOfWorms() == gameMapSent->getNumberOfWorms());

}

TEST_CASE("Testing the worms sent and received in the GameMap", "[info]") {
    Position pos(-9.7, 11.0);
    Position pos2(9.89, -9.1);

    WormDTO w2(2, 0, 1, 100, 0.9, 4.0, 1, 0, pos, {});
    WormDTO w1(1, 1, 2,  0, 0.0, 0.333, 0, 0, pos2, {});
    worms.emplace(2, w2);
    worms.emplace(1, w1);

    GameMap* gameMapSent = new GameMap(1, numTeams, mapName, beams, worms);

    gameMapSent->send(mockServer);
    std::shared_ptr<Serializable>serializableReceived(mockClient.receiveSerializable());
    std::shared_ptr<GameMap> gameMapReceived = std::dynamic_pointer_cast<GameMap>(serializableReceived);

    REQUIRE(gameMapReceived->getNumberOfWorms() == gameMapSent->getNumberOfWorms());

    std::unordered_map<int, WormDTO> wormsReceived = gameMapReceived->getWorms(); 

    for(auto& worm : wormsReceived) {
        auto wormS = worms.find(worm.first);
        REQUIRE(worm.second.getId() == wormS->second.getId());
        REQUIRE(worm.second.getDir() == wormS->second.getDir());
        REQUIRE(worm.second.getX() == wormS->second.getX());
        REQUIRE(worm.second.getY() == wormS->second.getY());
        REQUIRE(worm.second.getHealth() == wormS->second.getHealth());
        REQUIRE(worm.second.isAlive() == wormS->second.isAlive());
        REQUIRE(worm.second.getVelX() == wormS->second.getVelX());
        REQUIRE(worm.second.getVelY() == wormS->second.getVelY());
        REQUIRE(worm.second.isOnGround() == wormS->second.isOnGround());
        REQUIRE(worm.second.getCurrentAction() == wormS->second.getCurrentAction());
        REQUIRE(worm.second.getWeapons().size() == wormS->second.getWeapons().size());
    }
}

TEST_CASE("Testing the beams sent and received in GameMap", "[info]") {
    beams.push_back(BeamDTO(6, Position(10.0f, 10.0f), 20));
    beams.push_back(BeamDTO(3, Position(16.0f, 8.0f), -13));
    beams.push_back(BeamDTO(3, Position(16.0f, 25.0f), 180));

    GameMap* gameMapSent = new GameMap(1, numTeams, mapName, beams, worms);

    gameMapSent->send(mockServer);
    std::shared_ptr<Serializable>serializableReceived(mockClient.receiveSerializable());
    std::shared_ptr<GameMap> gameMapReceived = std::dynamic_pointer_cast<GameMap>(serializableReceived);

    REQUIRE(gameMapReceived->getNumberOfBeams() == gameMapSent->getNumberOfBeams());

    std::vector<BeamDTO> beamsReceived = gameMapReceived->getBeams();
    for(int i = 0; i < gameMapSent->getNumberOfBeams(); i++) {
        SECTION("BeamsInfo") {
            CAPTURE(i);
            REQUIRE(beamsReceived[i].getBeamLength() == beams[i].getBeamLength());
            REQUIRE(beamsReceived[i].getAngle() == beams[i].getAngle());
            REQUIRE(beamsReceived[i].getX() == beams[i].getX());
            REQUIRE(beamsReceived[i].getY() == beams[i].getY());
        }
    }
}

TEST_CASE("The amunition sent and received in WormsDTO", "[info]") {
    Position pos(-9.7, .0);
    Position pos2(9.89, -9.1);

    WormDTO w2(2, 0, 1, 100, 0.9, 4.0, 1, 0, pos, {});
    WormDTO w1(1, 1, 2,  0, 0.0, 0.333, 0, 0, pos2, {});
    worms.emplace(2, w2);
    worms.emplace(1, w1);

    GameMap* gameMapSent = new GameMap(1, numTeams, mapName, beams, worms);

    gameMapSent->send(mockServer);
    std::shared_ptr<Serializable>serializableReceived(mockClient.receiveSerializable());
    std::shared_ptr<GameMap> gameMapReceived = std::dynamic_pointer_cast<GameMap>(serializableReceived);

    REQUIRE(gameMapReceived->getNumberOfWorms() == gameMapSent->getNumberOfWorms());

    std::unordered_map<int, WormDTO> wormsReceived = gameMapReceived->getWorms(); 

    for(auto& wormR : wormsReceived) {
        auto wormS = worms.find(wormR.first);
        REQUIRE(wormR.second.getWeapons().size() == wormS->second.getWeapons().size());
        std::vector<int> weaponsSent = wormS->second.getWeapons();
        std::vector<int> weaponsReceived = wormR.second.getWeapons();

        for(int i = 0; i < weaponsSent.size(); i++){
            CAPTURE(i);
            REQUIRE(weaponsReceived[i] == weaponsSent[i]);

        }
    }
}
