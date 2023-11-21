#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include <unordered_map>
#include <stdexcept>
#include "entities/entity.h"

typedef void (Entity::*beginCollisionFunc)(Entity*, b2Contact*);
typedef void (Entity::*preSolveCollisionFunc)(Entity*, b2Contact*, const b2Manifold*);
typedef void (Entity::*postSolveCollisionFunc)(Entity*, b2Contact*, const b2ContactImpulse*);
typedef void (Entity::*endCollisionFunc)(Entity*, b2Contact*);

class CollisionHandler {
private:
    beginCollisionFunc beginCollisionArr[EntityCount];
    preSolveCollisionFunc preSolveCollisionArr[EntityCount];
    postSolveCollisionFunc postSolveCollisionArr[EntityCount];
    endCollisionFunc endCollisionArr[EntityCount];

public:
    CollisionHandler();
    
    void handleBeginCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact);

    void handlePreSolveCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact, const b2Manifold* oldManifold);

    void handlePostSolveCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact, const b2ContactImpulse* impulse);

    void handleEndCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact);
};

#endif
