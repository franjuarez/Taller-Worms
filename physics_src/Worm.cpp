#include "Worm.h"

Worm::Worm(b2Body* body, uint id, int direction) : Entity(body), id(id), health(WORM_INITIAL_HEALTH), direction(direction) {}


Worm::~Worm() {}

void Worm::takeDamage(float damage){
    this->health -= damage;
}

bool Worm::isDead(){
    return this->health <= 0;
}

uint Worm::getId(){
    return this->id;
}

WormDTO Worm::getDTO(){
    Position pos(body->GetPosition().x, body->GetPosition().y);
    WormDTO dto(id, 0, health, pos);
    return dto;
}

void Worm::moveOnWalkableBeam(b2Body* worm, b2Vec2 normal){
    b2Vec2 vel = worm->GetLinearVelocity();
    b2Vec2 perpendicular = b2Vec2(-normal.y, normal.x);
    int sign = (vel.x > 0) ? -1 : 1;
    if(normal.y <= 0){
        if(normal.x != 0)
            return;
        sign *=-1;
    }
    worm->SetGravityScale(0.0f);
    float velX = perpendicular.x * vel.Length() * sign;
    float velY = perpendicular.y * vel.Length() * sign;
    worm->SetLinearVelocity(b2Vec2(velX, velY));
}

void Worm::beginCollisionWithBeam(Entity* otherBody, std::set<b2Body*>& entitiesToRemove) {
    UNUSED(entitiesToRemove);
    Beam* beam = (Beam*) otherBody;
    //From auxiliar_physics_functions.cpp
    float height = calculateFallHeightFromVelocity(this->body->GetLinearVelocity());

    if(height > MIN_HEIGHT_TO_DAMAGE){
        float damage = height > MAX_HEIGHT_DAMAGE ? MAX_HEIGHT_DAMAGE : height;
        this->takeDamage(damage);
    }

    if(beam->isWalkable()){
        this->body->SetLinearVelocity(b2Vec2(0,0));
        this->body->SetLinearDamping(INFINITE_DAMPING);
    }
}

void Worm::beginCollisionWithRocket(Entity* otherBody, std::set<b2Body*>& entitiesToRemove) {
    otherBody->beginCollisionWithWorm(this, entitiesToRemove);
}

void Worm::beginCollisionWithWorm(Entity* otherBody, std::set<b2Body*>& entitiesToRemove) {
    UNUSED(otherBody);
    UNUSED(entitiesToRemove);
}

//Cuesta reconocer cuand oesta caminando/saltando/volando. 
//Bug conocido: cuando de alguna manera (volar por explosion por ej)
//Llega a mas velocidad q la de movimiento, resbala por la viga.
void Worm::preSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    Beam* beam = (Beam*) otherBody;
    if(beam->isWalkable()){
        this->body->SetLinearDamping(STANDARD_DAMPING);
        if(this->body->GetLinearVelocity().Length() <= MOVE_VELOCITY){
            b2Vec2 normal = contact->GetManifold()->localNormal;
            moveOnWalkableBeam(this->body, normal);
        }
    }
}

void Worm::preSolveCollisionWithRocket(Entity* otherBody, b2Contact* contact) {
    UNUSED(contact);
    Rocket* rocket = (Rocket*) otherBody;
    rocket->preSolveCollisionWithWorm(this, contact);
}

void Worm::preSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}

void Worm::postSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    UNUSED(contact);
    Beam* beam = (Beam*) otherBody;
    if(beam->isWalkable()){
        this->body->SetLinearDamping(STANDARD_DAMPING);
        this->body->SetGravityScale(1.0f);
        if(this->body->GetLinearVelocity().Length() < VELOCITY_SMOOTH_BREAK){ //For smooth movement
            this->body->SetLinearVelocity(b2Vec2(0,0));
        }
    }
}

void Worm::postSolveCollisionWithRocket(Entity* otherBody, b2Contact* contact) {
    UNUSED(contact);
    UNUSED(otherBody);
}

void Worm::postSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}

void Worm::endCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}

void Worm::endCollisionWithRocket(Entity* otherBody, b2Contact* contact) {
    UNUSED(contact);
    UNUSED(otherBody);
}

void Worm::endCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}
