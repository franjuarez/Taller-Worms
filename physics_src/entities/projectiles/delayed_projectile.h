#ifndef DELAYED_PROJECTILE_H
#define DELAYED_PROJECTILE_H

#include <iostream>
#include "projectile.h"
#include "../../query_handlers/explosion_handler.h"

class DelayedProjectile : public Projectile {
protected:
    float explosionTimer;

public:
    DelayedProjectile(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, 
    std::vector<createEntity>& entitiesToAdd, int id, float damage, float radius, float explosionTimer);
    
    void update(float deltaTime);
    
    virtual void beginCollisionWithWater(Entity* otherBody, b2Contact* contact) override;
    virtual void beginCollisionWithBeam(Entity* otherBody, b2Contact* contact) override;
    virtual void beginCollisionWithWorm(Entity* otherBody, b2Contact* contact) override;

    ~DelayedProjectile() override;
};

#endif