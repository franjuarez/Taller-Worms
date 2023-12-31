#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <box2d/box2d.h>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <unordered_set>

#include "query_handlers/explosion_handler.h"
#include "query_handlers/teleport_handler.h"
#include "query_handlers/supply_box_position_handler.h"
#include "collision_handler.h"
#include "listener.h"
#include "physics_constants.h"
#include "aux/auxiliar_functions.h"

#include "entities/worm.h"
#include "entities/beam.h"
#include "entities/water.h"
#include "entities/projectiles/bazooka.h"
#include "entities/projectiles/green_grenade.h"
#include "entities/projectiles/red_grenade.h"
#include "entities/projectiles/mortar.h"
#include "entities/projectiles/banana.h"
#include "entities/projectiles/dynamite.h"
#include "entities/projectiles/holy_grenade.h"
#include "entities/projectiles/air_attack_missile.h"
#include "entities/supplies/provition_supply_box.h"
#include "entities/supplies/trap_supply_box.h"

#include "../game_src/game_map.h"
#include "../game_src/beam_dto.h"
#include "../game_src/game_dynamic.h"

class GameWorld {
private:
    b2World* world;
    Listener* listener;
    float worldBegginningX;
    float worldBegginningY;
    float worldMaxY;
    float worldEndX;
    int lastProjectileId;
    int lastBoxId;
    std::unordered_map<int, b2Body*> projectiles;
    std::unordered_map<int, b2Body*> worms;
    std::unordered_map<int, b2Body*> boxes;
    std::unordered_set<b2Body*> entitiesToRemove;
    std::vector<createEntity> entitiesToAdd;

    void createWater();

    void createBeam(float startingX, float startingY, float angle, bool large);

    void createWorm(float startingX, float startingY, int id, int team, int health, std::vector<int> weapons);

    b2Body* createProjectile(b2Body* worm, int weaponId, int direction, float width, float height, float restitution);

    b2Body* createBazooka(b2Body* worm, int direction);

    b2Body* createMortar(b2Body* worm, int direction);

    b2Body* createGreenGrenade(b2Body* worm, int direction, int explosionTimer);

    b2Body* createRedGrenade(b2Body* worm, int direction, int explosionTimer);
    
    b2Body* createBanana(b2Body* worm, int direction, int explosionTimer);

    b2Body* createDynamite(b2Body* worm, int direction, int explosionTimer);

    b2Body* createHolyGrenade(b2Body* worm, int direction, int explosionTimer);

    b2Body* createAirAttackMissile(float startingX, float xDest, float velX);

    bool checkValidTpPosition(float x, float y);

    void checkWormExists(int id);

    void updateDelayedProjectiles(float deltaTime);

    void removeWormFromMap(b2Body* worm);

    void removeProjectileFromMap(b2Body* projectile);

    void removeBoxFromMap(b2Body* box);
    
    void removeEntities();

    void addFragments();

    Position calculateValidSupplyBoxPosition();

public:
    GameWorld(std::shared_ptr<GameMap> gameMap);

    void update();

    void moveWorm(int id, int direction);
 
    void jumpForwardWorm(int id);
    
    void jumpBackwardsWorm(int id);

    bool wormLaunchBazooka(int id, float angle, int direction, float power);

    bool wormLaunchMortar(int id, float angle, int direction, float power);
    
    bool wormThrowGreenGrenade(int id, float angle, int direction, float power, int explosionTimer);
    
    bool wormThrowRedGrenade(int id, float angle, int direction, float power, int explosionTimer);
    
    bool wormThrowBanana(int id, float angle, int direction, float power, int explosionTimer);

    bool wormDropDynamite(int id, int direction, int explosionTimer);

    bool wormCallAirAttack(int id, float xDest, float yDest);

    bool wormThrowHolyGrenade(int id, float angle, int direction, float power, int explosionTimer);

    void wormHitWithBat(int id, int direction);

    bool teleportWorm(int id, float x, float y);

    void dropSupplyBox(int type);

    bool allEntitiesAtRest();

    GameDynamic* getGameStatus(int id);

    ~GameWorld();

    //Cheats

    void addHealthToWorm(int id);
    
    void wormGetAllWeapons(int id);

    void toggleInvincible();

};

#endif