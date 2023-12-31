#include "game_world.h"

#define WORM_GROUP_INDEX -1
#define IMPOSSIBLE_POSITION Position(-999, -999)

GameWorld::GameWorld(std::shared_ptr<GameMap> gameMap) {
    this->world = new b2World(b2Vec2(CONFIG.getWorldGravityX(), CONFIG.getWorldGravityY()));
    this->listener = new Listener(this->world);
    this->world->SetContactListener(this->listener);
    this->lastProjectileId = 0;
    this->lastBoxId = 0;
    this->worldBegginningY = 0; //always 0
    this->worldBegginningX = INFINITY;
    this->worldEndX = -INFINITY;
    this->worldMaxY = -INFINITY;

    std::vector<BeamDTO> beams = gameMap->getBeams();
    for (BeamDTO& beam : beams) {
        float x = beam.getPosition().getX();
        float y = beam.getPosition().getY();
        bool large = beam.getBeamLength() == CONFIG.getBeamLargeLength() ? true : false;

        if(x < this->worldBegginningX){
            this->worldBegginningX = x;
        }
        if(x > worldEndX){
            worldEndX = x;
        }
        if(y > worldMaxY){
            worldMaxY = y;
        }

        createBeam(x, y, beam.getAngle(), large);
    }

    this->worldBegginningX -= 10;
    this->worldEndX += 10;
    this->worldMaxY += 10;

    std::unordered_map<int, WormDTO> worms = gameMap->getWorms();
    for (auto it = worms.begin(); it != worms.end(); it++) {
        float x = it->second.getPosition().getX();
        float y = it->second.getPosition().getY();
        int id = it->second.getId();
        int team = it->second.getTeam();
        int health = it->second.getHealth();
        std::vector<int> weapons = it->second.getWeapons();
        
        createWorm(x, y, id, team, health, weapons);
    }

    createWater();
}

void GameWorld::createWater(){
    b2BodyDef bd;
    bd.type = b2_staticBody;
    float worldHalf = (this->worldEndX + this->worldBegginningX) / 2.0f;
    float worldWidth = abs(this->worldEndX - this->worldBegginningX);
    bd.position.Set(worldHalf, 0);
    b2Body* body = this->world->CreateBody(&bd);
    b2FixtureDef fd;
    b2PolygonShape shape;
    shape.SetAsBox(worldWidth * 5, 0.1f);
    fd.shape = &shape;
    body->CreateFixture(&fd);

    Water* waterEntity = new Water(body, entitiesToRemove);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(waterEntity);
}

void GameWorld::createWorm(float startingX, float startingY, int id, int team, int health, std::vector<int> weapons){
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

    b2PolygonShape footSensorShape;
    footSensorShape.SetAsBox(WORM_WIDTH/2 - 0.01f , WORM_HEIGHT/4, b2Vec2(0, -WORM_HEIGHT/2), 0);
    b2FixtureDef footSensorFixture;
    footSensorFixture.shape = &footSensorShape;
    footSensorFixture.isSensor = true;
    b2Fixture* footSensor = body->CreateFixture(&footSensorFixture);

    Worm* wormEntity = new Worm(body, footSensor, entitiesToRemove, id, team, RIGHT, health, weapons); //Starts facing right
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
    float beamWidth = large ? CONFIG.getBeamLargeLength() : CONFIG.getBeamSmallLength();
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

    bool isWalkable = (abs(angle) > CONFIG.getBeamMaxWalkableAngle()) ? false : true;
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

b2Body* GameWorld::createProjectile(b2Body* worm, int weaponId, int direction, float width, float height, float restitution = 0.3f){
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    float deltaX = (direction == LEFT) ? - WORM_WIDTH/2 - width/2 - 0.05f : WORM_WIDTH/2 + width/2 + 0.05f;
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
    Worm* wormData = (Worm*) worm->GetUserData().pointer;
    wormData->reduceAmmo(weaponId);
    return body;
}

b2Body* GameWorld::createBazooka(b2Body* worm, int direction){
    int id = this->lastProjectileId;
    b2Body* body = createProjectile(worm, BAZOOKA, direction, BAZOOKA_WIDTH, BAZOOKA_HEIGHT);
    Bazooka* bazookaEntity = new Bazooka(body, entitiesToRemove, entitiesToAdd, id,  CONFIG.getBazookaDamage(), CONFIG.getBazookaRadius());
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(bazookaEntity);

    return body;
}

bool GameWorld::wormLaunchBazooka(int id, float angle, int direction, float power){
    checkWormExists(id);
    b2Body* worm = this->worms[id];
    Worm* wormData = (Worm*) worm->GetUserData().pointer;
    if(!wormData->hasAmmo(BAZOOKA)){
        return false; 
    }
    b2Body* bazooka = createBazooka(worm, direction);
    b2Vec2 vel = calculatVelocityOfProjectile(CONFIG.getProjectileMaxSpeed(), angle, direction, power);
    bazooka->SetLinearVelocity(vel);
    wormData->changeDirection(direction);
    return true;
}

b2Body* GameWorld::createMortar(b2Body* worm, int direction){
    int id = this->lastProjectileId;
    b2Body* body = createProjectile(worm, MORTAR, direction, MORTAR_WIDTH, MORTAR_HEIGHT);

    Mortar* mortarEntity = new Mortar(body, entitiesToRemove, entitiesToAdd, id, CONFIG.getMortarDamage(), CONFIG.getMortarRadius());
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(mortarEntity);

    return body;
}

bool GameWorld::wormLaunchMortar(int id, float angle, int direction, float power){
    checkWormExists(id);
    b2Body* worm = this->worms[id];
    Worm* wormData = (Worm*) worm->GetUserData().pointer;
    if(!wormData->hasAmmo(MORTAR)){
        return false; 
    }
    b2Body* bazooka = createMortar(worm, direction);
    b2Vec2 vel = calculatVelocityOfProjectile(CONFIG.getProjectileMaxSpeed(), angle, direction, power);
    bazooka->SetLinearVelocity(vel);
    wormData->changeDirection(direction);
    return true;
}

b2Body* GameWorld::createGreenGrenade(b2Body* worm, int direction, int explosionTimer){
    int id = this->lastProjectileId;
    b2Body* body = createProjectile(worm, GREEN_GRENADE, direction, GREEN_GRENADE_WIDTH, GREEN_GRENADE_WIDTH);

    GreenGrenade* greenGrenadeEntity = new GreenGrenade(body, entitiesToRemove, entitiesToAdd, id, CONFIG.getGreenGrenadeDamage(),CONFIG.getGreenGrenadeRadius(), explosionTimer);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(greenGrenadeEntity);

    return body;
}

bool GameWorld::wormThrowGreenGrenade(int id, float angle, int direction, float power, int explosionTimer){
    checkWormExists(id);
    b2Body* worm = this->worms[id];
    Worm* wormData = (Worm*) worm->GetUserData().pointer;
    if(!wormData->hasAmmo(GREEN_GRENADE)){
        return false; 
    }
    b2Body* granade = createGreenGrenade(worm, direction, explosionTimer);
    b2Vec2 grenadeVel = calculatVelocityOfProjectile(CONFIG.getProjectileMaxSpeed(), angle, direction, power);
    granade->SetLinearVelocity(grenadeVel);
    wormData->changeDirection(direction);
    return true;
}

b2Body* GameWorld::createRedGrenade(b2Body* worm, int direction, int explosionTimer){
    int id = this->lastProjectileId;
    b2Body* body = createProjectile(worm, RED_GRENADE, direction, RED_GRENADE_WIDTH, RED_GRENADE_HEIGHT);

    RedGrenade* redGrenadeEntity = new RedGrenade(body, entitiesToRemove, entitiesToAdd, id, CONFIG.getRedGrenadeDamage(), CONFIG.getRedGrenadeRadius(), explosionTimer);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(redGrenadeEntity);

    return body;
}

bool GameWorld::wormThrowRedGrenade(int id, float angle, int direction, float power, int explosionTimer){
    checkWormExists(id);
    b2Body* worm = this->worms[id];
    Worm* wormData = (Worm*) worm->GetUserData().pointer;
    if(!wormData->hasAmmo(RED_GRENADE)){
        return false; 
    }
    b2Body* granade = createRedGrenade(worm, direction, explosionTimer);
    b2Vec2 grenadeVel = calculatVelocityOfProjectile(CONFIG.getProjectileMaxSpeed(), angle, direction, power);
    granade->SetLinearVelocity(grenadeVel);
    wormData->changeDirection(direction);
    return true;
}

b2Body* GameWorld::createBanana(b2Body* worm, int direction, int explosionTimer){
    int id = this->lastProjectileId;
    b2Body* body = createProjectile(worm, BANANA, direction, BANANA_WIDTH, BANANA_HEIGHT, CONFIG.getBananaBounciness());

    Banana* bananaEntity = new Banana(body, entitiesToRemove, entitiesToAdd, id, CONFIG.getBananaDamage(), CONFIG.getBananaRadius(), explosionTimer);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(bananaEntity);

    return body;
}

bool GameWorld::wormThrowBanana(int id, float angle, int direction, float power, int explosionTimer){
    checkWormExists(id);
    b2Body* worm = this->worms[id];
    Worm* wormData = (Worm*) worm->GetUserData().pointer;
    if(!wormData->hasAmmo(BANANA)){
        return false; 
    }
    b2Body* banana = createBanana(worm, direction, explosionTimer);
    b2Vec2 bananaVel = calculatVelocityOfProjectile(CONFIG.getProjectileMaxSpeed(), angle, direction, power);
    banana->SetLinearVelocity(bananaVel);
    wormData->changeDirection(direction);
    return true;
}

b2Body* GameWorld::createDynamite(b2Body* worm, int direction, int explosionTimer){
    int id = this->lastProjectileId;
    b2Body* body = createProjectile(worm, DYNAMITE, direction, DYNAMITE_WIDTH, DYNAMITE_HEIGHT, 0.0f);

    body->SetFixedRotation(true);
    Dynamite* dynamiteEntity = new Dynamite(body, entitiesToRemove, entitiesToAdd, id, CONFIG.getDynamiteDamage(), CONFIG.getDynamiteRadius(), explosionTimer);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(dynamiteEntity);

    return body;
}

bool GameWorld::wormDropDynamite(int id, int direction, int explosionTimer){
    checkWormExists(id);
    b2Body* worm = this->worms[id];
    Worm* wormData = (Worm*) worm->GetUserData().pointer;
    if(!wormData->hasAmmo(DYNAMITE)){
        return false; 
    }
    b2Body* dynamite = createDynamite(worm, direction, explosionTimer);
    dynamite->SetLinearVelocity(b2Vec2(0, -1)); //So it falls
    return true;
}

b2Body* GameWorld::createHolyGrenade(b2Body* worm, int direction, int explosionTimer){
    int id = this->lastProjectileId;
    b2Body* body = createProjectile(worm, HOLY_GRENADE, direction, HOLY_GRENADE_WIDTH, HOLY_GRENADE_HEIGHT);

    HolyGrenade* holyGrenadeEntity = new HolyGrenade(body, entitiesToRemove, entitiesToAdd, id, CONFIG.getHolyGrenadeDamage(), CONFIG.getHolyGrenadeRadius(), explosionTimer);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(holyGrenadeEntity);

    return body;
}

b2Body* GameWorld::createAirAttackMissile(float startingX, float xDest, float velX){
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(startingX, this->worldMaxY + AIR_ATTACK_MISSILE_HEIGHT);
    b2Body* body = this->world->CreateBody(&bd);
    body->SetBullet(true);
    b2FixtureDef fd;
    b2PolygonShape shape;
    shape.SetAsBox(AIR_ATTACK_MISSILE_WIDTH/2, AIR_ATTACK_MISSILE_HEIGHT/2);
    fd.shape = &shape;
    fd.density = 1.0f;
    body->CreateFixture(&fd);

    body->SetLinearVelocity(b2Vec2(velX, -1));

    int id = this->lastProjectileId;
    this->projectiles[this->lastProjectileId] = body;
    this->lastProjectileId++;
    
    AirAttackMissile* airAttackMissileEntity = new AirAttackMissile(body, entitiesToRemove, entitiesToAdd, id, CONFIG.getAirAttackMissileDamage(), CONFIG.getAirAttackMissileRadius());
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(airAttackMissileEntity);

    return body;
}

bool GameWorld::wormCallAirAttack(int id, float xDest, float yDest){
    checkWormExists(id);
    b2Body* worm = this->worms[id];
    Worm* wormData = (Worm*) worm->GetUserData().pointer;

    if(!wormData->hasAmmo(AIR_ATTACK)){
        return false; 
    }
    float currentX = xDest - 5 - AIR_ATTACK_MISSILE_WIDTH - (AIR_ATTACK_MISSILE_AMOUNT/2 * AIR_ATTACK_MISSILE_WIDTH*2);
    float velX = (xDest - currentX) / 2;
    for(int i = 0; i < AIR_ATTACK_MISSILE_AMOUNT; i++){
        b2Body* missile = createAirAttackMissile(currentX, xDest, velX);
        currentX += AIR_ATTACK_MISSILE_WIDTH*2;
        velX += AIR_ATTACK_MISSILE_WIDTH*2;
    }
    wormData->reduceAmmo(AIR_ATTACK);
    return true;
}

bool GameWorld::wormThrowHolyGrenade(int id, float angle, int direction, float power, int explosionTimer){
    checkWormExists(id);
    b2Body* worm = this->worms[id];
    Worm* wormData = (Worm*) worm->GetUserData().pointer;

    if(!wormData->hasAmmo(HOLY_GRENADE)){
        return false; 
    }
    b2Body* holyGrenade = createHolyGrenade(worm, direction, explosionTimer);
    b2Vec2 grenadeVel = calculatVelocityOfProjectile(CONFIG.getProjectileMaxSpeed(), angle, direction, power);
    holyGrenade->SetLinearVelocity(grenadeVel);
    wormData->changeDirection(direction);
    return true;
}

void GameWorld::wormHitWithBat(int id, int direction){
    checkWormExists(id);
    b2Body* worm = this->worms[id];
    Worm* wormData = (Worm*) worm->GetUserData().pointer;
    if(!wormData->hasAmmo(BAT)){
        return;
    }
    wormData->hitWithBat(direction);
}

bool GameWorld::checkValidTpPosition(float x, float y){
    if(y < 0){
        return false;
    }
    b2AABB aabb;
    aabb.lowerBound = b2Vec2(x - WORM_WIDTH/2, y - WORM_HEIGHT/2);
    aabb.upperBound = b2Vec2(x + WORM_WIDTH/2, y + WORM_HEIGHT/2);
    TeleportQueryCallback callback;
    this->world->QueryAABB(&callback, aabb);
    return callback.validTeleport;
}

bool GameWorld::teleportWorm(int id, float x, float y){
    checkWormExists(id);
    Worm* wormData = (Worm*) this->worms[id]->GetUserData().pointer;
    if(!wormData->hasAmmo(REMOTE_OPERATED)){
        return false;
    }
    if(checkValidTpPosition(x, y)){
        b2Body* worm = this->worms[id];
        worm->SetTransform(b2Vec2(x, y), 0);
        worm->SetLinearVelocity(b2Vec2(0, -0.01f)); //So it falls
        return true;
    }
    return false;
}

float randomNumberGenerator(float min, float max){
    return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
}

Position GameWorld::calculateValidSupplyBoxPosition(){
    int maxAttempts = 100;
    int attempts = 0;
    while(attempts < maxAttempts){
        float x = randomNumberGenerator(this->worldBegginningX, this->worldEndX);
        SupplyQueryCallback callback;
        this->world->RayCast(&callback, b2Vec2(x, this->worldMaxY), b2Vec2(x, 0));
        if(callback.lastIntersectedType != EntityBeam){
            attempts++;
            continue;
        }
        b2Body* foundBeam = callback.beam;
        bool found = true;
        float offset = 0.3f;
        float step = 0.1f;
        float currX = x - SUPPLY_BOX_WIDTH/2;
        for(float i = -offset; i <= SUPPLY_BOX_WIDTH + offset; i+=step){
            float test = currX + i;
            this->world->RayCast(&callback, b2Vec2(test, this->worldMaxY), b2Vec2(test, 0));
            if(callback.lastIntersectedType != EntityBeam || callback.beam != foundBeam){
                found = false;
                break;
            }
        }
        if(!found){
            attempts++;
            continue;
        }
        b2Vec2 beamPos = foundBeam->GetPosition();
        float y = beamPos.y * 2;
        return Position(x, y);
    }
    return IMPOSSIBLE_POSITION;
}

void GameWorld::dropSupplyBox(int type){
    Position pos = calculateValidSupplyBoxPosition();
    if(pos.getX() == IMPOSSIBLE_POSITION.getX() && pos.getY() == IMPOSSIBLE_POSITION.getY()){
        return;
    }
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(pos.getX(), pos.getY());
    b2Body* body = this->world->CreateBody(&bd);
    b2FixtureDef fd;
    b2PolygonShape shape;
    shape.SetAsBox(SUPPLY_BOX_WIDTH/2, SUPPLY_BOX_HEIGHT/2);
    fd.shape = &shape;
    fd.density = 1.0f;
    body->CreateFixture(&fd);
    body->SetGravityScale(0.0f);//So it falls slower
    body->SetLinearVelocity(b2Vec2(0, -2.5f)); //So it starts falling with velocity

    if(type == TRAP_SUPPLY){
        TrapSupplyBox* supplyBoxEntity = new TrapSupplyBox(body, entitiesToRemove, this->lastBoxId, type);
        body->GetUserData().pointer = reinterpret_cast<uintptr_t>(supplyBoxEntity);
    } else{
        ProvitionsSupplyBox* supplyBoxEntity = new ProvitionsSupplyBox(body, entitiesToRemove, this->lastBoxId, type);
        body->GetUserData().pointer = reinterpret_cast<uintptr_t>(supplyBoxEntity);
    }
    this->boxes[this->lastBoxId] = body;
    this->lastBoxId++;
}

void GameWorld::addHealthToWorm(int id){
    checkWormExists(id);
    b2Body* worm = this->worms[id];
    Worm* wormData = (Worm*) worm->GetUserData().pointer;
    wormData->addHealth(CONFIG.getWormAdditionalHealth());
}

void GameWorld::wormGetAllWeapons(int id){
    checkWormExists(id);
    b2Body* worm = this->worms[id];
    Worm* wormData = (Worm*) worm->GetUserData().pointer;
    wormData->getAllWeapons();
}

void GameWorld::toggleInvincible(){
    for(auto it = this->worms.begin(); it != this->worms.end(); ++it){
        Worm* wormData = (Worm*) it->second->GetUserData().pointer;
        wormData->toggleInvincible();
    }
}

void GameWorld::removeProjectileFromMap(b2Body* projectile){
    Projectile* projectileData = (Projectile*) projectile->GetUserData().pointer;
    int id = projectileData->getId();
    auto it = this->projectiles.find(id);
    if(it == this->projectiles.end()){
        throw std::runtime_error("Projectile does not exist");
    }
    this->projectiles.erase(id);
}

void GameWorld::removeBoxFromMap(b2Body* box){
    SupplyBox* boxData = (SupplyBox*) box->GetUserData().pointer;
    int id = boxData->getId();
    auto it = this->boxes.find(id);
    if(it == this->boxes.end()){
        throw std::runtime_error("Box does not exist");
    }
    this->boxes.erase(id);
}

void GameWorld::removeWormFromMap(b2Body* worm){
    Worm* wormData = (Worm*) worm->GetUserData().pointer;
    int id = wormData->getId();
    auto it = this->worms.find(id);
    if(it == this->worms.end()){
        throw std::runtime_error("Worm does not exist");
    }
    this->worms.erase(id);
}

void GameWorld::removeEntities(){
    std::unordered_set<b2Body*> deadWorms;
    for(b2Body* body : this->entitiesToRemove){
        Entity* entity = (Entity*) body->GetUserData().pointer;
        EntityType entityType = entity->getEntityType();
        if(entityType == EntityInstantProjectile || entityType == EntityDelayedProjectile){
            removeProjectileFromMap(body);
        }  else if (entityType == EntitySupplyBox){
            removeBoxFromMap(body);
        } else if(entityType == EntityWorm){
            Worm* wormData = (Worm*) body->GetUserData().pointer;
            if(body->GetLinearVelocity().Length() != 0){
                deadWorms.insert(body);
                continue;
            }
            removeWormFromMap(body);
        }
        this->world->DestroyBody(body);
        delete entity;
    }
    this->entitiesToRemove.clear();
    for(b2Body* body : deadWorms){
        entitiesToRemove.insert(body);
    }
}

bool GameWorld::allEntitiesAtRest(){
    for (b2Body* body = this->world->GetBodyList(); body != NULL; body = body->GetNext()) {
        if(body->GetType() == b2_dynamicBody){
            EntityType entityType = ((Entity*) body->GetUserData().pointer)->getEntityType();
            float velModule = body->GetLinearVelocity().Length();
            if(velModule != 0 || entityType == EntityDelayedProjectile){
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
    std::unordered_map<int, WormDTO> wormsDTO;
    for(auto& worm: this->worms){
        Worm* wormData = (Worm*) worm.second->GetUserData().pointer;
        wormsDTO.emplace(worm.first, wormData->getDTO());
        // std::cout << "Worm " << worm.first << " health: " << wormData->getHealth() << std::endl;
    }

    std::unordered_map<int, ExplosivesDTO> projectilesDTO;
    for (auto& projectile : this->projectiles) {
        Projectile* projectileData = (Projectile*) projectile.second->GetUserData().pointer;
        projectilesDTO.emplace(projectile.first, projectileData->getDTO());
    }

    std::unordered_map<int, SupplyBoxDTO> boxesDTO;
    for (auto& box : this->boxes) {
        SupplyBox* boxData = (SupplyBox*) box.second->GetUserData().pointer;
        boxesDTO.emplace(box.first, boxData->getDTO());
    }

    return new GameDynamic(id, wormsDTO, projectilesDTO, boxesDTO);
}

GameWorld::~GameWorld() {
    for (auto& worm : this->worms) {
        this->world->DestroyBody(worm.second);
        delete (Worm*) worm.second->GetUserData().pointer;
    }
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