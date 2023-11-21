#ifndef GREEN_GRENADE_H
#define GREEN_GRENADE_H

#include <iostream>
#include "../worm.h"
#include "delayed_projectile.h"

class GreenGrenade : public DelayedProjectile {
private:
public:
    GreenGrenade(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, std::vector<createEntity>& entitiesToAdd, 
    int id, float damage, float radius, float explosionTimer);

    ExplosivesDTO getDTO();

    ~GreenGrenade() override;
};

#endif