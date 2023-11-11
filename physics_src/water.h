#ifndef WATER_H
#define WATER_H

#include "entity.h"
#include "worm.h"
#include "rocket.h"
#include <set>

class Worm;

class Water : public Entity {
    public:
    Water(b2Body* body, std::vector<b2Body*>& entitiesToRemove);
    
    virtual void beginCollisionWithWater(Entity* otherBody, b2Contact* contact) override;
    virtual void beginCollisionWithBeam(Entity* otherBody, b2Contact* contact) override;
    virtual void beginCollisionWithWorm(Entity* otherBody, b2Contact* contact) override;
    virtual void beginCollisionWithRocket(Entity* otherBody, b2Contact* contact) override;

    ~Water();

};

#endif
