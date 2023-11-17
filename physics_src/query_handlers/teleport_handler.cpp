#include "teleport_handler.h"

TeleportQueryCallback::TeleportQueryCallback() {}

bool TeleportQueryCallback::ReportFixture(b2Fixture* fixture) {
    Entity* type = (Entity*) fixture->GetBody()->GetUserData().pointer;
    if (type->getEntityType() != EntityWorm){
        return true;
    }
    validTeleport = false;
    return false;
}
    