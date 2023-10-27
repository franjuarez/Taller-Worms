#include "game_world.h"

#include <iostream>

#define WORLD_WIDTH 100
#define WORLD_HEIGHT 70
#define WORLD_GRAVITY_X 0.0f
#define WORLD_GRAVITY_Y -9.8f

#define TIME_STEP 1/60.0f
#define VELOCITY_ITERATIONS 8
#define POSITION_ITERATIONS 3

#define LARGE_BEAM_WIDTH 6
#define SMALL_BEAM_WIDTH 3
#define BEAM_HEIGHT 0.8f

#define WORM_WIDTH 0.5f
#define WORM_HEIGHT 1.0f
#define WORM_DENSITY 1.0f
#define WORM_FRICTION 0.3f

#define MOVE_VELOCITY_X 0.2f


//Enum for walkable, sliding,
enum beamType{
    walkable,
    sliding
};

GameWorld::GameWorld() {
    b2Vec2 gravity(WORLD_GRAVITY_X, WORLD_GRAVITY_Y);
    this->world = new b2World(gravity);
    //Hardcoded (for now)
    std::cout << "Creating world" << std::endl;
    //Beam 1, walkable and large (where the player starts)
    createBeam(-10.0f, 4.0f, 0, true);
    
    std::cout << "Viga 2" << std::endl;
    // //Beam 2, walkable
    createBeam(-5.0f, 0.0f, 30, true);

    
    //Beam 3, sliding
    // createBeam(false);

    //"worm"
    createWorm(-9.0f, 5.0f);
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
    body->CreateFixture(&fd);
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
    gb.friction = 0.0f;
    gb.shape = &shape;
    beamBody->CreateFixture(&gb);

    beamType type = (angle > 45) ? sliding : walkable;
    beamBody->GetUserData().pointer = type;
}

void GameWorld::update() {
    this->world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
}


GameWorld::~GameWorld() {
    for (b2Body* body = this->world->GetBodyList(); body != NULL; body = body->GetNext()) {
        std::cout << "Destroying body" << std::endl;
        this->world->DestroyBody(body);
    }
    delete this->world;
}