#include "melee_handler.h"

MeleeQueryCallback::MeleeQueryCallback() {}

bool MeleeQueryCallback::ReportFixture(b2Fixture* fixture) {
        b2Body* body = fixture->GetBody();
        //Edge case: Does this explosion affect something else? Or just Worms?
        Entity* type = (Entity*) body->GetUserData().pointer; 
        if (typeid(*type) != typeid(Worm)){
            return true;
        }
        foundBodies.push_back(body);
        return true;
    }
    