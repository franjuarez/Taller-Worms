#include "supply_box.h"

SupplyBox::SupplyBox(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, int id, int type) : 
    Entity(body, entitiesToRemove, EntitySupplyBox), id(id), supplyType(type) {}

int SupplyBox::getId() {
    return this->id;
}

int SupplyBox::getSupplyType() {
    return this->supplyType;
}

SupplyBoxDTO SupplyBox::getDTO() {
    SupplyBoxDTO dto(this->id, this->supplyType, Position(this->body->GetPosition().x, this->body->GetPosition().y));
    return dto;
}

void SupplyBox::beginCollisionWithWater(Entity* otherBody, b2Contact* contact) {
    otherBody->beginCollisionWithSupplyBox(this, contact);
}

void SupplyBox::beginCollisionWithProjectile(Entity* otherBody, b2Contact* contact) {
    otherBody->beginCollisionWithSupplyBox(this, contact);
}

SupplyBox::~SupplyBox() {}