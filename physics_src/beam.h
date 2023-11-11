#ifndef BEAM_H
#define BEAM_H

#include "entity.h"
#include "worm.h"
#include "rocket.h"

class Worm;

class Beam : public Entity {
    private:
    bool walkable;

    public:
    Beam(b2Body* body, std::vector<b2Body*>& entitiesToRemove, bool isWalkable);

    bool isWalkable();
    
    virtual void beginCollisionWithWater(Entity* otherBody, b2Contact* contact);
    virtual void beginCollisionWithWorm(Entity* otherBody, b2Contact* contact);
    virtual void beginCollisionWithRocket(Entity* otherBody, b2Contact* contact);

    virtual void preSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold);
    virtual void preSolveCollisionWithRocket(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold);

    virtual void postSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse);
    virtual void postSolveCollisionWithRocket(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse);

    virtual void endCollisionWithWorm(Entity* otherBody, b2Contact* contact);
    virtual void endCollisionWithRocket(Entity* otherBody, b2Contact* contact);

    ~Beam() override;
};

#endif