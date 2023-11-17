#include "teleport_handler.h"
#include <iostream>
TeleportQueryCallback::TeleportQueryCallback() {}

bool TeleportQueryCallback::ReportFixture(b2Fixture* fixture) {
    Entity* type = (Entity*) fixture->GetBody()->GetUserData().pointer;
    if (type->getEntityType() != EntityBeam){
        return true;
    }
    std::cout << "Found beam" << std::endl;
    validTeleport = false;
    return false;
}
    