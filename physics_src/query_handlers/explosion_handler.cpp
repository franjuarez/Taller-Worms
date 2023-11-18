#include "explosion_handler.h"

ExplosionQueryCallback::ExplosionQueryCallback(b2Vec2 explosionCenter, float blastRadius) :
                                                explosionCenter(explosionCenter), blastRadius(blastRadius) {}

bool ExplosionQueryCallback::ReportFixture(b2Fixture* fixture) {
        b2Body* body = fixture->GetBody();
        //Edge case: Does this explosion affect something else? Or just Worms?
        Entity* type = (Entity*) body->GetUserData().pointer; 
        if (type->getEntityType() != EntityWorm){
            return true;
        }
        b2Vec2 bodyPos = body->GetPosition();
        float distance = b2Distance(this->explosionCenter, bodyPos);
        if(distance < this->blastRadius) {
            foundBodies.push_back(body);
        }
        return true;
    }
    