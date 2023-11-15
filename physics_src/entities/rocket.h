#ifndef ROCKET_H
#define ROCKET_H

#include <iostream>
#include "worm.h"
#include "../query_handlers/explosion_handler.h"
#include "../../game_src/explosives_dto.h"

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

    ExplosivesDTO getDTO();

    ~Rocket() override;
};

#endif