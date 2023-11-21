#include "instant_projectile.h"

InstantProjectile::InstantProjectile(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove,
 std::vector<createEntity>& entitiesToAdd, int id, float damage, float radius) : 
    Projectile(body, entitiesToRemove, entitiesToAdd, EntityInstantProjectile, id, damage, radius) {}

void InstantProjectile::beginCollisionWithWater(Entity* otherBody, b2Contact* contact) {
    otherBody->beginCollisionWithProjectile(this, contact);
}

void InstantProjectile::beginCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    UNUSED(contact);
    UNUSED(otherBody);
    explode();
}

void InstantProjectile::beginCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    UNUSED(contact);
    UNUSED(otherBody);
    explode();    
}

InstantProjectile::~InstantProjectile() {}

