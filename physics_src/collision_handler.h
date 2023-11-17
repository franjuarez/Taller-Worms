#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include <unordered_map>
//include for runtime error
#include <stdexcept>
#include "entities/entity.h"

typedef void (Entity::*beginCollisionFunc)(Entity*, b2Contact*);
typedef void (Entity::*preSolveCollisionFunc)(Entity*, b2Contact*, const b2Manifold*);
typedef void (Entity::*postSolveCollisionFunc)(Entity*, b2Contact*, const b2ContactImpulse*);
typedef void (Entity::*endCollisionFunc)(Entity*, b2Contact*);

class CollisionHandler {
private:
    std::unordered_map<EntityType, beginCollisionFunc> beginCollisionMap;
    std::unordered_map<EntityType, preSolveCollisionFunc> preSolveCollisionMap;
    std::unordered_map<EntityType, postSolveCollisionFunc> postSolveCollisionMap;
    std::unordered_map<EntityType, endCollisionFunc> endCollisionMap;

public:
    CollisionHandler();
    
    void handleBeginCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact);

    void handlePreSolveCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact, const b2Manifold* oldManifold);

    void handlePostSolveCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact, const b2ContactImpulse* impulse);

    void handleEndCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact);
};

#endif
