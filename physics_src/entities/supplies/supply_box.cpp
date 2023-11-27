#include "supply_box.h"

SupplyBox::SupplyBox(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, int type) : 
    Entity(body, entitiesToRemove, EntitySupplyBox), supplyType(type) {}

int SupplyBox::getSupplyType() {
    return this->supplyType;
}

void SupplyBox::beginCollisionWithWater(Entity* otherBody, b2Contact* contact) {
    otherBody->beginCollisionWithSupplyBox(this, contact);
}

void SupplyBox::beginCollisionWithProjectile(Entity* otherBody, b2Contact* contact) {
    otherBody->beginCollisionWithSupplyBox(this, contact);
}

SupplyBox::~SupplyBox() {}