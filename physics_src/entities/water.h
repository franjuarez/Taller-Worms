#ifndef WATER_H
#define WATER_H

#include "entity.h"
#include "worm.h"
#include <set>

class Worm;

class Water : public Entity {
    public:
    Water(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove);
    
    virtual void beginCollisionWithWater(Entity* otherBody, b2Contact* contact) override;
    virtual void beginCollisionWithBeam(Entity* otherBody, b2Contact* contact) override;
    virtual void beginCollisionWithWorm(Entity* otherBody, b2Contact* contact) override;
    virtual void beginCollisionWithProjectile(Entity* otherBody, b2Contact* contact) override;

    ~Water();

};

#endif
