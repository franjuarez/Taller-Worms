#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <iostream>

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

    b2Body* worm;

    void createBeam(float startingX, float startingY, float angle, bool large);

    void createWorm(float startingX, float startingY);

    b2Body* createRocket(int direction);

    void killDeadWorms();
    
    void removeEntities();

    void jumpWorm(b2Body* worm, float maxHeight, float distance);
public:
    GameWorld();

    void update();

    void moveWormLeft();

    void moveWormRight();

    void jumpForwardWorm();
    
    void jumpBackwardsWorm();

    void wormLaunchRocket(float angle, int direction, float power);

    ~GameWorld();
};

#endif