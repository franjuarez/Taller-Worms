#include "entity.h"

Entity::Entity(b2Body* body, std::vector<b2Body*>& entitiesToRemove) : body(body), entitiesToRemove(entitiesToRemove) {}

Entity::~Entity() {}

void Entity::beginCollisionWithWater(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}

void Entity::beginCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}

void Entity::beginCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}

void Entity::beginCollisionWithRocket(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}

void Entity::preSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold) {
    UNUSED(otherBody);
    UNUSED(contact);
    UNUSED(oldManifold);
}

void Entity::preSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold) {
    UNUSED(otherBody);
    UNUSED(contact);
    UNUSED(oldManifold);
}

void Entity::postSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse) {
    UNUSED(otherBody);
    UNUSED(contact);
    UNUSED(impulse);
}

void Entity::postSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse) {
    UNUSED(otherBody);
    UNUSED(contact);
    UNUSED(impulse);
}

void Entity::endCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}

void Entity::endCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}
