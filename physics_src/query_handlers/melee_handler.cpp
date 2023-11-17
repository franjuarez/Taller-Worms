#include "melee_handler.h"
#include <iostream>
MeleeQueryCallback::MeleeQueryCallback() {}

bool MeleeQueryCallback::ReportFixture(b2Fixture* fixture) {
        b2Body* body = fixture->GetBody();
        //Edge case: Does this explosion affect something else? Or just Worms?
        Entity* type = (Entity*) body->GetUserData().pointer; 
        if (type->getEntityType() == EntityWorm){
            foundBodies.push_back(body);
        }
        return true;
    }
    