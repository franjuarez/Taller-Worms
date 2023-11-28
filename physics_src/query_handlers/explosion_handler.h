#ifndef EXPLOSION_CALLBACK_H
#define EXPLOSION_CALLBACK_H

#include <vector>
#include "../entities/entity.h"

class ExplosionQueryCallback : public b2RayCastCallback {
public:
    b2Vec2 explosionCenter;
    float blastRadius;
    std::vector<b2Body*> foundBodies;

    ExplosionQueryCallback(b2Vec2 explosionCenter, float blastRadius);

    float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction);

};

#endif