#ifndef ENTITY_H
#define ENTITY_H

#include <box2d/box2d.h>
#include <string>
#include <vector>
#include <unordered_set>
#include "../physics_constants.h"
#include "../../game_src/constants_game.h"

#define UNUSED(x) (void)(x)

enum EntityType{
    EntityWorm, //0
    EntityBeam, //1
    EntityWater, //2
    EntityInstantProjectile, //3
    EntityDelayedProjectile, //4
    EntityCount, //5
};

class Entity {
public:
    b2Body* body;
    std::unordered_set<b2Body*>& entitiesToRemove;
    EntityType entityType;
    
    Entity(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, EntityType entityType);

    EntityType getEntityType();
    
    virtual void beginCollisionWithWater(Entity* otherBody, b2Contact* contact);
    virtual void beginCollisionWithBeam(Entity* otherBody, b2Contact* contact);
    virtual void beginCollisionWithWorm(Entity* otherBody, b2Contact* contact);
    virtual void beginCollisionWithProjectile(Entity* otherBody, b2Contact* contact);

    virtual void preSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold);
    virtual void preSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold);

    virtual void postSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse);
    virtual void postSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse);

    virtual void endCollisionWithBeam(Entity* otherBody, b2Contact* contact);
    virtual void endCollisionWithWorm(Entity* otherBody, b2Contact* contact);

    virtual ~Entity();
};

#endif
