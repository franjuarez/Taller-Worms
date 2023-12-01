#ifndef HOLY_GRENADE_H
#define HOLY_GRENADE_H

#include <iostream>
#include "../worm.h"
#include "delayed_projectile.h"

class HolyGrenade : public DelayedProjectile {
private:
public:
    HolyGrenade(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, std::vector<createEntity>& entitiesToAdd, 
    int id, float damage, float radius, float explosionTimer);

    ExplosivesDTO getDTO();

    ~HolyGrenade() override;
};

#endif