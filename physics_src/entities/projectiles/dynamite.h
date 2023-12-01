#ifndef DYNAMITE_H
#define DYNAMITE_H

#include <iostream>
#include "../worm.h"
#include "delayed_projectile.h"

class Dynamite : public DelayedProjectile {
private:
public:
    Dynamite(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, std::vector<createEntity>& entitiesToAdd, 
    int id, float damage, float radius, float explosionTimer);

    ExplosivesDTO getDTO();

    ~Dynamite() override;
};

#endif