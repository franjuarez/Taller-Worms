#ifndef SUPPLY_CALLBACK_H
#define SUPPLY_CALLBACK_H

#include <vector>
#include "../entities/entity.h"

class SupplyQueryCallback : public b2RayCastCallback {
public:
    bool foundBeam = false;

    SupplyQueryCallback();

    float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction);
};

#endif