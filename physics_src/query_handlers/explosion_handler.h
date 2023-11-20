#ifndef EXPLOSION_CALLBACK_H
#define EXPLOSION_CALLBACK_H

#include <vector>
#include "../entities/entity.h"

struct collisionData{
    b2Body* body;
    b2Vec2 pointOfCollision;
};

class ExplosionQueryCallback : public b2RayCastCallback {
public:
    std::vector<collisionData> foundBodies;
    b2Vec2 explosionCenter;
    float blastRadius;

    // ExplosionQueryCallback(b2Vec2 explosionCenter, float blastRadius);
    ExplosionQueryCallback();

    float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction);
};

#endif