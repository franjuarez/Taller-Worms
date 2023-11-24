#include "supply_box_position_handler.h"

SupplyQueryCallback::SupplyQueryCallback() {}

float SupplyQueryCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) {
    Entity* type = (Entity*) fixture->GetBody()->GetUserData().pointer;
    if (type->getEntityType() == EntityBeam){
        foundBeam = true;
        return 0;
    }
    return 1;
}