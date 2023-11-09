#include "Worm.h"

Worm::Worm(b2Body* body, int id, int team, int direction) : Entity(body), id(id), team(team), health(WORM_INITIAL_HEALTH), direction(direction) {}


Worm::~Worm() {}

// void Worm::takeDamage(float damage){
//     this->health -= damage;
// }

bool Worm::isDead(){
    return this->health <= 0;
}

int Worm::getId(){
    return this->id;
}

void Worm::move(int direction){
    if(this->currentAction == JUMPING || this->currentAction == EJECTED){
        return;
    }
    
    this->currentAction = MOVING;
    this->direction = direction;

    b2Vec2 vel;
    if(direction == LEFT){
        vel.x = -MOVE_VELOCITY;
    } else {
        vel.x = MOVE_VELOCITY;
    }
    this->body->SetLinearVelocity(vel);
}

void Worm::jump(float maxHeight, float distance){
    if(this->currentAction == JUMPING || this->currentAction == EJECTED){
        return;
    }
    this->currentAction = JUMPING;
    std::cout << "Jumping" << "height" << maxHeight << "distance" << distance << std::endl;
    b2Vec2 vel = this->body->GetLinearVelocity();
    //From auxiliar_physics_functions.cpp
    b2Vec2 newVel = calculateInitialVelocityForMaxHeight(maxHeight, distance);
    newVel.x += vel.x;
    this->body->SetLinearVelocity(newVel);
}

void Worm::jumpForward(){
    if(this->direction == LEFT){
        jump(JUMP_FORWARD_MOVEMENT_Y, -JUMP_FORWARD_MOVEMENT_X);
    } else {
        jump(JUMP_FORWARD_MOVEMENT_Y, JUMP_FORWARD_MOVEMENT_X);
    }
}

void Worm::jumpBackwards(){
    if(this->direction == LEFT){
        jump(JUMP_BACKWARDS_MOVEMENT_Y, JUMP_BACKWARDS_MOVEMENT_X);
    } else {
        jump(JUMP_BACKWARDS_MOVEMENT_Y, -JUMP_BACKWARDS_MOVEMENT_X);
    }
}

void Worm::handleExplosion(float damage, b2Vec2 explosionCenter){
    this->currentAction = EJECTED;
    this->health -= damage;
    b2Vec2 direction = this->body->GetPosition() - explosionCenter;
    direction.Normalize();
    b2Vec2 impulse = b2Vec2(direction.x * damage / 4, direction.y * damage / 4);
    this->body->ApplyLinearImpulseToCenter(impulse, true);
}

WormDTO Worm::getDTO(){
    Position pos(body->GetPosition().x, body->GetPosition().y);
    WormDTO dto(id, direction, 0, health, pos);
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
    worm->SetLinearDamping(STANDARD_DAMPING);
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
        this->health -= damage;
    }

    if(beam->isWalkable()){
        this->body->SetLinearVelocity(b2Vec2(0,0));
        this->body->SetLinearDamping(INFINITE_DAMPING);
        this->currentAction = STANDING;
    }
}

void Worm::beginCollisionWithRocket(Entity* otherBody, std::set<b2Body*>& entitiesToRemove) {
    otherBody->beginCollisionWithWorm(this, entitiesToRemove);
}

void Worm::beginCollisionWithWorm(Entity* otherBody, std::set<b2Body*>& entitiesToRemove) {
    UNUSED(otherBody);
    UNUSED(entitiesToRemove);
}

void Worm::preSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    Beam* beam = (Beam*) otherBody;
    if(beam->isWalkable()){
        if(this->currentAction == STANDING){
            this->body->SetLinearDamping(0.0f);
        }
        if(this->currentAction == MOVING){
            b2Vec2 normal = contact->GetManifold()->localNormal;
            moveOnWalkableBeam(this->body, normal);
        }
        if(this->currentAction == JUMPING){
            this->body->SetLinearDamping(STANDARD_DAMPING);
        }
        if(this->currentAction == EJECTED){
            this->body->SetGravityScale(0.0f);
            this->body->SetLinearDamping(0.0f);
            contact->SetFriction(0.0f);
        }
    }
}

void Worm::preSolveCollisionWithRocket(Entity* otherBody, b2Contact* contact) {
    UNUSED(contact);
    otherBody->preSolveCollisionWithWorm(this, contact);
}

void Worm::preSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    UNUSED(otherBody);
    UNUSED(contact);
}

void Worm::postSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    UNUSED(contact);
    Beam* beam = (Beam*) otherBody;
    if(beam->isWalkable()){
        this->body->SetLinearDamping(INFINITE_DAMPING);
        this->body->SetGravityScale(1.0f);
        if(this->body->GetLinearVelocity().Length() < VELOCITY_SMOOTH_BREAK){ //For smooth movement
            this->body->SetLinearVelocity(b2Vec2(0,0));
            this->currentAction = STANDING;
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
    this->body->SetLinearDamping(STANDARD_DAMPING);
    this->currentAction = EJECTED;
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
