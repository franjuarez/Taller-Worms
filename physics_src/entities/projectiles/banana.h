#ifndef BANANA_H
#define BANANA_H

#include <iostream>
#include "../worm.h"
#include "delayed_projectile.h"

class Banana : public DelayedProjectile {
private:
public:
    Banana(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, std::vector<createEntity>& entitiesToAdd, 
    int id, float damage, float radius, float explosionTimer);
    
    ~Banana() override;
};

#endif