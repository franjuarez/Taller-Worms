#include "water.h"

Water::Water(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove) : Entity(body, entitiesToRemove, EntityWater) {}

Water::~Water() {}

void Water::beginCollisionWithWater(Entity* otherBody, b2Contact* contact) {
    this->entitiesToRemove.insert(otherBody->body);
    UNUSED(contact);
}

void Water::beginCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    this->entitiesToRemove.insert(otherBody->body);
    UNUSED(contact);
}

void Water::beginCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    Worm* worm = (Worm*) otherBody;
    worm->die();
    UNUSED(contact);
}

void Water::beginCollisionWithProjectile(Entity* otherBody, b2Contact* contact) {
    this->entitiesToRemove.insert(otherBody->body);
    UNUSED(otherBody);
    UNUSED(contact);
}
