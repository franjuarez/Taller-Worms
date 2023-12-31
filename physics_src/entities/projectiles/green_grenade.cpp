#include "green_grenade.h"

GreenGrenade::GreenGrenade(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove,
 std::vector<createEntity>& entitiesToAdd, int id, float damage, float radius, float explosionTimer) :
    DelayedProjectile(body, entitiesToRemove, entitiesToAdd, id, damage, radius, explosionTimer) {}

ExplosivesDTO GreenGrenade::getDTO() {
    return Projectile::getDTO(GREEN_GRENADE);
}

GreenGrenade::~GreenGrenade() {}
