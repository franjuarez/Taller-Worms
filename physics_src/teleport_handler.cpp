#include "teleport_handler.h"

TeleportQueryCallback::TeleportQueryCallback() {}

bool TeleportQueryCallback::ReportFixture(b2Fixture* fixture) {
    Entity* type = (Entity*) fixture->GetBody()->GetUserData().pointer;
    if (typeid(*type) != typeid(Beam)){
        return true;
    }
    std::cout << "Found beam" << std::endl;
    validTeleport = false;
    return false;
}
    