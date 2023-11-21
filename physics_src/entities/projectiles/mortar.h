#ifndef MORTAR_H
#define MORTAR_H

#include "../../query_handlers/explosion_handler.h"
#include "instant_projectile.h"
#include "projectile_fragment.h"

class Mortar : public InstantProjectile {
    public:
        Mortar(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, 
        std::vector<createEntity>& entitiesToAdd, int id, float damage, float radius);

        void leaveFragments() override;

        ExplosivesDTO getDTO();

        ~Mortar();
};


#endif