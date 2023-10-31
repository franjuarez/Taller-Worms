#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <box2d/box2d.h>
#include "listener.h"
// #include "physics_constants.h"

class GameWorld {
private:
    b2World* world;
    Listener* listener;
    b2Body* worm;

    void createBeam(float startingX, float startingY, float angle, bool large);

    void createWorm(float startingX, float startingY);
public:
    GameWorld();

    void update();

    void moveWormLeft();

    void moveWormRight();

    ~GameWorld();
};

#endif