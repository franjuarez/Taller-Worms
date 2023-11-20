#ifndef EXPLOSION_CALLBACK_H
#define EXPLOSION_CALLBACK_H

#include <vector>
#include "../entities/entity.h"

struct collisionData{
    b2Body* body;
    b2Vec2 pointOfCollision;

    collisionData() : body(nullptr), pointOfCollision(b2Vec2(0,0)) {}

    collisionData(b2Body* body, const b2Vec2& pointOfCollision)
    : body(body), pointOfCollision(pointOfCollision) {}
};

class ExplosionQueryCallback : public b2RayCastCallback {
public:
    b2Vec2 explosionCenter;
    float blastRadius;
    std::vector<collisionData> foundBodies;

    ExplosionQueryCallback(b2Vec2 explosionCenter, float blastRadius);
    // ExplosionQueryCallback();

    float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction);
};

#endif