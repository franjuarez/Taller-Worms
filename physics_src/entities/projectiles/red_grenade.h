#ifndef RED_GRENADE_H
#define RED_GRENADE_H

#include <iostream>
#include "../worm.h"
#include "delayed_projectile.h"
#include "projectile_fragment.h"

class RedGrenade : public DelayedProjectile {
public:
    RedGrenade(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, 
    std::vector<createEntity>& entitiesToAdd, int id, float damage, float radius, float explosionTimer);
    
    void leaveFragments() override;

    ExplosivesDTO getDTO();

    ~RedGrenade() override;
};

#endif