#include "Rocket.h"

Rocket::Rocket(b2Body* body, float damage, float radius) : Entity(body), damage(damage), radius(radius) {}

Rocket::~Rocket() {}

void Rocket::explode(std::set<b2Body*>& entitiesToRemove) {
    b2Body* rocket = this->body;
    b2Vec2 rocketPos = rocket->GetPosition();
    ExplosionQueryCallback explosionCallback(rocketPos, ROCKET_BLAST_RADIOUS);
    b2AABB aabb;
    aabb.lowerBound = rocketPos - b2Vec2(this->radius, this->radius);
    aabb.upperBound = rocketPos + b2Vec2(this->radius, this->radius);
    b2World* world = rocket->GetWorld();
    world->QueryAABB( &explosionCallback, aabb);
    
    for(b2Body* body : explosionCallback.foundBodies) {
        //Assuming it just affects worms
        Worm* worm = (Worm*) body->GetUserData().pointer;
        b2Vec2 bodyPos = body->GetPosition();
        float distance = b2Distance(rocketPos, bodyPos);
        float damage = this->damage * (1 - distance / this->radius);
        //Should fly away from the explosion
        worm->takeDamage(damage);
    }
    entitiesToRemove.insert(rocket);
}

void Rocket::beginCollisionWithBeam(Entity* otherBody, std::set<b2Body*>& entitiesToRemove) {
    UNUSED(otherBody);
    explode(entitiesToRemove);
}

void Rocket::beginCollisionWithWorm(Entity* otherBody, std::set<b2Body*>& entitiesToRemove) {
    UNUSED(otherBody);
    explode(entitiesToRemove);
}

void Rocket::beginCollisionWithRocket(Entity* otherBody, std::set<b2Body*>& entitiesToRemove) {
    UNUSED(otherBody);
    explode(entitiesToRemove);
}

void Rocket::preSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}

void Rocket::preSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}

void Rocket::preSolveCollisionWithRocket(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}

void Rocket::postSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}

void Rocket::postSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}

void Rocket::postSolveCollisionWithRocket(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}

void Rocket::endCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}

void Rocket::endCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}

void Rocket::endCollisionWithRocket(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}

