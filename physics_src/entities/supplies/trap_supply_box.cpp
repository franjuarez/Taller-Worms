#include "trap_supply_box.h"

#define DEGTORAD 0.0174532925199432957f

TrapSupplyBox::TrapSupplyBox(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, int type) : 
    SupplyBox(body, entitiesToRemove, type) {}

void TrapSupplyBox::beginCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    b2Vec2 pos = this->body->GetPosition();
    b2World* world = this->body->GetWorld();
    float radius = CONFIG.getSupplyBoxTrapRadius();
    float damage = CONFIG.getSupplyBoxTrapDamage();
    int numberOfRays = 20;
    std::unordered_set<b2Body*> allFoundBodies;
    for(int i = 0; i < numberOfRays; i++){
        float angle = (i / (float)numberOfRays) * 360 * DEGTORAD;
        b2Vec2 rayDir( sinf(angle), cosf(angle) );
        b2Vec2 rayEnd = pos + radius * rayDir;
        ExplosionQueryCallback callback(pos, radius);
        world->RayCast(&callback, pos, rayEnd);
        for(b2Body* body : callback.foundBodies) {
            if(allFoundBodies.find(body) != allFoundBodies.end()){
                continue;
            }
            //Assuming it just affects worms
            Worm* worm = (Worm*) body->GetUserData().pointer;
            b2Vec2 bodyPos = body->GetPosition();
            float distance = b2Distance(pos, bodyPos);
            float damage = damage * (1 - distance / radius);
            worm->handleExplosion(damage, pos);
            allFoundBodies.insert(body);
        }
    }
    this->entitiesToRemove.insert(this->body);
}

TrapSupplyBox::~TrapSupplyBox() {}