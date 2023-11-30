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
    bool falling = this->body->GetLinearVelocity().Length() != 0;
    SupplyBoxDTO dto(this->id, this->supplyType, falling, Position(this->body->GetPosition().x, this->body->GetPosition().y));
    return dto;
}

void SupplyBox::beginCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    Beam* beam = (Beam*) otherBody;
    if(beam->isWalkable()) {
        this->body->SetLinearVelocity(b2Vec2(0, 0));
        this->body->SetGravityScale(0);
    } else{
        this->body->SetGravityScale(0.5);
    }
}

void SupplyBox::beginCollisionWithWater(Entity* otherBody, b2Contact* contact) {
    otherBody->beginCollisionWithSupplyBox(this, contact);
}

void SupplyBox::beginCollisionWithProjectile(Entity* otherBody, b2Contact* contact) {
    otherBody->beginCollisionWithSupplyBox(this, contact);
}

SupplyBox::~SupplyBox() {}