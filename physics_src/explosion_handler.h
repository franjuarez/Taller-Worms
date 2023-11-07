#ifndef EXPLOSION_CALLBACK_H
#define EXPLOSION_CALLBACK_H

#include <vector>
#include "entities/Worm.h"

class ExplosionQueryCallback : public b2QueryCallback {
public:
    std::vector<b2Body*> foundBodies;
    b2Vec2 explosionCenter;
    float blastRadious;

    ExplosionQueryCallback(b2Vec2 explosionCenter, float blastRadious);

    bool ReportFixture(b2Fixture* fixture);
};

#endif