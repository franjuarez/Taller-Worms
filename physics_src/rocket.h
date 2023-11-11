#ifndef ROCKET_H
#define ROCKET_H

#include <iostream>
#include "worm.h"
#include "explosion_handler.h"
#include "../game_src/projectile_dto.h"

class Rocket : public Entity {
private:
    float damage;
    float radius;

    void explode();
public:
    Rocket(b2Body* body, std::vector<b2Body*>& entitiesToRemove, float damage, float radius);
    
    virtual void beginCollisionWithWater(Entity* otherBody, b2Contact* contact);
    virtual void beginCollisionWithBeam(Entity* otherBody, b2Contact* contact);
    virtual void beginCollisionWithWorm(Entity* otherBody, b2Contact* contact);
    virtual void beginCollisionWithRocket(Entity* otherBody, b2Contact* contact);

    ProjectileDTO getDTO();

    ~Rocket() override;
};

#endif