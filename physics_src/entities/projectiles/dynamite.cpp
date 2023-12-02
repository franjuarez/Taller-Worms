#include "dynamite.h"

Dynamite::Dynamite(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove,
 std::vector<createEntity>& entitiesToAdd, int id, float damage, float radius, float explosionTimer) :
    DelayedProjectile(body, entitiesToRemove, entitiesToAdd, id, damage, radius, explosionTimer) {
    }

ExplosivesDTO Dynamite::getDTO() {
    return Projectile::getDTO(DYNAMITE);
}

void Dynamite::beginCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    this->body->SetLinearVelocity(b2Vec2(0, 0));
    this->body->SetLinearDamping(INFINITE_DAMPING);
}

Dynamite::~Dynamite() {}
