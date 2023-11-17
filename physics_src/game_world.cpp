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
    fd.filter.groupIndex = WORM_GROUP_INDEX; //This way it doesn't collide with other worms
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

void GameWorld::checkWormExists(int id){
    if(this->worms.find(id) == this->worms.end()){
        throw std::runtime_error("Worm does not exist");
    }
    Worm* worm = (Worm*) this->worms[id]->GetUserData().pointer;
    if(worm->isDead()){
        throw std::runtime_error("Worm is dead");
    }
}

b2Body* GameWorld::createProjectile(b2Body* worm, int direction, float width, float height, float restitution = 0.0f){
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    float deltaX = (direction == LEFT) ? - WORM_WIDTH/2 - width/2 - 0.1f : WORM_WIDTH/2 + width/2 + 0.1f;
    float posX = worm->GetPosition().x + deltaX;
    float posY = worm->GetPosition().y;
    bd.position.Set(posX, posY);
    b2Body* body = this->world->CreateBody(&bd);
    body->SetBullet(true);
    b2FixtureDef fd;
    b2PolygonShape shape;
    shape.SetAsBox(width/2, height/2);
    fd.shape = &shape;
    fd.density = 1.0f;
    fd.restitution = restitution;
    body->CreateFixture(&fd);

    this->projectiles[this->lastProjectileId] = body;
    this->lastProjectileId++;
    return body;
}

b2Body* GameWorld::createBazooka(b2Body* worm, int direction){
    int id = this->lastProjectileId;
    b2Body* body = createProjectile(worm, direction, BAZOOKA_WIDTH, BAZOOKA_HEIGHT);
    Bazooka* bazookaEntity = new Bazooka(body, entitiesToRemove, entitiesToAdd, id,  BAZOOKA_DAMAGE, BAZOOKA_BLAST_RADIOUS);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(bazookaEntity);

    return body;
}

void GameWorld::wormLaunchBazooka(int id, float angle, int direction, float power){
    checkWormExists(id);
    b2Body* worm = this->worms[id];
    b2Body* bazooka = createBazooka(worm, direction);
    b2Vec2 vel = calculatVelocityOfProjectile(PROJECTILE_MAX_SPEED, angle, direction, power);
    bazooka->SetLinearVelocity(vel);
}

b2Body* GameWorld::createMortar(b2Body* worm, int direction){
    int id = this->lastProjectileId;
    b2Body* body = createProjectile(worm, direction, MORTAR_WIDTH, MORTAR_HEIGHT);

    Mortar* mortarEntity = new Mortar(body, entitiesToRemove, entitiesToAdd, id, MORTAR_DAMAGE, MORTAR_BLAST_RADIOUS);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(mortarEntity);

    return body;
}

void GameWorld::wormLaunchMortar(int id, float angle, int direction, float power){
    checkWormExists(id);
    b2Body* worm = this->worms[id];
    b2Body* bazooka = createMortar(worm, direction);
    b2Vec2 vel = calculatVelocityOfProjectile(PROJECTILE_MAX_SPEED, angle, direction, power);
    bazooka->SetLinearVelocity(vel);
}

b2Body* GameWorld::createGreenGrenade(b2Body* worm, int direction, float explosionTimer){
    int id = this->lastProjectileId;
    b2Body* body = createProjectile(worm, direction, GREEN_GRENADE_WIDTH, GREEN_GRENADE_WIDTH);

    GreenGrenade* greenGrenadeEntity = new GreenGrenade(body, entitiesToRemove, entitiesToAdd, id, GREEN_GRENADE_DAMAGE, GREEN_GRENADE_BLAST_RADIOUS, explosionTimer);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(greenGrenadeEntity);

    return body;
}

void GameWorld::wormThrowGreenGrenade(int id, float angle, int direction, float power, float explosionTimer){
    checkWormExists(id);
    b2Body* worm = this->worms[id];
    b2Body* granade = createGreenGrenade(worm, direction, explosionTimer);
    b2Vec2 grenadeVel = calculatVelocityOfProjectile(PROJECTILE_MAX_SPEED, angle, direction, power);
    granade->SetLinearVelocity(grenadeVel);
}

b2Body* GameWorld::createRedGrenade(b2Body* worm, int direction, float explosionTimer){
    int id = this->lastProjectileId;
    b2Body* body = createProjectile(worm, direction, GREEN_GRENADE_WIDTH, GREEN_GRENADE_WIDTH);

    RedGrenade* redGrenadeEntity = new RedGrenade(body, entitiesToRemove, entitiesToAdd, id, RED_GRENADE_DAMAGE, RED_GRENADE_BLAST_RADIOUS, explosionTimer);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(redGrenadeEntity);

    return body;
}

void GameWorld::wormThrowRedGrenade(int id, float angle, int direction, float power, float explosionTimer){
    checkWormExists(id);
    b2Body* worm = this->worms[id];
    b2Body* granade = createRedGrenade(worm, direction, explosionTimer);
    b2Vec2 grenadeVel = calculatVelocityOfProjectile(PROJECTILE_MAX_SPEED, angle, direction, power);
    granade->SetLinearVelocity(grenadeVel);
}

b2Body* GameWorld::createBanana(b2Body* worm, int direction, float explosionTimer){
    int id = this->lastProjectileId;
    b2Body* body = createProjectile(worm, direction, GREEN_GRENADE_WIDTH, GREEN_GRENADE_WIDTH, BANANA_RESTITUTION);

    Banana* redGrenadeEntity = new Banana(body, entitiesToRemove, entitiesToAdd, id, RED_GRENADE_DAMAGE, RED_GRENADE_BLAST_RADIOUS, explosionTimer);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(redGrenadeEntity);

    return body;
}

void GameWorld::wormThrowBanana(int id, float angle, int direction, float power, float explosionTimer){
    checkWormExists(id);
    b2Body* worm = this->worms[id];
    b2Body* banana = createBanana(worm, direction, explosionTimer);
    b2Vec2 bananaVel = calculatVelocityOfProjectile(PROJECTILE_MAX_SPEED, angle, direction, power);
    banana->SetLinearVelocity(bananaVel);
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
        worm->SetLinearVelocity(b2Vec2(0, -0.01f));
        return true;
    }
    return false;
}

void GameWorld::removeWorm(b2Body* worm){
    bool erased = false;
    for(auto it = this->worms.begin(); it != this->worms.end(); ++it){
        if(it->second == worm){
            this->worms.erase(it);
            erased = true;
            break;
        }
    }
    if(!erased){
        throw std::invalid_argument("Worm not found");
    }
}

void GameWorld::removeProjectile(b2Body* projectile){
    bool erased = false;
    for(auto it = this->projectiles.begin(); it != this->projectiles.end(); ++it){
        if(it->second == projectile){
            this->projectiles.erase(it);
            erased = true;
            break;
        }
    }
    if(!erased){
        throw std::invalid_argument("Projectile not found");
    }
}

void GameWorld::removeEntities(){
    for(b2Body* body : this->entitiesToRemove){
        Entity* entity = (Entity*) body->GetUserData().pointer;
        EntityType entityType = entity->getEntityType();
        std::cout << "Removing entity of type " << entityType << std::endl;
        if(entityType == EntityInstantProjectile || entityType == EntityDelayedProjectile){
            removeProjectile(body);
        }
        this->world->DestroyBody(body);
        delete entity;
    }
    this->entitiesToRemove.clear();
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

void GameWorld::updateDelayedProjectiles(float deltaTime){
    for(auto it = this->projectiles.begin(); it != this->projectiles.end(); ++it){
        b2Body* projectile = it->second;
        Entity* entity = (Entity*) projectile->GetUserData().pointer;
        EntityType projectileType = entity->getEntityType();
        if(projectileType == EntityDelayedProjectile){
            DelayedProjectile* delayedProjectile = (DelayedProjectile*) entity;
            delayedProjectile->update(deltaTime);
        }
    }
}

void GameWorld::addFragments(){
    for(createEntity& fragment : this->entitiesToAdd){
        b2Body* fragmentBody = fragment(this->lastProjectileId);
        this->projectiles[this->lastProjectileId] = fragmentBody;
        this->lastProjectileId++;
    }
    this->entitiesToAdd.clear();
}

void GameWorld::update() {
    this->world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
    updateDelayedProjectiles(TIME_STEP);
    addFragments();
    removeEntities();
}

GameDynamic* GameWorld::getGameStatus(int id){
    std::vector<WormDTO> wormsDTO;
    for (auto& worm : this->worms) {
        Worm* wormData = (Worm*) worm.second->GetUserData().pointer;
        wormsDTO.push_back(wormData->getDTO());
    }

    std::unordered_map<int, ExplosivesDTO> projectilesDTO;
    for (auto& projectile : this->projectiles) {
        Projectile* projectileData = (Projectile*) projectile.second->GetUserData().pointer;
        projectilesDTO.emplace(projectile.first, projectileData->getDTO());
    }
    GameDynamic* dynamicData = new GameDynamic(id, wormsDTO, projectilesDTO);
    return dynamicData;
}

GameWorld::~GameWorld() {
    for (auto& worm : this->worms) {
        this->world->DestroyBody(worm.second);
        delete (Worm*) worm.second->GetUserData().pointer;
    }
    //This shouldnt be necessary but just in case
    for (auto& projectile : this->projectiles) {
        this->world->DestroyBody(projectile.second);
        delete (Projectile*) projectile.second->GetUserData().pointer;
    }

    for (b2Body* body = this->world->GetBodyList(); body != NULL; body = body->GetNext()) {
        Entity* entity = (Entity*) body->GetUserData().pointer;
        this->world->DestroyBody(body);
        delete entity;
    }
    delete this->listener;
    delete this->world;
}