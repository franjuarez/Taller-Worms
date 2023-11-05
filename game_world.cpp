#include "game_world.h"

#define WORM_GROUP_INDEX -1

GameWorld::GameWorld() {
    this->world = new b2World(b2Vec2(WORLD_GRAVITY_X, WORLD_GRAVITY_Y));
    this->listener = new Listener(this->world, this->entitiesToRemove); //VER SI HACE FALTA HEAP O STACK
    this->world->SetContactListener(this->listener);
    
    //Hardcoded (for now)

    createBeam(-11.0f, 4.0f, 0, false);
    createBeam(-7.5f, 1.0f, 30, false);
    createBeam(-4.0f, 0.0f, -30, false);
    createBeam(-1.0f, -5.0f, 68, true);
    
    createWorm(-9, 7);
}

void GameWorld::createWorm(float startingX, float startingY){
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(startingX, startingY);
    b2Body* body = world->CreateBody(&bd);
    
    b2FixtureDef fd;
    b2PolygonShape shape;
    shape.SetAsBox(WORM_WIDTH, WORM_HEIGHT);
    fd.shape = &shape;
    fd.density = WORM_DENSITY;
    fd.friction = WORM_FRICTION;
    body->SetFixedRotation(true);
    fd.filter.groupIndex = WORM_GROUP_INDEX; //This way it doesn't collide with other worms
    body->CreateFixture(&fd);
    
    Worm* wormEntity = new Worm(body, RIGHT);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(wormEntity);

    this->worm = body;
}

void GameWorld::createBeam(float startingX, float startingY, float angle, bool large){
    b2BodyDef beam;
    beam.type = b2_staticBody;
    beam.position.Set(startingX, startingY);
    b2Body* beamBody = this->world->CreateBody(&beam);
    b2FixtureDef gb;
    b2PolygonShape shape;
    float beamWidth = large ? LARGE_BEAM_WIDTH : SMALL_BEAM_WIDTH;
    b2Vec2 vs[4];
    float angleInRadians = angle * b2_pi / 180.0f;
    float realX = cos(angleInRadians) * beamWidth;
    float realY = sin(angleInRadians) * beamWidth;
    vs[0].Set(0, 0);
    vs[1].Set(realX, realY);
    vs[2].Set(realX, realY + BEAM_HEIGHT);
    vs[3].Set(0, BEAM_HEIGHT);
    shape.Set(vs, 4);
    gb.shape = &shape;
    gb.friction = WORM_FRICTION;
    beamBody->CreateFixture(&gb);

    bool isWalkable = (abs(angle) > MAX_WALKABLE_BEAM_ANGLE) ? false : true;
    Beam* beamEntity = new Beam(beamBody, isWalkable);
    beamBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(beamEntity);
}

b2Body* GameWorld::createRocket(int direction){
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    float deltaX = (direction == LEFT) ? - WORM_WIDTH - ROCKET_WIDTH - 0.1f : WORM_WIDTH + ROCKET_WIDTH + 0.1f;
    float posX = this->worm->GetPosition().x + deltaX;
    float posY = this->worm->GetPosition().y;
    bd.position.Set(posX, posY);
    b2Body* body = this->world->CreateBody(&bd);
    body->IsBullet()
    ;
    b2FixtureDef fd;
    b2PolygonShape shape;
    shape.SetAsBox(ROCKET_WIDTH, ROCKET_HEIGHT);
    fd.shape = &shape;
    fd.density = ROCKET_DENSITY;
    body->CreateFixture(&fd);

    Rocket* rocketEntity = new Rocket(body, ROCKET_DAMAGE, ROCKET_BLAST_RADIOUS);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(rocketEntity);
    return body;
}

void GameWorld::wormLaunchRocket(float angle, int direction, float power){
    b2Body* rocket = createRocket(direction);
    float velX = ROCKET_MAX_SPEED * (power / 100.0f);
    float velY = ROCKET_MAX_SPEED * (power / 100.0f);
    int sign = (direction == LEFT) ? -1 : 1;
    velX = cos(angle * b2_pi / 180.0f) * velX * sign;
    velY = sin(angle * b2_pi / 180.0f) * velY;
    b2Vec2 rocketVel = b2Vec2(velX, velY);
    rocket->SetLinearVelocity(rocketVel);
}

void GameWorld::moveWormLeft(){
    b2Vec2 vel = this->worm->GetLinearVelocity(); 
    vel.x = -MOVE_VELOCITY;
    this->worm->SetLinearVelocity(vel);
}

void GameWorld::moveWormRight(){
    b2Vec2 vel = this->worm->GetLinearVelocity(); 
    vel.x = MOVE_VELOCITY;
    this->worm->SetLinearVelocity(vel);
}

void GameWorld::jumpWorm(b2Body* worm, float maxHeight, float distance){
    b2Vec2 vel = worm->GetLinearVelocity();
    if(vel.y != 0){
        return;
    }
    //From auxiliar_physics_functions.cpp
    b2Vec2 newVel = calculateInitialVelocityForMaxHeight(maxHeight, distance);
    newVel.x += vel.x;
    this->worm->SetLinearVelocity(newVel);
}

void GameWorld::jumpForwardWorm(){
    jumpWorm(this->worm, JUMP_FORWARD_MOVEMENT_Y, JUMP_FORWARD_MOVEMENT_X);
}

void GameWorld::jumpBackwardsWorm(){
    jumpWorm(this->worm, JUMP_BACKWARDS_MOVEMENT_Y, JUMP_BACKWARDS_MOVEMENT_X);   
}

void GameWorld::killDeadWorms(){
    if(this->worm != nullptr){
        Worm* wormData = (Worm*) this->worm->GetUserData().pointer;
        if(wormData->isDead()){
            std::cout << "Worm is dead" << std::endl;
            this->entitiesToRemove.insert(this->worm);
            this->worm = nullptr;
        }
    }
}

void GameWorld::removeEntities(){
    for(b2Body* body : this->entitiesToRemove){
        Entity* entity = (Entity*) body->GetUserData().pointer;
        this->world->DestroyBody(body);
        delete entity;
    }
    this->entitiesToRemove.clear();
}

void GameWorld::update() {
    this->world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

    killDeadWorms();
    removeEntities();
}

GameWorld::~GameWorld() {
    for (b2Body* body = this->world->GetBodyList(); body != NULL; body = body->GetNext()) {
        //delete user data
        Entity* entity = (Entity*) body->GetUserData().pointer;
        this->world->DestroyBody(body);
        delete entity;
    }
    delete this->listener;
    delete this->world;
}