#ifndef ROCKET_H
#define ROCKET_H

#include <iostream>
#include <set>
#include "Worm.h"
#include "explosion_handler.h"

class Rocket : public Entity {
private:
    float damage;
    float radius;

    void explode(std::set<b2Body*>& entitiesToRemove);
public:
    Rocket(b2Body* body, float damage, float radius);

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

    ~Rocket() override;
};

#endif