#include "worm.h"
#include <iostream>
Worm::Worm(b2Body* body, b2Fixture* footSensor, std::unordered_set<b2Body*>& entitiesToRemove, int id, int team, int direction, float health, std::vector<int> weapons) : 
        Entity(body, entitiesToRemove, EntityWorm),
        id(id), team(team), health(health), 
        direction(direction), footSensor(footSensor), currentAction(STANDING),
        weapons(weapons), invincible(false) {
            max_ammo_per_weapon[BAZOOKA] = CONFIG.getBazookaMaxAmmo();
            max_ammo_per_weapon[GREEN_GRENADE] = CONFIG.getGreenGrenadeMaxAmmo();
            max_ammo_per_weapon[BAT] = CONFIG.getBatMaxAmmo();
            max_ammo_per_weapon[REMOTE_OPERATED] = CONFIG.getTeleportMaxAmmo();
            max_ammo_per_weapon[MORTAR] = CONFIG.getMortarMaxAmmo();
            max_ammo_per_weapon[RED_GRENADE] = CONFIG.getRedGrenadeMaxAmmo();
            max_ammo_per_weapon[BANANA] = CONFIG.getBananaMaxAmmo();
            max_ammo_per_weapon[DYNAMITE] = CONFIG.getDynamiteMaxAmmo();
            max_ammo_per_weapon[HOLY_GRENADE] = CONFIG.getHolyGrenadeMaxAmmo();
            max_ammo_per_weapon[AIR_ATTACK] = CONFIG.getAirAttackMaxAmmo();
        }


Worm::~Worm() {}

WormDTO Worm::getDTO(){
    Position pos(body->GetPosition().x, body->GetPosition().y);
    float velX = body->GetLinearVelocity().x;
    float velY = body->GetLinearVelocity().y;
    int isOnGround = this->onGround;
    WormDTO dto(id, direction, team, health, velX, velY, isOnGround, pos, weapons);
    return dto;
}

void Worm::takeDamage(float damage){
    if(this->invincible){
        return;
    }
    this->health -= damage;
    if(this->health < 0){
        this->health = 0;
    }
}

void Worm::die(){
    if(this->invincible){
        return;
    }
    this->health = 0;
}

void Worm::addHealth(int additionalHealth){
    this->health += additionalHealth;
    if (this->health > CONFIG.getWormMaxHealth()){
        this->health = CONFIG.getWormMaxHealth();
    }
}

void Worm::toggleInvincible(){
    this->invincible = !this->invincible;
}

bool Worm::isDead(){
    return this->health <= 0;
}

int Worm::getId(){
    return this->id;
}

void Worm::changeDirection(int direction){
    this->direction = direction;
}

bool Worm::hasAmmo(int weaponId){
    if(weaponId < 0 || weaponId >= this->weapons.size()){
        throw std::runtime_error("Invalid weapon id");
    }
    return this->weapons[weaponId] > 0 || this->weapons[weaponId] == INFINITE_AMUNITION;
}

void Worm::reduceAmmo(int weaponId){
    if(weaponId < 0 || weaponId >= this->weapons.size()){
        throw std::runtime_error("Invalid weapon id");
    }
    if(this->weapons[weaponId] == INFINITE_AMUNITION){
        return;
    }
    this->weapons[weaponId] = this->weapons[weaponId] == 0 ? 0 : this->weapons[weaponId] - 1;
}

void Worm::addAmmo(int weaponId, int amount){
    if(weaponId < 0 || weaponId >= this->weapons.size()){
        throw std::runtime_error("Invalid weapon id");
    }
    if(this->weapons[weaponId] == INFINITE_AMUNITION){
        return;
    }
    this->weapons[weaponId] += amount;
    if(this->weapons[weaponId] > max_ammo_per_weapon[weaponId]){
        this->weapons[weaponId] = max_ammo_per_weapon[weaponId];
    }
}

void Worm::getAllWeapons(){
    for(int i = 0; i < this->weapons.size(); i++){
        this->weapons[i] = INFINITE_AMUNITION;
    }
}

void Worm::move(int direction){
    if(!this->onGround){
        return;
    }
    
    this->currentAction = MOVING;
    this->direction = direction;

    b2Vec2 vel(0,0);
    if(direction == LEFT){
        vel.x = -CONFIG.getWormMoveVelocity();
    } else {
        vel.x = CONFIG.getWormMoveVelocity();
    }
    this->body->SetLinearVelocity(vel);
}

void Worm::jump(float maxHeight, float distance){
    if(!this->onGround|| this->currentAction == JUMPING){
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
        jump(CONFIG.getJumpForwardMovementY(), - CONFIG.getJumpForwardMovementX());
    } else {
        jump(CONFIG.getJumpForwardMovementY(), CONFIG.getJumpForwardMovementX());
    }
}

void Worm::jumpBackwards(){
    if(this->direction == LEFT){
        jump(CONFIG.getJumpBackwardsMovementY(), CONFIG.getJumpBackwardsMovementX());
    } else {
        jump(CONFIG.getJumpBackwardsMovementY(), -CONFIG.getJumpBackwardsMovementX());
    }
}

void Worm::handleExplosion(float damage, b2Vec2 explosionCenter){
    this->currentAction = EJECTED;
    takeDamage(damage);
    b2Vec2 direction = this->body->GetPosition() - explosionCenter;
    direction.Normalize();
    if(this->body->GetLinearVelocity().y < 0){
        this->body->SetLinearVelocity(b2Vec2(0,0));
    }
    b2Vec2 impulse = b2Vec2(direction.x * damage / CONFIG.getProjectileImpulseFactorX(), damage / CONFIG.getProjectileImpulseFactorY());
    this->body->ApplyLinearImpulseToCenter(impulse, true);
}

void Worm::hitWithBat(int direction){
    this->direction = direction;
    b2Vec2 pos = this->body->GetPosition();
    MeleeQueryCallback callback;
    b2AABB aabb;
    float batDir = this->direction == LEFT ? -BAT_WIDTH: BAT_WIDTH;
    aabb.lowerBound = b2Vec2(pos.x + batDir, pos.y - BAT_HEIGHT/2);
    aabb.upperBound = b2Vec2(pos.x + batDir, pos.y + BAT_HEIGHT/2);
    // std::cout << "Worm pos: " << pos.x << ", " << pos.y << std::endl; 
    // std::cout << "Bat AABB: " << aabb.lowerBound.x << ", " << aabb.lowerBound.y << " - " << aabb.upperBound.x << ", " << aabb.upperBound.y << std::endl;
    b2World* world = this->body->GetWorld();
    world->QueryAABB(&callback, aabb);
    for(b2Body* hitBody : callback.foundBodies) {
        //Assuming it just affects worms other than me
        if(hitBody == this->body){
            continue;
        }
        Worm* worm = (Worm*) hitBody->GetUserData().pointer;
        b2Vec2 direction = hitBody->GetPosition() - pos;
        direction.Normalize();
        b2Vec2 impulse = b2Vec2(direction.x * CONFIG.getBatDamage() / CONFIG.getBatImpulseFactor(), 0.8 * CONFIG.getBatDamage() / CONFIG.getBatImpulseFactor());
        hitBody->ApplyLinearImpulseToCenter(impulse, true);
        worm->takeDamage(CONFIG.getBatDamage());
    }
}

void Worm::applyFallDamage(b2Vec2 vel){
    //From auxiliar_physics_functions.cpp
    float height = calculateFallHeightFromVelocity(vel);
    if(height > CONFIG.getMinHeightToDamage()){
        float damage = height > CONFIG.getMaxHeightDamage() ? CONFIG.getMaxHeightDamage() : height;
        takeDamage(damage);
    }
}

void Worm::beginCollisionWithWater(Entity* otherBody, b2Contact* contact) {
    otherBody->beginCollisionWithWorm(this, contact);
}

void Worm::beginCollisionWithSupplyBox(Entity* otherBody, b2Contact* contact) {
    otherBody->beginCollisionWithWorm(this, contact);
}

void Worm::beginCollisionWithProjectile(Entity* otherBody, b2Contact* contact) {
    otherBody->beginCollisionWithWorm(this, contact);
}

void Worm::moveOnWalkableBeam(b2Body* worm, b2Vec2 normal){
    b2Vec2 vel = worm->GetLinearVelocity();
    b2Vec2 perpendicular = b2Vec2(-normal.y, normal.x);
    int sign = (vel.x > 0) ? -1 : 1;
    if(normal.y <= 0){
        sign *=-1;
    }
    if(abs(normal.x) == 1){
        perpendicular = b2Vec2(normal.x * sign, 0);
    }
    worm->SetLinearDamping(STANDARD_DAMPING);
    worm->SetGravityScale(0.0f);
    float velX = perpendicular.x * vel.Length() * sign;
    float velY = perpendicular.y * vel.Length() * sign;
    worm->SetLinearVelocity(b2Vec2(velX, velY));
}

void Worm::beginCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    UNUSED(contact);
    if(contact->GetFixtureA() == this->footSensor || contact->GetFixtureB() == this->footSensor){
        this->groundsTouching += 1;
        applyFallDamage(this->body->GetLinearVelocity());
        return;
    }
    if(this->groundsTouching > 0){
        this->onGround = true;
    }

    Beam* beam = (Beam*) otherBody;

    if(beam->isWalkable()){
        b2Vec2 normal = contact->GetManifold()->localNormal;
        if(!this->onGround){
            this->body->SetLinearDamping(0.0f);
            return;
        }
        this->body->SetLinearVelocity(b2Vec2(0,0));
        this->body->SetLinearDamping(INFINITE_DAMPING);
        this->currentAction = STANDING;
    }
}


void Worm::preSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold) {
    if(contact->GetFixtureA() == this->footSensor || contact->GetFixtureB() == this->footSensor){
        return;
    }
    Beam* beam = (Beam*) otherBody;
    if(beam->isWalkable()){
        if(!this->onGround){
            return;
        }
        if(this->currentAction == STANDING){
            this->body->SetLinearDamping(INFINITE_DAMPING);
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

void Worm::postSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse) {
    if(contact->GetFixtureA() == this->footSensor || contact->GetFixtureB() == this->footSensor){
        return;
    }
    UNUSED(contact);
    Beam* beam = (Beam*) otherBody;
    if(beam->isWalkable()){
        if(!this->onGround){
            return;
        }
        this->body->SetLinearDamping(INFINITE_DAMPING);
        this->body->SetGravityScale(1.0f);
        if(this->currentAction == MOVING && this->body->GetLinearVelocity().Length() < VELOCITY_SMOOTH_BREAK){ //For smooth movement
            this->body->SetLinearVelocity(b2Vec2(0,0));
            this->currentAction = STANDING;
        }
    }
}

void Worm::endCollisionWithBeam(Entity* otherBody, b2Contact* contact) {
    if(contact->GetFixtureA() == this->footSensor || contact->GetFixtureB() == this->footSensor){
        this->groundsTouching -= 1;
    }
    if(this->groundsTouching <= 0){
        this->onGround = false;

    }
    this->body->SetLinearDamping(STANDARD_DAMPING);
    this->body->SetGravityScale(1.0f);
    UNUSED(otherBody);
    UNUSED(contact);
}
