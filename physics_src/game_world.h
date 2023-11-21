#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <box2d/box2d.h>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <unordered_set>

#include "query_handlers/explosion_handler.h"
#include "query_handlers/teleport_handler.h"
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

#include "../game_src/game_map.h"
#include "../game_src/beam_dto.h"
#include "../game_src/game_dynamic.h"

class GameWorld {
private:
    b2World* world;
    Listener* listener;
    int lastProjectileId;
    std::unordered_map<int, b2Body*> projectiles;
    std::unordered_map<int, b2Body*> worms;
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

    bool checkValidTpPosition(float x, float y);

    void checkWormExists(int id);

    void updateDelayedProjectiles(float deltaTime);

    void removeWorm(b2Body* worm);

    void removeProjectile(b2Body* projectile);
    
    void removeEntities();

    void addFragments();

public:
    GameWorld(std::shared_ptr<GameMap> gameMap);

    void update();

    void moveWorm(int id, int direction);
 
    void jumpForwardWorm(int id);
    
    void jumpBackwardsWorm(int id);

    void wormLaunchBazooka(int id, float angle, int direction, float power);

    void wormLaunchMortar(int id, float angle, int direction, float power);
    
    void wormThrowGreenGrenade(int id, float angle, int direction, float power, int explosionTimer);
    
    void wormThrowRedGrenade(int id, float angle, int direction, float power, int explosionTimer);
    
    void wormThrowBanana(int id, float angle, int direction, float power, int explosionTimer);

    void wormHitWithBat(int id, int direction);

    bool teleportWorm(int id, float x, float y);

    bool allEntitiesAtRest();

    GameDynamic* getGameStatus(int id);

    ~GameWorld();

    //Cheats

    void addHealthToWorm(int id);
    
    void wormGetAllWeapons(int id);

    void toggleInvincible();

};

#endif