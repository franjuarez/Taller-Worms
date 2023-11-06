#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <iostream>
#include <unordered_map>

#include <box2d/box2d.h>
#include "listener.h"
#include "physics_constants.h"
#include "aux/auxiliar_physics_functions.h"

#include "entities/Entity.h"
#include "entities/Worm.h"
#include "entities/Beam.h"
#include "entities/Rocket.h"

class GameWorld {
private:
    b2World* world;
    Listener* listener;
    std::set<b2Body*> entitiesToRemove;
    std::unordered_map<uint, b2Body*> worms;

    void checkWormExists(uint id);

    void createBeam(float startingX, float startingY, float angle, bool large);

    void createWorm(float startingX, float startingY, uint id);

    b2Body* createRocket(b2Body* worm, int direction);

    void killDeadWorms();
    
    void removeEntities();

    void moveWorm(b2Body* worm, b2Vec2 vel);

    void jumpWorm(b2Body* worm, float maxHeight, float distance);
public:
    GameWorld();

    void update();

    void moveWormLeft(uint id);

    void moveWormRight(uint id);

    void jumpForwardWorm(uint id);
    
    void jumpBackwardsWorm(uint id);

    void wormLaunchRocket(uint id, float angle, int direction, float power);

    ~GameWorld();
};

#endif