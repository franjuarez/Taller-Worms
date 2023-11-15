#include "rocket.h"

Rocket::Rocket(b2Body* body, std::vector<b2Body*>& entitiesToRemove, float damage, float radius) : 
    Entity(body, entitiesToRemove), damage(damage), radius(radius) {}

Rocket::~Rocket() {}

void Rocket::explode() {
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
        worm->handleExplosion(damage, rocketPos);
    }
    this->entitiesToRemove.push_back(rocket);
}

WeaponDTO Rocket::getDTO(){
    Position pos(this->body->GetPosition().x, this->body->GetPosition().y);
    b2Vec2 vel = this->body->GetLinearVelocity();
    WeaponDTO dto(0, 1, pos, vel.x, vel.y);
    return dto;
}

void Rocket::beginCollisionWithWater(Entity* otherBody, b2Contact* contact) {
    otherBody->beginCollisionWithRocket(this, contact);
}

void Rocket::beginCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    explode();
}

void Rocket::beginCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    Worm* worm = (Worm*) otherBody;
    worm->applyFallDamage(worm->body->GetLinearVelocity());
    explode();
}

void Rocket::beginCollisionWithRocket(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    explode();
}