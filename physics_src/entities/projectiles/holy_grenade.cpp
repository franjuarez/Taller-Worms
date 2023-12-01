#include "holy_grenade.h"

HolyGrenade::HolyGrenade(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove,
 std::vector<createEntity>& entitiesToAdd, int id, float damage, float radius, float explosionTimer) :
    DelayedProjectile(body, entitiesToRemove, entitiesToAdd, id, damage, radius, explosionTimer) {}

ExplosivesDTO HolyGrenade::getDTO() {
    return Projectile::getDTO(HOLY_GRENADE);
}

HolyGrenade::~HolyGrenade() {}
