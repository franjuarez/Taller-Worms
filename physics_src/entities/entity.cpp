#include "entity.h"

Entity::Entity(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, EntityType entityType) : body(body),
 entitiesToRemove(entitiesToRemove), entityType(entityType) {}

Entity::~Entity() {}

EntityType Entity::getEntityType() {
    return this->entityType;
}

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

void Entity::beginCollisionWithProjectile(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}

void Entity::beginCollisionWithProvitionsSupplyBox(Entity* otherBody, b2Contact* contact) {
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
