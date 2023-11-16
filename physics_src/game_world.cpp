#include "game_world.h"

#define WORM_GROUP_INDEX -1

GameWorld::GameWorld(GameMap* gameMap) {
    this->world = new b2World(b2Vec2(WORLD_GRAVITY_X, WORLD_GRAVITY_Y));
    this->listener = new Listener(this->world); //VER SI HACE FALTA HEAP O STACK
    this->world->SetContactListener(this->listener);
    this->lastProjectileId = 0;

    createWater();

    std::vector<BeamDTO> beams = gameMap->getBeams();
    for (BeamDTO& beam : beams) {
        float x = beam.getPosition().getX();
        float y = beam.getPosition().getY();
        bool large = beam.getBeamLength() == LARGE_BEAM_WIDTH ? true : false;
        createBeam(x, y, beam.getAngle(), large);
    }

    std::vector<WormDTO> worms = gameMap->getWorms();
    for (WormDTO& worm : worms) {
        float x = worm.getPosition().getX();
        float y = worm.getPosition().getY();
        int id = worm.getId();
        int team = worm.getTeam();
        int health = worm.getHealth();
        createWorm(x, y, id, team, health);
    }
}

void GameWorld::createWater(){
    b2BodyDef bd;
    bd.type = b2_staticBody;
    bd.position.Set(WORLD_WIDTH/2, 0);
    b2Body* body = this->world->CreateBody(&bd);
    b2FixtureDef fd;
    b2PolygonShape shape;
    shape.SetAsBox(WORLD_WIDTH/2, 0.1f);
    fd.shape = &shape;
    body->CreateFixture(&fd);

    Water* waterEntity = new Water(body, entitiesToRemove);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(waterEntity);
}

void GameWorld::createWorm(float startingX, float startingY, int id, int team, int health){
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
    fd.filter.groupIndex = WORM_GROUP_INDEX; //This way it doesn't collide with other worms SALMON
    body->CreateFixture(&fd);

    Worm* wormEntity = new Worm(body, entitiesToRemove, id, team, RIGHT, health); //Starts facing right
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

    projectiles[this->lastProjectileId] = body;

    Rocket* rocketEntity = new Rocket(body, entitiesToRemove, this->lastProjectileId, ROCKET_DAMAGE, ROCKET_BLAST_RADIOUS);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(rocketEntity);

    this->lastProjectileId++;
    return body;
}

void GameWorld::checkWormExists(int id){ //Capaz conviene un array con pos de id? es mas rapido pero mas choto de acceder
    //Check if the worm exists and if its dead and throw error
    if(this->worms.find(id) == this->worms.end()){
        throw std::runtime_error("Worm does not exist");
    }
    Worm* worm = (Worm*) this->worms[id]->GetUserData().pointer;
    if(worm->isDead()){
        throw std::runtime_error("Worm is dead");
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

void GameWorld::wormHitWithBat(int id){
    checkWormExists(id);
    b2Body* worm = this->worms[id];
    Worm* wormData = (Worm*) worm->GetUserData().pointer;
    wormData->hitWithBat();
}

bool GameWorld::checkValidTpPosition(float x, float y){
    b2AABB aabb;
    aabb.lowerBound = b2Vec2(x - WORM_WIDTH/2, y - WORM_HEIGHT/2);
    aabb.upperBound = b2Vec2(x + WORM_WIDTH/2, y + WORM_HEIGHT/2);
    TeleportQueryCallback callback;
    this->world->QueryAABB(&callback, aabb);
    return callback.validTeleport;
}

bool GameWorld::teleportWorm(int id, float x, float y){
    checkWormExists(id);
    if(checkValidTpPosition(x, y)){
        b2Body* worm = this->worms[id];
        worm->SetTransform(b2Vec2(x, y), 0);
        worm->SetLinearVelocity(b2Vec2(0, 0));
        return true;
    }
    return false;
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
        if(it->second == projectile){
            this->projectiles.erase(it);
            break;
        }
    }
}

void GameWorld::removeEntities(){
    for(b2Body* body : this->entitiesToRemove){
        Entity* entity = (Entity*) body->GetUserData().pointer;
        if(typeid(*entity) == typeid(Rocket)){
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

bool GameWorld::allEntitiesAtRest(){
    for (b2Body* body = this->world->GetBodyList(); body != NULL; body = body->GetNext()) {
        if(body->GetType() == b2_dynamicBody){
            if(!body->GetLinearVelocity().Length() == 0){
                return false;
            }
        }
    }
    return true;
}

GameDynamic* GameWorld::getGameStatus(int id){
    std::vector<WormDTO> wormsDTO;
    for (auto& worm : this->worms) {
        Worm* wormData = (Worm*) worm.second->GetUserData().pointer;
        wormsDTO.push_back(wormData->getDTO());
    }

    std::vector<ExplosivesDTO> projectilesDTO;
    for (auto& projectile : this->projectiles) {
        Rocket* rocketData = (Rocket*) projectile.second->GetUserData().pointer;
        projectilesDTO.push_back(rocketData->getDTO());
    }
    GameDynamic* dynamicData = new GameDynamic(id, wormsDTO, projectilesDTO);
    return dynamicData;
}

GameWorld::~GameWorld() {
    //erase and delete worms
    for (auto& worm : this->worms) {
        this->world->DestroyBody(worm.second);
        delete (Worm*) worm.second->GetUserData().pointer;
    }
    // //erase and delete projectiles
    // for(b2Body* projectile : this->projectiles){
    //     this->world->DestroyBody(projectile);
    //     delete (Rocket*) projectile->GetUserData().pointer;
    // }
    //erase and delete the rest of the entities
    for (b2Body* body = this->world->GetBodyList(); body != NULL; body = body->GetNext()) {
        //deleting user data
        Entity* entity = (Entity*) body->GetUserData().pointer;
        this->world->DestroyBody(body);
        delete entity;
    }
    delete this->listener;
    delete this->world;
}