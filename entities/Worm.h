#ifndef WORM_H
#define WORM_H

#include "Entity.h"
#include "Beam.h"
#include "Rocket.h"
#include "../aux/auxiliar_physics_functions.h"

class Worm : public Entity {
    private:
    uint id;
    // uint team; (Future update)
    float health;
    int direction;
    //weapons (Future update)

    void moveOnWalkableBeam(b2Body* worm, b2Vec2 normal);

    public:
    Worm(b2Body* body, uint id, int direction);


    void beginCollisionWithBeam(Entity* otherBody, std::set<b2Body*>& entitiesToRemove) override;
    void beginCollisionWithWorm(Entity* otherBody, std::set<b2Body*>& entitiesToRemove) override;
    void beginCollisionWithRocket(Entity* otherBody, std::set<b2Body*>& entitiesToRemove) override;

    void preSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact) override;
    void preSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact) override;
    void preSolveCollisionWithRocket(Entity* otherBody, b2Contact* contact) override;

    void postSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact) override;
    void postSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact) override;
    void postSolveCollisionWithRocket(Entity* otherBody, b2Contact* contact) override;

    void endCollisionWithBeam(Entity* otherBody, b2Contact* contact) override;
    void endCollisionWithWorm(Entity* otherBody, b2Contact* contact) override;
    void endCollisionWithRocket(Entity* otherBody, b2Contact* contact) override;

    ~Worm() override;

    void takeDamage(float damage);

    bool isDead();

    uint getId();
};

#endif