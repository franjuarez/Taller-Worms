#include "explosion_handler.h"
#include <iostream>

// ExplosionQueryCallback::ExplosionQueryCallback() { }
ExplosionQueryCallback::ExplosionQueryCallback(b2Vec2 explosionCenter, float blastRadius) :
                                            explosionCenter(explosionCenter), blastRadius(blastRadius) {}

float ExplosionQueryCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) {
        std::cout << "ReportFixture" << std::endl;
        b2Body* body = fixture->GetBody();
        //Edge case: Does this explosion affect something else? Or just Worms?
        Entity* type = (Entity*) body->GetUserData().pointer; 
        if (type->getEntityType() != EntityWorm){
            return -1;
        }
        for(collisionData data : foundBodies) { //COMO USO UN FOR EN EL RAYCAST LO ENCUENTRA EN DIFERENTES ITERACIONES!
            if (data.body == body){
                return -1;
            }
        }
        b2Vec2 bodyPos = body->GetPosition();
        float distance = b2Distance(this->explosionCenter, bodyPos);
        if(distance < this->blastRadius) {
            collisionData data;
            data.body = body;
            data.pointOfCollision = point;
            foundBodies.push_back(data);
        }
        return 1;
    }

// bool ExplosionQueryCallback::ReportFixture(b2Fixture* fixture) {
//         b2Body* body = fixture->GetBody();
//         //Edge case: Does this explosion affect something else? Or just Worms?
//         Entity* type = (Entity*) body->GetUserData().pointer; 
//         if (type->getEntityType() != EntityWorm){
//             return true;
//         }
//         b2Vec2 bodyPos = body->GetPosition();
//         float distance = b2Distance(this->explosionCenter, bodyPos);
//         if(distance < this->blastRadius) {
//             foundBodies.push_back(body);
//         }
//         return true;
//     }
    