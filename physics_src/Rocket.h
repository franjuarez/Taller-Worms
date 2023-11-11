#ifndef ROCKET_H
#define ROCKET_H

#include <iostream>
#include <set>
#include "Worm.h"
#include "explosion_handler.h"
#include "../game_src/weapons_dto.h"


class Rocket : public Entity {
private:
    float damage;
    float radius;

    void explode();
public:
    Rocket(b2Body* body, std::vector<b2Body*>& entitiesToRemove, float damage, float radius);

    virtual void beginCollisionWithBeam(Entity* otherBody, b2Contact* contact);
    virtual void beginCollisionWithWorm(Entity* otherBody, b2Contact* contact);
    virtual void beginCollisionWithRocket(Entity* otherBody, b2Contact* contact);

    virtual void preSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold);
    virtual void preSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold);
    virtual void preSolveCollisionWithRocket(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold);

    virtual void postSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse);
    virtual void postSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse);
    virtual void postSolveCollisionWithRocket(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse);

    virtual void endCollisionWithBeam(Entity* otherBody, b2Contact* contact);
    virtual void endCollisionWithWorm(Entity* otherBody, b2Contact* contact);
    virtual void endCollisionWithRocket(Entity* otherBody, b2Contact* contact);

    WeaponDTO getDTO();

    ~Rocket() override;
};

#endif