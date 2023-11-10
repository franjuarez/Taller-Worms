#include "game_world.h"

#define WORM_GROUP_INDEX -1

GameWorld::GameWorld() {
    this->world = new b2World(b2Vec2(WORLD_GRAVITY_X, WORLD_GRAVITY_Y));
    this->listener = new Listener(this->world); //VER SI HACE FALTA HEAP O STACK
    this->world->SetContactListener(this->listener);
    
    //Hardcoded (for now)

    // createBeam(-11.0f, 4.0f, 0, false);
    // createBeam(-7.5f, 1.0f, 30, true);
    // createBeam(-4.0f, 0.0f, -30, false);
    // createBeam(-1.0f, -5.0f, 68, true);

    createBeam(10.0f, 10.0f, 0, true);
    createBeam(16.0f, 8.0f, 0, true);
    createBeam(22.0f, 6.0f, 0, true);
    createBeam(28.0f, 4.0f, 0, true);
    createBeam(34.0f, 2.0f, 0, true);
    createBeam(40.0f, 0.0f, 0, true);
    createBeam(46.0f, -2.0f, 0, true);
    // createBeam(10.0f, 12.0f, 0, false);
    // createBeam(15.0f, 5.0f, 50, true);
    // createBeam(10.0f, 3.0f, -10, false);
    
    createWorm(14.0f, 15.0f, 0, 0);
    // createWorm(12.0f, 12.0f, 1, 1);
}

void GameWorld::createWorm(float startingX, float startingY, int id, int team){
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(startingX, startingY);
    b2Body* body = this->world->CreateBody(&bd);

    b2FixtureDef fd;
    b2PolygonShape shape;
    shape.SetAsBox(WORM_WIDTH/2, WORM_HEIGHT/2);
    fd.shape = &shape;
    fd.density = WORM_DENSITY;
    fd.friction = WORM_FRICTION;
    body->SetFixedRotation(true);
    //fd.filter.groupIndex = WORM_GROUP_INDEX; //This way it doesn't collide with other worms SALMON
    body->CreateFixture(&fd);

    Worm* wormEntity = new Worm(body, entitiesToRemove, id, team, RIGHT); //Starts facing right
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(wormEntity);

    this->worms[id] = body;
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
    vs[2].Set(realX, realY - BEAM_HEIGHT);
    vs[3].Set(0, -BEAM_HEIGHT);
    shape.Set(vs, 4);
    gb.shape = &shape;
    gb.friction = WORM_FRICTION;
    beamBody->CreateFixture(&gb);

    bool isWalkable = (abs(angle) > MAX_WALKABLE_BEAM_ANGLE) ? false : true;
    Beam* beamEntity = new Beam(beamBody, entitiesToRemove, isWalkable);
    beamBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(beamEntity);
}

b2Body* GameWorld::createRocket(b2Body* worm, int direction){
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    float deltaX = (direction == LEFT) ? - WORM_WIDTH/2 - ROCKET_WIDTH/2 - 0.1f : WORM_WIDTH/2 + ROCKET_WIDTH/2 + 0.1f;
    float posX = worm->GetPosition().x + deltaX;
    float posY = worm->GetPosition().y;
    bd.position.Set(posX, posY);
    b2Body* body = this->world->CreateBody(&bd);
    body->IsBullet();
    
    b2FixtureDef fd;
    b2PolygonShape shape;
    shape.SetAsBox(ROCKET_WIDTH/2, ROCKET_HEIGHT/2);
    fd.shape = &shape;
    fd.density = ROCKET_DENSITY;
    body->CreateFixture(&fd);

    Rocket* rocketEntity = new Rocket(body, entitiesToRemove, ROCKET_DAMAGE, ROCKET_BLAST_RADIOUS);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(rocketEntity);

    projectiles.push_back(body);
    return body;
}

void GameWorld::checkWormExists(uint id){ //Capaz conviene un array con pos de id? es mas rapido pero mas choto de acceder
    if(this->worms.find(id) == this->worms.end()){
        throw std::invalid_argument("Worm with id " + std::to_string(id) + " does not exist");
    }
}

void GameWorld::wormLaunchRocket(int id, float angle, int direction, float power){
    checkWormExists(id);
    b2Body* worm = this->worms[id];
    b2Body* rocket = createRocket(worm, direction);
    float velX = ROCKET_MAX_SPEED * (power / 100.0f);
    float velY = ROCKET_MAX_SPEED * (power / 100.0f);
    int sign = (direction == LEFT) ? -1 : 1;
    velX = cos(angle * b2_pi / 180.0f) * velX * sign;
    velY = sin(angle * b2_pi / 180.0f) * velY;
    b2Vec2 rocketVel = b2Vec2(velX, velY);
    rocket->SetLinearVelocity(rocketVel);
}

void GameWorld::moveWorm(int id, int direction){
    checkWormExists(id);
    b2Body* worm = this->worms[id];
    Worm* wormData = (Worm*) worm->GetUserData().pointer;
    wormData->move(direction);
}

void GameWorld::jumpForwardWorm(int id){
    checkWormExists(id);
    b2Body* worm = this->worms[id];
    Worm* wormData = (Worm*) worm->GetUserData().pointer;
    wormData->jumpForward();
}

void GameWorld::jumpBackwardsWorm(int id){
    checkWormExists(id);
    b2Body* worm = this->worms[id];
    Worm* wormData = (Worm*) worm->GetUserData().pointer;
    wormData->jumpBackwards();
}

void GameWorld::removeWorm(b2Body* worm){
    for(auto it = this->worms.begin(); it != this->worms.end(); ++it){
        if(it->second == worm){
            this->worms.erase(it);
            break;
        }
    }
}

void GameWorld::removeProjectile(b2Body* projectile){
    for(auto it = this->projectiles.begin(); it != this->projectiles.end(); ++it){
        if(*it == projectile){
            this->projectiles.erase(it);
            break;
        }
    }
}


void GameWorld::removeEntities(){
    for(b2Body* body : this->entitiesToRemove){
        Entity* entity = (Entity*) body->GetUserData().pointer;
        if(typeid(*entity) == typeid(Worm)){
            removeWorm(body);
        } else if(typeid(*entity) == typeid(Rocket)){
            removeProjectile(body);
        }
        this->world->DestroyBody(body);
        delete entity;
    }
    this->entitiesToRemove.clear();
}

void GameWorld::update() {
    this->world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
    removeEntities();
}

GameDynamic* GameWorld::getGameStatus(int id){
    std::vector<WormDTO> wormsDTO;
    for (auto& worm : this->worms) {
        Worm* wormData = (Worm*) worm.second->GetUserData().pointer;
        wormsDTO.push_back(wormData->getDTO());
    }

    std::vector<ProjectileDTO> projectilesDTO;
    for(b2Body* projectile : this->projectiles){
        Rocket* rocketData = (Rocket*) projectile->GetUserData().pointer;
        projectilesDTO.push_back(rocketData->getDTO());
    }
    GameDynamic* dynamicData = new GameDynamic(id, wormsDTO, projectilesDTO);
    return dynamicData;
}

GameWorld::~GameWorld() {
    for (b2Body* body = this->world->GetBodyList(); body != NULL; body = body->GetNext()) {
        //deleting user data
        Entity* entity = (Entity*) body->GetUserData().pointer;
        this->world->DestroyBody(body);
        delete entity;
    }
    delete this->listener;
    delete this->world;
}