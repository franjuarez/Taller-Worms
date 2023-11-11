#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <iostream>
#include <unordered_map>

#include <box2d/box2d.h>
#include "listener.h"
#include "physics_constants.h"
#include "auxiliar_physics_functions.h"
#include "../game_src/game_dynamic.h"
#include "query_handlers/teleport_handler.h"

#include "entities/entity.h"
#include "entities/water.h"
#include "entities/worm.h"
#include "entities/beam.h"
#include "entities/rocket.h"

class GameWorld {
private:
    b2World* world;
    Listener* listener;
    std::unordered_map<int, b2Body*> worms;
    std::vector<b2Body*> projectiles;
    std::vector<b2Body*> entitiesToRemove;

    void createWater();

    b2Body* createRocket(b2Body* worm, int direction);

    bool checkValidTpPosition(float x, float y);

    void checkWormExists(int id);

    void removeWorm(b2Body* worm);

    void removeProjectile(b2Body* projectile);
    
    void removeEntities();

public:
    GameWorld();

    void update();

    void createBeam(float startingX, float startingY, float angle, bool large);

    void createWorm(float startingX, float startingY, int id, int team);

    void moveWorm(int id, int direction);
 
    void jumpForwardWorm(int id);
    
    void jumpBackwardsWorm(int id);

    void wormLaunchRocket(int id, float angle, int direction, float power);

    void wormHitWithBat(int id);

    bool teleportWorm(int id, float x, float y);

    GameDynamic* getGameStatus(int id);

    ~GameWorld();
};

#endif