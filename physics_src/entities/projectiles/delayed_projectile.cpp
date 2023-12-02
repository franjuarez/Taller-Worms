#include "delayed_projectile.h"

DelayedProjectile::DelayedProjectile(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove,
std::vector<createEntity>& entitiesToAdd, int id, float damage, float radius, float explosionTimer) : 
    Projectile(body, entitiesToRemove, entitiesToAdd, EntityDelayedProjectile, id, damage, radius), explosionTimer(explosionTimer) {}

void DelayedProjectile::update(float deltaTime) {
        explosionTimer -= deltaTime;

        if (explosionTimer <= 0.0f) {
            explode();
        }
}

void DelayedProjectile::beginCollisionWithWater(Entity* otherBody, b2Contact* contact) {
    otherBody->beginCollisionWithProjectile(this, contact);
}

void DelayedProjectile::beginCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    UNUSED(contact);
    UNUSED(otherBody);
}

void DelayedProjectile::beginCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    UNUSED(contact);
    UNUSED(otherBody);
}

void DelayedProjectile::beginCollisionWithSupplyBox(Entity* otherBody, b2Contact* contact) {
    UNUSED(contact);
    UNUSED(otherBody);
    otherBody->body->SetLinearDamping(INFINITE_DAMPING);
    otherBody->body->SetLinearVelocity(b2Vec2(0, 0));
}

DelayedProjectile::~DelayedProjectile() {}