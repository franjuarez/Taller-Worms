#include "dynamite.h"

Dynamite::Dynamite(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove,
 std::vector<createEntity>& entitiesToAdd, int id, float damage, float radius, float explosionTimer) :
    DelayedProjectile(body, entitiesToRemove, entitiesToAdd, id, damage, radius, explosionTimer) {}

ExplosivesDTO Dynamite::getDTO() {
    return Projectile::getDTO(DYNAMITE);
}

Dynamite::~Dynamite() {}
