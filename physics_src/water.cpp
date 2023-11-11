#include "water.h"

Water::Water(b2Body* body, std::vector<b2Body*>& entitiesToRemove) : Entity(body, entitiesToRemove) {}

Water::~Water() {}

void Water::beginCollisionWithWater(Entity* otherBody, b2Contact* contact) {
    this->entitiesToRemove.push_back(otherBody->body);
    UNUSED(contact);
}

void Water::beginCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    this->entitiesToRemove.push_back(otherBody->body);
    UNUSED(contact);
}

void Water::beginCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    this->entitiesToRemove.push_back(otherBody->body);
    UNUSED(contact);
}

void Water::beginCollisionWithRocket(Entity* otherBody, b2Contact* contact) {
    this->entitiesToRemove.push_back(otherBody->body);
    UNUSED(otherBody);
    UNUSED(contact);
}
