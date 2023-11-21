#include "bazooka.h"

Bazooka::Bazooka(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove,
 std::vector<createEntity>& entitiesToAdd, int id, float damage, float radius) : 
    InstantProjectile(body, entitiesToRemove, entitiesToAdd, id, damage, radius) {}

ExplosivesDTO Bazooka::getDTO() {
    return Projectile::getDTO(BAZOOKA);
}

Bazooka::~Bazooka() {}
