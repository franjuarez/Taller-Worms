#ifndef ENTITY_H
#define ENTITY_H

#include <box2d/box2d.h>
#include <typeinfo>
#include <string>
#include <vector>

#include "physics_constants.h"

//For supressing unused variable warnings
#define UNUSED(x) (void)(x)

class Entity {
    public:
    b2Body* body;
    std::vector<b2Body*>& entitiesToRemove;

    Entity(b2Body* body, std::vector<b2Body*>& entitiesToRemove) : body(body), entitiesToRemove(entitiesToRemove) {}
    
    virtual void beginCollisionWithBeam(Entity* otherBody, b2Contact* contact) = 0;
    virtual void beginCollisionWithWorm(Entity* otherBody, b2Contact* contact) = 0;
    virtual void beginCollisionWithRocket(Entity* otherBody, b2Contact* contact) = 0;

    virtual void preSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold) = 0;
    virtual void preSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold) = 0;
    virtual void preSolveCollisionWithRocket(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold) = 0;

    virtual void postSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse) = 0;
    virtual void postSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse) = 0;
    virtual void postSolveCollisionWithRocket(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse) = 0;

    virtual void endCollisionWithBeam(Entity* otherBody, b2Contact* contact) = 0;
    virtual void endCollisionWithWorm(Entity* otherBody, b2Contact* contact) = 0;
    virtual void endCollisionWithRocket(Entity* otherBody, b2Contact* contact) = 0;

    virtual ~Entity() {}
};

#endif
