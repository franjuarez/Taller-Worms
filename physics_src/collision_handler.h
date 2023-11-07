#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include <unordered_map>

#include "../entities/Entity.h"
#include "../entities/Beam.h"
#include "../entities/Rocket.h"
#include "../entities/Worm.h"

typedef void (Entity::*beginCollisionFunc)(Entity*, std::set<b2Body*>&);
typedef void (Entity::*preSolveCollisionFunc)(Entity*, b2Contact*);
typedef void (Entity::*postSolveCollisionFunc)(Entity*, b2Contact*);
typedef void (Entity::*endCollisionFunc)(Entity*, b2Contact*);

class CollisionHandler {
private:
    std::unordered_map<std::string, beginCollisionFunc> beginCollisionMap;
    std::unordered_map<std::string, preSolveCollisionFunc> preSolveCollisionMap;
    std::unordered_map<std::string, postSolveCollisionFunc> postSolveCollisionMap;
    std::unordered_map<std::string, endCollisionFunc> endCollisionMap;

public:
    CollisionHandler();
    
    void handleBeginCollision(Entity* bodyA, Entity* bodyB, std::set<b2Body*>& entitiesToRemove);

    void handlePreSolveCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact);

    void handlePostSolveCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact);

    void handleEndCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact);
};

#endif
