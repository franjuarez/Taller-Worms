#ifndef BAZOOKA_H
#define BAZOOKA_H

#include <iostream>
#include "../../query_handlers/explosion_handler.h"
#include "instant_projectile.h"

class Bazooka : public InstantProjectile {
private:
public:
    Bazooka(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, 
    std::vector<createEntity>& entitiesToAdd, int id, float damage, float radius);

    ExplosivesDTO getDTO();

    ~Bazooka();
};

#endif