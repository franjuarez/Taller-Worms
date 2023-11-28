#include "supply_box_position_handler.h"

SupplyQueryCallback::SupplyQueryCallback() {}

float SupplyQueryCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) {
    Entity* type = (Entity*) fixture->GetBody()->GetUserData().pointer;
    this->lastIntersectedType = type->getEntityType();
    return fraction;
}