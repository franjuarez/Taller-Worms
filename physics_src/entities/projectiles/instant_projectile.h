#ifndef INSTANT_PROJECTILE_H
#define INSTANT_PROJECTILE_H

#include "projectile.h"
#include "../../query_handlers/explosion_handler.h"

class InstantProjectile : public Projectile {
protected:
public:
    InstantProjectile(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, 
    std::vector<createEntity>& entitiesToAdd, int id, float damage, float radius);
    
    virtual void beginCollisionWithWater(Entity* otherBody, b2Contact* contact) override;
    virtual void beginCollisionWithBeam(Entity* otherBody, b2Contact* contact) override;
    virtual void beginCollisionWithWorm(Entity* otherBody, b2Contact* contact) override;

    ~InstantProjectile() override;
};

#endif