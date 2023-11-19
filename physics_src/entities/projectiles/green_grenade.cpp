#include "green_grenade.h"

GreenGrenade::GreenGrenade(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove,
 std::vector<createEntity>& entitiesToAdd, int id, float damage, float radius, float explosionTimer) :
    DelayedProjectile(body, entitiesToRemove, entitiesToAdd, GREEN_GRENADE, id, damage, radius, explosionTimer) {}

GreenGrenade::~GreenGrenade() {}
