#ifndef EXPLOSION_CALLBACK_H
#define EXPLOSION_CALLBACK_H

#include <vector>
#include "../entities/entity.h"

class ExplosionQueryCallback : public b2QueryCallback {
public:
    std::vector<b2Body*> foundBodies;
    b2Vec2 explosionCenter;
    float blastRadius;

    ExplosionQueryCallback(b2Vec2 explosionCenter, float blastRadius);

    bool ReportFixture(b2Fixture* fixture);
};

#endif