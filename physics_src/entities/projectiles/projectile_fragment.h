#ifndef PROJECTILE_FRAGMENT_H
#define PROJECTILE_FRAGMENT_H

#include "../../query_handlers/explosion_handler.h"
#include "instant_projectile.h"

class ProjectileFragment : public InstantProjectile {
    public:
        ProjectileFragment(b2Body* fatherBody, std::unordered_set<b2Body*>& entitiesToRemove, 
        std::vector<createEntity>& entitiesToAdd, int id, float damage, float radius);

        b2Body* createFragment();

        ~ProjectileFragment();
};

#endif