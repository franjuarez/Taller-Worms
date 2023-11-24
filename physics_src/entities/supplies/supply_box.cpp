#include "supply_box.h"

SupplyBox::SupplyBox(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, int type) : 
    Entity(body, entitiesToRemove, EntitySupplyBox), supplyType(type) {}

int SupplyBox::getSupplyType() {
    return this->supplyType;
}

void SupplyBox::beginCollisionWithWater(Entity* otherBody, b2Contact* contact) {
    otherBody->beginCollisionWithProvitionsSupplyBox(this, contact);
}

SupplyBox::~SupplyBox() {}