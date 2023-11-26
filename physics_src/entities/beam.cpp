#include "beam.h"

Beam::Beam(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, float angle) :
 Entity(body, entitiesToRemove, EntityBeam), angle(angle), walkable((abs(angle) > CONFIG.getBeamMaxWalkableAngle()) ? false : true) {}

Beam::~Beam() {}

bool Beam::isWalkable() { return this->walkable; }

float Beam::getAngle() { return this->angle; }

void Beam::beginCollisionWithWater(Entity* otherBody, b2Contact* contact) {
    otherBody->beginCollisionWithBeam(this, contact);
}

void Beam::beginCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    otherBody->beginCollisionWithBeam(this, contact);
}

void Beam::beginCollisionWithInstantProjectile(Entity* otherBody, b2Contact* contact) {
    otherBody->beginCollisionWithBeam(this, contact);
}

void Beam::beginCollisionWithDelayedProjectile(Entity* otherBody, b2Contact* contact) {
    otherBody->beginCollisionWithBeam(this, contact);
}

void Beam::preSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold) {
    otherBody->preSolveCollisionWithBeam(this, contact, oldManifold);
}

void Beam::preSolveCollisionWithInstantProjectile(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold) {
    otherBody->preSolveCollisionWithBeam(this, contact, oldManifold);
}

void Beam::postSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse) {
    otherBody->postSolveCollisionWithBeam(this, contact, impulse);
}

void Beam::postSolveCollisionWithInstantProjectile(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse) {
    otherBody->postSolveCollisionWithBeam(this, contact, impulse);
}

void Beam::endCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    otherBody->endCollisionWithBeam(this, contact);
}

void Beam::endCollisionWithInstantProjectile(Entity* otherBody, b2Contact* contact) {
    otherBody->endCollisionWithBeam(this, contact);
}
