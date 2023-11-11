#ifndef ENTITY_H
#define ENTITY_H

#include <box2d/box2d.h>
#include <typeinfo>
#include <string>
#include <vector>

#include "../physics_constants.h"

#define UNUSED(x) (void)(x)

class Entity {
    public:
    b2Body* body;
    std::vector<b2Body*>& entitiesToRemove;

    Entity(b2Body* body, std::vector<b2Body*>& entitiesToRemove);
    
    virtual void beginCollisionWithWater(Entity* otherBody, b2Contact* contact);
    virtual void beginCollisionWithBeam(Entity* otherBody, b2Contact* contact);
    virtual void beginCollisionWithWorm(Entity* otherBody, b2Contact* contact);
    virtual void beginCollisionWithRocket(Entity* otherBody, b2Contact* contact);

    virtual void preSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold);
    virtual void preSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold);

    virtual void postSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse);
    virtual void postSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse);

    virtual void endCollisionWithBeam(Entity* otherBody, b2Contact* contact);
    virtual void endCollisionWithWorm(Entity* otherBody, b2Contact* contact);

    virtual ~Entity();
};

#endif
