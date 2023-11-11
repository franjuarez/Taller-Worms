#include "explosion_handler.h"

ExplosionQueryCallback::ExplosionQueryCallback(b2Vec2 explosionCenter, float blastRadious) :
                                                explosionCenter(explosionCenter), blastRadious(blastRadious) {}

bool ExplosionQueryCallback::ReportFixture(b2Fixture* fixture) {
        b2Body* body = fixture->GetBody();
        //Edge case: Does this explosion affect something else? Or just Worms?
        Entity* type = (Entity*) body->GetUserData().pointer; 
        if (typeid(*type) != typeid(Worm)){
            return true;
        }
        b2Vec2 bodyPos = body->GetPosition();
        float distance = b2Distance(this->explosionCenter, bodyPos);
        if(distance < this->blastRadious) {
            foundBodies.push_back(body);
        }
        return true;
    }
    