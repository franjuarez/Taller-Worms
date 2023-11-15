#include "worm.h"

Worm::Worm(b2Body* body, std::vector<b2Body*>& entitiesToRemove, int id, int team, int direction, int health) : 
        Entity(body, entitiesToRemove),
        id(id), team(team), health(health), 
        direction(direction), currentAction(STANDING) {}


Worm::~Worm() {}

WormDTO Worm::getDTO(){
    Position pos(body->GetPosition().x, body->GetPosition().y);
    WormDTO dto(id, direction, team, health, pos, {});
    return dto;
}

void Worm::takeDamage(float damage){
    this->health -= damage;
    if(this->health < 0){
        this->health = 0;
    }
}

void Worm::die(){
    this->health = 0;
}

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
    takeDamage(damage);
    b2Vec2 direction = this->body->GetPosition() - explosionCenter;
    direction.Normalize();
    b2Vec2 impulse = b2Vec2(direction.x * damage / EXPLOSION_IMPULSE_FACTOR_X, damage / EXPLOSION_IMPULSE_FACTOR_Y);
    this->body->ApplyLinearImpulseToCenter(impulse, true);
}

void Worm::hitWithBat(){
    b2Vec2 pos = this->body->GetPosition();
    MeleeQueryCallback callback;
    b2AABB aabb;
    float batDir = this->direction == LEFT ? -BAT_WIDTH : BAT_WIDTH;
    aabb.lowerBound = b2Vec2(pos.x, pos.y - BAT_HEIGHT/2);
    aabb.upperBound = b2Vec2(pos.x + batDir, pos.y + BAT_HEIGHT/2);
    b2World* world = this->body->GetWorld();
    world->QueryAABB(&callback, aabb);
    for(b2Body* hitBody : callback.foundBodies) {
        //Assuming it just affects worms
        Worm* worm = (Worm*) hitBody->GetUserData().pointer;
        b2Vec2 direction = hitBody->GetPosition() - pos;
        direction.Normalize();
        b2Vec2 impulse = b2Vec2(direction.x * BAT_DAMAGE / BAT_IMPULSE_FACTOR, direction.y * BAT_DAMAGE / BAT_IMPULSE_FACTOR);
        hitBody->ApplyLinearImpulseToCenter(impulse, true);
        worm->takeDamage(BAT_DAMAGE);
    }
}

void Worm::applyFallDamage(b2Vec2 vel){
    //From auxiliar_physics_functions.cpp
    float height = calculateFallHeightFromVelocity(vel);
    if(height > MIN_HEIGHT_TO_DAMAGE){
        float damage = height > MAX_HEIGHT_DAMAGE ? MAX_HEIGHT_DAMAGE : height;
        takeDamage(damage);
    }
}

void Worm::beginCollisionWithWater(Entity* otherBody, b2Contact* contact) {
    otherBody->beginCollisionWithWorm(this, contact);
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

void Worm::beginCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    UNUSED(contact);

    applyFallDamage(this->body->GetLinearVelocity());

    Beam* beam = (Beam*) otherBody;

    if(beam->isWalkable()){
        b2Vec2 normal = contact->GetManifold()->localNormal;
        if(abs(normal.x) == 1){
            this->body->SetLinearDamping(0.0f);
            return;
        }
        this->body->SetLinearVelocity(b2Vec2(0,0));
        this->body->SetLinearDamping(INFINITE_DAMPING);
        this->currentAction = STANDING;
    }
}

void Worm::beginCollisionWithRocket(Entity* otherBody, b2Contact* contact) {
    applyFallDamage(this->body->GetLinearVelocity());
    otherBody->beginCollisionWithWorm(this, contact);
}

void Worm::beginCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    applyFallDamage(this->body->GetLinearVelocity());
    UNUSED(otherBody);
    UNUSED(contact);
}

void Worm::preSolveCollisionWithWater(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold) {
    otherBody->preSolveCollisionWithWorm(this, contact, oldManifold);
}

void Worm::preSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold) {
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
            this->body->SetLinearDamping(0.0f);
        }
    }
}

void Worm::preSolveCollisionWithRocket(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold) {
    otherBody->preSolveCollisionWithWorm(this, contact, oldManifold);
}

void Worm::postSolveCollisionWithWater(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse) {
    otherBody->postSolveCollisionWithWorm(this, contact, impulse);
}

void Worm::postSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse) {
    UNUSED(contact);
    Beam* beam = (Beam*) otherBody;
    if(beam->isWalkable()){

        b2Vec2 normal = contact->GetManifold()->localNormal;
        if(abs(normal.x) == 1){
            this->body->SetLinearDamping(0.0f);
            return;
        }
        this->body->SetLinearDamping(INFINITE_DAMPING);
        this->body->SetGravityScale(1.0f);
        if(this->body->GetLinearVelocity().Length() < VELOCITY_SMOOTH_BREAK){ //For smooth movement
            this->body->SetLinearVelocity(b2Vec2(0,0));
            this->currentAction = STANDING;
        }
    }
}

void Worm::endCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    this->body->SetLinearDamping(STANDARD_DAMPING);
    this->currentAction = this->currentAction == JUMPING ? JUMPING : EJECTED;
    UNUSED(otherBody);
    UNUSED(contact);
}