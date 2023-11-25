#include "explosion_handler.h"
#include <iostream>

ExplosionQueryCallback::ExplosionQueryCallback(b2Vec2 explosionCenter, float blastRadius) :
                                            explosionCenter(explosionCenter), blastRadius(blastRadius) {}

float ExplosionQueryCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) {
        b2Body* body = fixture->GetBody();
        //Edge case: Does this explosion affect something else? Or just Worms?
        Entity* type = (Entity*) body->GetUserData().pointer; 
        if (type->getEntityType() == EntityBeam){
            float beamDistance = b2Distance(this->explosionCenter, point);
            std::vector<b2Body*> bodiesToRemove;
            for (b2Body* currentBody : foundBodies) {
                float bodyDistance = b2Distance(this->explosionCenter, currentBody->GetPosition());
                if (beamDistance < bodyDistance) {
                    bodiesToRemove.push_back(currentBody);
                }
            }

            for (b2Body* bodyToRemove : bodiesToRemove) {
                foundBodies.erase(std::remove(foundBodies.begin(), foundBodies.end(), bodyToRemove), foundBodies.end());
            }
            return 0;
        }
        b2Vec2 bodyPos = body->GetPosition();
        float distance = b2Distance(this->explosionCenter, bodyPos);
        if(distance < this->blastRadius) {
            foundBodies.push_back(body);
        }
        return 1;
    }
    //Como los fixtures que me da NO son en orden capaz primero me da al gusano  y despues la viga!