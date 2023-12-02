#include "air_attack_missile.h"

AirAttackMissile::AirAttackMissile(b2Body* fatherBody, std::unordered_set<b2Body*>& entitiesToRemove,
 std::vector<createEntity>& entitiesToAdd, int id, float damage, float radius) : 
        InstantProjectile(fatherBody, entitiesToRemove, entitiesToAdd, id, damage, radius) { }

ExplosivesDTO AirAttackMissile::getDTO() {
    return Projectile::getDTO(AIR_ATTACK);
}

AirAttackMissile::~AirAttackMissile() {}