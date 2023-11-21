#include "banana.h"

Banana::Banana(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove,
 std::vector<createEntity>& entitiesToAdd, int id, float damage, float radius, float explosionTimer) :
    DelayedProjectile(body, entitiesToRemove, entitiesToAdd, id, damage, radius, explosionTimer) {}

ExplosivesDTO Banana::getDTO() {
    return Projectile::getDTO(BANANA);
}

Banana::~Banana() {}
