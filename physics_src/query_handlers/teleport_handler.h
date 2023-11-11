#ifndef TELEPORT_CALLBACK_H
#define TELEPORT_CALLBACK_H

#include <vector>
#include "../entities/beam.h"

class TeleportQueryCallback : public b2QueryCallback {
public:
    bool validTeleport = true;

    TeleportQueryCallback();

    bool ReportFixture(b2Fixture* fixture);
};


#endif