#include "game_world.h"
#include <iostream>

GameWorld::GameWorld() {
    b2Vec2 gravity(WORLD_GRAVITY_X, WORLD_GRAVITY_Y);
    this->world = new b2World(gravity);
    this->listener = new Listener();
    this->world->SetContactListener(this->listener);
    
    //Hardcoded (for now)

    createBeam(-11.0f, 4.0f, 0, false);
    createBeam(-7.5f, 1.0f, 30, false);
    createBeam(-4.0f, 0.0f, -30, false);
    createBeam(-1.0f, -5.0f, 68, true);
    createWorm(-10.0f, 8.0f);
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
    fd.filter.groupIndex = -1; //This way it doesn't collide with other worms
    body->CreateFixture(&fd);
    EntityType type = Worm;
    body->GetUserData().pointer = type;
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
    gb.friction = BEAM_FRICTION;
    beamBody->CreateFixture(&gb);

    EntityType type = (abs(angle) > 45) ? SlidingBeam : WalkableBeam;
    beamBody->GetUserData().pointer = type;
}

void GameWorld::moveWormLeft(){
    b2Vec2 vel = this->worm->GetLinearVelocity(); 
    vel.x = -MOVE_VELOCITY_X;
    this->worm->SetLinearVelocity(vel);
}

void GameWorld::moveWormRight(){
    b2Vec2 vel = this->worm->GetLinearVelocity(); 
    vel.x = MOVE_VELOCITY_X;
    this->worm->SetLinearVelocity(vel);
}

void GameWorld::update() {
    this->world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
    // std::cout << "Worm position: " << this->worm->GetPosition().x << ", " << this->worm->GetPosition().y << std::endl;
}


GameWorld::~GameWorld() {
    for (b2Body* body = this->world->GetBodyList(); body != NULL; body = body->GetNext()) {
        this->world->DestroyBody(body);
    }
    delete this->world;
}