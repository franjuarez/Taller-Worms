#ifndef SUPPLY_CALLBACK_H
#define SUPPLY_CALLBACK_H

#include <vector>
#include "../entities/beam.h"

class SupplyQueryCallback : public b2RayCastCallback {
public:
    EntityType lastIntersectedType;
    b2Body *beam;

    SupplyQueryCallback();

    float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction);
};

#endif