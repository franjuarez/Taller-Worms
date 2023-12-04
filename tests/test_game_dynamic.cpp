#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <vector>
#include <map>
#include "../shared_src/protocol.h"
#include "../shared_src/socket.h"
#include "../game_src/game_dynamic.h"
#include "../game_src/explosives_dto.h"
#include "../game_src/constants_game.h"
#include "../game_src/worm_dto.h"
#include "../game_src/serializable.h"
#include "../game_src/supply_box_dto.h"


Socket mockServerS2("1230");
Protocol mockClient2("localhost", "1230");
Socket peer2 = mockServerS2.accept();
Protocol mockServer2(std::move(peer2));

std::string mapName2 = "small";
int numTeams2 = 2;
std::unordered_map<int, WormDTO> worms2 = {};
std::unordered_map<int, ExplosivesDTO> explosives = {};
std::unordered_map<int, SupplyBoxDTO> supplies = {};
std::vector<uint32_t> teamsHealth = {};

TEST_CASE("Sending and receiving a GameDynamic") {

    Position pos(9.7, 11.0);
    Position pos2(9.89, 9.1);
    WormDTO w2(2, 0, 1, 100, 0.9, 4.0, 1, STANDING, pos, {});
    WormDTO w1(1, 1, 2,  0, 0.0, 0.333, 0, MOVING, pos2, {});
    worms2.emplace(2, w2);
    worms2.emplace(1, w1);


    GameDynamic* gameDynamicSent = new GameDynamic(1, 1, -1, worms2, explosives, supplies, teamsHealth);

    gameDynamicSent->send(mockServer2);

    std::shared_ptr<Serializable>serializableReceived(mockClient2.receiveSerializable());
    std::shared_ptr<GameDynamic> gameDynamicReceived = std::dynamic_pointer_cast<GameDynamic>(serializableReceived);

    REQUIRE(gameDynamicReceived->getWormPlayingID() == gameDynamicSent->getWormPlayingID());
    REQUIRE(gameDynamicReceived->getStatus() == gameDynamicSent->getStatus());
    REQUIRE(gameDynamicReceived->getWinnerTeam() == gameDynamicSent->getWinnerTeam());
    REQUIRE(gameDynamicReceived->getExplosives().size() == gameDynamicSent->getExplosives().size());
    REQUIRE(gameDynamicReceived->getSupplyBox().size() == gameDynamicSent->getSupplyBox().size());
    REQUIRE(gameDynamicReceived->getWorms().size() == gameDynamicSent->getWorms().size());
}

TEST_CASE("Testing the worms sent and received in the GameDynamic", "[info]") {
    Position pos(-9.7, 11.0);
    Position pos2(9.89, -9.1);

    WormDTO w2(2, 0, 1, 100, 0.9, 4.0, 1, STANDING, pos, {});
    WormDTO w1(1, 1, 2,  0, 0.0, 0.333, 0, MOVING, pos2, {});
    worms2.emplace(2, w2);
    worms2.emplace(1, w1);

    GameDynamic* gameDynamicSent = new GameDynamic(1, 1, -1, worms2, explosives, supplies, teamsHealth);

    gameDynamicSent->send(mockServer2);

    std::shared_ptr<Serializable>serializableReceived(mockClient2.receiveSerializable());
    std::shared_ptr<GameDynamic> gameDynamicReceived = std::dynamic_pointer_cast<GameDynamic>(serializableReceived);

    REQUIRE(gameDynamicReceived->getWorms().size() == gameDynamicSent->getWorms().size());

    std::unordered_map<int, WormDTO> wormsReceived = gameDynamicReceived->getWorms(); 
    for(int i = 0; i < gameDynamicReceived->getWorms().size(); i++) {
        SECTION("WormInfo"){        
            CAPTURE(i);

            REQUIRE(wormsReceived[i].getId() == worms2[i].getId());
            REQUIRE(wormsReceived[i].getDir() == worms2[i].getDir());
            REQUIRE(wormsReceived[i].getX() == worms2[i].getX());
            REQUIRE(wormsReceived[i].getY() == worms2[i].getY());
            REQUIRE(wormsReceived[i].getHealth() == worms2[i].getHealth());
            REQUIRE(wormsReceived[i].isAlive() == worms2[i].isAlive());
            REQUIRE(wormsReceived[i].getVelX() == worms2[i].getVelX());
            REQUIRE(wormsReceived[i].getVelY() == worms2[i].getVelY());
            REQUIRE(wormsReceived[i].isOnGround() == worms2[i].isOnGround());
            REQUIRE(wormsReceived[i].getCurrentAction() == worms2[i].getCurrentAction());
            REQUIRE(wormsReceived[i].getWeapons().size() == worms2[i].getWeapons().size());
        }
    }

}

TEST_CASE("The amunition sent and received in WormsDTO through GameDynamic", "[info]") {
    Position pos(-9.7, .0);
    Position pos2(9.89, -9.1);

    WormDTO w2(2, 0, 1, 100, 0.9, 4.0, 1, STANDING, pos,  {0,1,7,0,1});
    WormDTO w1(1, 1, 2,  0, 0.0, 0.333, 0, MOVING, pos2, {2,3,9,4,1,0});
    worms2.emplace(2, w2);
    worms2.emplace(1, w1);
    
    
    //worms2.emplace(2, WormDTO(2, 0, 1, 100, 0.0, 0.0, 1, STANDING, pos, {0,1,7,0,1}));
    //worms2.emplace(1, WormDTO(1, 0, 2,  100,0.0, 0.0, 1, MOVING, pos2, {2,3,9,4,1,0}));

    GameDynamic* gameDynamicSent = new GameDynamic(1, 1, -1, worms2, explosives, supplies, teamsHealth);

    gameDynamicSent->send(mockServer2);

    std::shared_ptr<Serializable>serializableReceived(mockClient2.receiveSerializable());
    std::shared_ptr<GameDynamic> gameDynamicReceived = std::dynamic_pointer_cast<GameDynamic>(serializableReceived);

    REQUIRE(gameDynamicReceived->getWorms().size() == gameDynamicSent->getWorms().size());

    std::unordered_map<int, WormDTO> wormsReceived = gameDynamicReceived->getWorms(); 
    for(int i = 0; i < gameDynamicReceived->getWorms().size(); i++) {
        SECTION("WormInfo"){        
            CAPTURE(i);
            REQUIRE(wormsReceived[i].getWeapons().size() == worms2[i].getWeapons().size());
            SECTION("WeaponsInfo") {
                std::vector<int> weaponsSent = worms2[i].getWeapons();
                std::vector<int> weaponsReceived = wormsReceived[i].getWeapons();

                for(int j = 0; j < weaponsSent.size(); j++){
                    CAPTURE(j);
                    REQUIRE(weaponsReceived[j] == weaponsSent[j]);

                }
            }
        }
    }
}


TEST_CASE("Sending and receiving ExplosivesDTO", "[info]") {
    Position pos(9.7, 11.0);
    Position pos2(9.89, 9.1);
    

    WormDTO w2(2, 0, 1, 100, 0.9, 4.0, 1, JUMPING, pos, {});
    WormDTO w1(1, 1, 2,  0, 0.0, 0.333, 0, STANDING, pos2, {});
    worms2.emplace(2, w2);
    worms2.emplace(1, w1);

    explosives.emplace(0 ,ExplosivesDTO(0, 0, Position(1.0, 3.6), 5.3, -3.2));
    explosives.emplace(2, ExplosivesDTO(4, 2, Position(1.8666, 5), 5.3, -3.2));
    explosives.emplace(1, ExplosivesDTO(0, 1, Position(-1.0, 13.6), 5.3, -3.2));
    explosives.emplace(6, ExplosivesDTO(0, 6, Position(10.0, -2.6), 5.3, -3.2));


    GameDynamic* gameDynamicSent = new GameDynamic(1, 1, -1, worms2, explosives, supplies, teamsHealth);

    gameDynamicSent->send(mockServer2);

    std::shared_ptr<Serializable>serializableReceived(mockClient2.receiveSerializable());
    std::shared_ptr<GameDynamic> gameDynamicReceived = std::dynamic_pointer_cast<GameDynamic>(serializableReceived);

    REQUIRE(gameDynamicReceived->getExplosives().size() == gameDynamicSent->getExplosives().size());

    std::unordered_map<int, ExplosivesDTO> explosivesSent =  gameDynamicSent->getExplosives();
    std::unordered_map<int, ExplosivesDTO> explosivesReceived =  gameDynamicReceived->getExplosives();

    for(auto& explosiveR : explosivesReceived) {
        auto explosiveS = explosivesSent.find(explosiveR.first);
        REQUIRE(explosiveR.second.getID() == explosiveS->second.getID());
        REQUIRE(explosiveR.second.getType() == explosiveS->second.getType());
        REQUIRE(explosiveR.second.getPosition().getX() == explosiveS->second.getPosition().getX());
        REQUIRE(explosiveR.second.getPosition().getY() == explosiveS->second.getPosition().getY());
        REQUIRE(explosiveR.second.getVelX() == explosiveS->second.getVelX());
        REQUIRE(explosiveR.second.getVelY() == explosiveS->second.getVelY());
    }

}

TEST_CASE("Sending and receiving SupplyBoxDTO", "[info]") {
    Position pos(9.7, 11.0);
    Position pos2(9.89, 9.1);

    WormDTO w2(2, 0, 1, 100, 0.9, 4.0, 1, JUMPING, pos, {});
    WormDTO w1(1, 1, 2,  0, 0.0, 0.333, 0, MOVING, pos2, {});
    worms2.emplace(2, w2);
    worms2.emplace(1, w1);

    supplies.emplace(0 ,SupplyBoxDTO(0, 2, true, Position(1.0, 3.6)));
    supplies.emplace(2, SupplyBoxDTO(2, 7, true, Position(1.8666, 5)));
    supplies.emplace(1, SupplyBoxDTO(1, 5, false, Position(-1.0, 13.6)));
    supplies.emplace(6, SupplyBoxDTO(6, 3, false,Position(10.0, -2.6)));


    GameDynamic* gameDynamicSent = new GameDynamic(1, 1, -1, worms2, explosives, supplies, teamsHealth);

    gameDynamicSent->send(mockServer2);

    std::shared_ptr<Serializable>serializableReceived(mockClient2.receiveSerializable());
    std::shared_ptr<GameDynamic> gameDynamicReceived = std::dynamic_pointer_cast<GameDynamic>(serializableReceived);

    REQUIRE(gameDynamicReceived->getSupplyBox().size() == gameDynamicSent->getSupplyBox().size());

    std::unordered_map<int, SupplyBoxDTO> suppliesSent =  gameDynamicSent->getSupplyBox();
    std::unordered_map<int, SupplyBoxDTO> suppliessReceived =  gameDynamicReceived->getSupplyBox();

    for(auto& suppliesR : suppliessReceived) {
        auto suppliesS = suppliesSent.find(suppliesR.first);
        REQUIRE(suppliesR.second.getID() == suppliesS->second.getID());
        REQUIRE(suppliesR.second.getX() == suppliesS->second.getX());
        REQUIRE(suppliesR.second.getY() == suppliesS->second.getY());
        REQUIRE(suppliesR.second.getContent() == suppliesS->second.getContent());
        REQUIRE(suppliesR.second.isFalling() == suppliesS->second.isFalling());
    }

}

TEST_CASE("Sending and receiving TeamHealth", "[info]") {
    Position pos(-9.7, 11.0);
    Position pos2(9.89, -9.1);

    WormDTO w2(2, 0, 1, 100, 0.9, 4.0, 1, STANDING, pos, {});
    WormDTO w1(1, 1, 2,  0, 0.0, 0.333, 0, JUMPING, pos2, {});
    worms2.emplace(2, w2);  
    worms2.emplace(1, w1);

    GameDynamic* gameDynamicSent = new GameDynamic(1, 1, -1, worms2, explosives, supplies, teamsHealth);

    gameDynamicSent->send(mockServer2);

    std::shared_ptr<Serializable>serializableReceived(mockClient2.receiveSerializable());
    std::shared_ptr<GameDynamic> gameDynamicReceived = std::dynamic_pointer_cast<GameDynamic>(serializableReceived);

    REQUIRE(gameDynamicReceived->getTeamsHealth().size() == gameDynamicSent->getTeamsHealth().size());

    std::vector<uint32_t> teamsHealthReceived = gameDynamicReceived->getTeamsHealth(); 
    for(int i = 0; i < gameDynamicReceived->getTeamsHealth().size(); i++) {
        SECTION("WormInfo"){        
            CAPTURE(i);
            REQUIRE(teamsHealthReceived[i] == teamsHealth[i]);

        }
    }
}