#include "collision_handler.h"

CollisionHandler::CollisionHandler(){
    this->beginCollisionMap[std::string(typeid(Water).name())] = &Entity::beginCollisionWithWater;
    this->beginCollisionMap[std::string(typeid(Beam).name())] = &Entity::beginCollisionWithBeam;
    this->beginCollisionMap[std::string(typeid(Worm).name())] = &Entity::beginCollisionWithWorm;
    this->beginCollisionMap[std::string(typeid(Rocket).name())] = &Entity::beginCollisionWithRocket;

    this->preSolveCollisionMap[std::string(typeid(Beam).name())] = &Entity::preSolveCollisionWithBeam;
    this->preSolveCollisionMap[std::string(typeid(Worm).name())] = &Entity::preSolveCollisionWithWorm;

    this->postSolveCollisionMap[std::string(typeid(Beam).name())] = &Entity::postSolveCollisionWithBeam;
    this->postSolveCollisionMap[std::string(typeid(Worm).name())] = &Entity::postSolveCollisionWithWorm;

    this->endCollisionMap[std::string(typeid(Beam).name())] = &Entity::endCollisionWithBeam;
    this->endCollisionMap[std::string(typeid(Worm).name())] = &Entity::endCollisionWithWorm;
}

void CollisionHandler::handleBeginCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact) {
    std::string typeA = typeid(*bodyA).name();
    std::string typeB = typeid(*bodyB).name();
    if (this->beginCollisionMap.find(typeA) != this->beginCollisionMap.end()) {
        (bodyB->*beginCollisionMap[typeA])(bodyA, contact);
    }
}

void CollisionHandler::handlePreSolveCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact, const b2Manifold* oldManifold) {
    std::string typeA = typeid(*bodyA).name();
    std::string typeB = typeid(*bodyB).name();
    if (this->preSolveCollisionMap.find(typeA) != this->preSolveCollisionMap.end()) {
        (bodyB->*preSolveCollisionMap[typeA])(bodyA, contact, oldManifold);
    }
}

void CollisionHandler::handlePostSolveCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact, const b2ContactImpulse* impulse) {
    std::string typeA = typeid(*bodyA).name();
    std::string typeB = typeid(*bodyB).name();
    if (this->postSolveCollisionMap.find(typeA) != this->postSolveCollisionMap.end()) {
        (bodyB->*postSolveCollisionMap[typeA])(bodyA, contact, impulse);
    }
}

void CollisionHandler::handleEndCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact) {
    std::string typeA = typeid(*bodyA).name();
    std::string typeB = typeid(*bodyB).name();
    if (this->endCollisionMap.find(typeA) != this->endCollisionMap.end()) {
        (bodyB->*endCollisionMap[typeA])(bodyA, contact);
    }
}
