#ifndef MELEE_CALLBACK_H
#define MELEE_CALLBACK_H

#include <vector>
#include "../entities/worm.h"

class MeleeQueryCallback : public b2QueryCallback {
public:
    std::vector<b2Body*> foundBodies;

    MeleeQueryCallback();

    bool ReportFixture(b2Fixture* fixture);
};


#endif