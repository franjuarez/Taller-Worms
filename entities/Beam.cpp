#include "Beam.h"

Beam::Beam(b2Body* body, bool isWalkable) : Entity(body), walkable(isWalkable) {}

Beam::~Beam() {}

bool Beam::isWalkable() { return this->walkable; }

void Beam::beginCollisionWithBeam(Entity* otherBody, std::set<b2Body*>& entitiesToRemove) {
    UNUSED(otherBody);
    UNUSED(entitiesToRemove);
}

void Beam::beginCollisionWithWorm(Entity* otherBody, std::set<b2Body*>& entitiesToRemove) {
    otherBody->beginCollisionWithBeam(this, entitiesToRemove);
}

void Beam::beginCollisionWithRocket(Entity* otherBody, std::set<b2Body*>& entitiesToRemove) {
    otherBody->beginCollisionWithBeam(this, entitiesToRemove);
}

void Beam::preSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}

void Beam::preSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    otherBody->preSolveCollisionWithBeam(this, contact);
}

void Beam::preSolveCollisionWithRocket(Entity* otherBody, b2Contact* contact) {
    otherBody->preSolveCollisionWithBeam(this, contact);
}

void Beam::postSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}

void Beam::postSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    otherBody->postSolveCollisionWithBeam(this, contact);
}

void Beam::postSolveCollisionWithRocket(Entity* otherBody, b2Contact* contact) {
    otherBody->postSolveCollisionWithBeam(this, contact);
}

void Beam::endCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}

void Beam::endCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    otherBody->endCollisionWithBeam(this, contact);
}

void Beam::endCollisionWithRocket(Entity* otherBody, b2Contact* contact) {
    otherBody->endCollisionWithBeam(this, contact);
}

