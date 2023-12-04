
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
    for(int i = 0; i < gameMapSent->getNumberOfWorms(); i++) {
        SECTION("WormInfo"){        
            CAPTURE(i);

            REQUIRE(wormsReceived[i].getId() == worms[i].getId());
            REQUIRE(wormsReceived[i].getDir() == worms[i].getDir());
            REQUIRE(wormsReceived[i].getX() == worms[i].getX());
            REQUIRE(wormsReceived[i].getY() == worms[i].getY());
            REQUIRE(wormsReceived[i].getHealth() == worms[i].getHealth());
            REQUIRE(wormsReceived[i].isAlive() == worms[i].isAlive());
            REQUIRE(wormsReceived[i].getVelX() == worms[i].getVelX());
            REQUIRE(wormsReceived[i].getVelY() == worms[i].getVelY());
            REQUIRE(wormsReceived[i].isOnGround() == worms[i].isOnGround());
            REQUIRE(wormsReceived[i].getCurrentAction() == worms[i].getCurrentAction());
            REQUIRE(wormsReceived[i].getWeapons().size() == worms[i].getWeapons().size());
        }
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
    for(int i = 0; i < gameMapSent->getNumberOfWorms(); i++) {
        SECTION("WormInfo"){        
            CAPTURE(i);
            REQUIRE(wormsReceived[i].getWeapons().size() == worms[i].getWeapons().size());
            SECTION("WeaponsInfo") {
                std::vector<int> weaponsSent = worms[i].getWeapons();
                std::vector<int> weaponsReceived = wormsReceived[i].getWeapons();

                for(int j = 0; j < weaponsSent.size(); j++){
                    CAPTURE(j);
                    REQUIRE(weaponsReceived[j] == weaponsSent[j]);

                }
            }
        }
    }
}
