#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <box2d/box2d.h>

class GameWorld {
private:
    b2World* world;
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