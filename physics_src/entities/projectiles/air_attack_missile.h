#ifndef AIR_ATTACK_MISSILE_H
#define AIR_ATTACK_MISSILE_H

#include "../../query_handlers/explosion_handler.h"
#include "instant_projectile.h"

class AirAttackMissile : public InstantProjectile {
    public:
        AirAttackMissile(b2Body* fatherBody, std::unordered_set<b2Body*>& entitiesToRemove, 
        std::vector<createEntity>& entitiesToAdd, int id, float damage, float radius);

        ExplosivesDTO getDTO();

        ~AirAttackMissile();
};

#endif