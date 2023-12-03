#include "supply_box_position_handler.h"


#include <iostream>
SupplyQueryCallback::SupplyQueryCallback() {}

float SupplyQueryCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) {
    Entity* entity = (Entity*) fixture->GetBody()->GetUserData().pointer;
    this->lastIntersectedType = entity->getEntityType();
    if(this->lastIntersectedType == EntityBeam) {
        this->beam = entity->body;
    }
    return fraction;
}