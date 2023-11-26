#ifndef BEAM_H
#define BEAM_H

#include "entity.h"
#include "worm.h"

class Beam : public Entity {
    private:
    float angle;
    bool walkable;

    public:
    Beam(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, float angle);

    bool isWalkable();
    float getAngle();
    
    virtual void beginCollisionWithWater(Entity* otherBody, b2Contact* contact);
    virtual void beginCollisionWithWorm(Entity* otherBody, b2Contact* contact);
    virtual void beginCollisionWithInstantProjectile(Entity* otherBody, b2Contact* contact);
    virtual void beginCollisionWithDelayedProjectile(Entity* otherBody, b2Contact* contact);

    virtual void preSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold);
    virtual void preSolveCollisionWithInstantProjectile(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold);

    virtual void postSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse);
    virtual void postSolveCollisionWithInstantProjectile(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse);

    virtual void endCollisionWithWorm(Entity* otherBody, b2Contact* contact);
    virtual void endCollisionWithInstantProjectile(Entity* otherBody, b2Contact* contact);

    ~Beam() override;
};

#endif