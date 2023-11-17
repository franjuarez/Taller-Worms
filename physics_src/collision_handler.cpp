#include "collision_handler.h"
#include <iostream>

CollisionHandler::CollisionHandler(){
    this->beginCollisionMap[EntityWorm] = &Entity::beginCollisionWithWorm;
    this->beginCollisionMap[EntityBeam] = &Entity::beginCollisionWithBeam;
    this->beginCollisionMap[EntityWater] = &Entity::beginCollisionWithWater;
    this->beginCollisionMap[EntityDelayedProjectile] = &Entity::beginCollisionWithProjectile;
    this->beginCollisionMap[EntityInstantProjectile] = &Entity::beginCollisionWithProjectile;

    this->preSolveCollisionMap[EntityWorm] = &Entity::preSolveCollisionWithWorm;
    this->preSolveCollisionMap[EntityBeam] = &Entity::preSolveCollisionWithBeam;

    this->postSolveCollisionMap[EntityWorm] = &Entity::postSolveCollisionWithWorm;
    this->postSolveCollisionMap[EntityBeam] = &Entity::postSolveCollisionWithBeam;

    this->endCollisionMap[EntityBeam] = &Entity::endCollisionWithBeam;
    this->endCollisionMap[EntityWorm] = &Entity::endCollisionWithWorm;
}

void CollisionHandler::handleBeginCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact) {
    EntityType typeA = bodyA->getEntityType();
    EntityType typeB = bodyB->getEntityType();

    if (this->beginCollisionMap.find(typeA) != this->beginCollisionMap.end()) {
        (bodyB->*beginCollisionMap[typeA])(bodyA, contact);
    } else{
        throw std::runtime_error("Colision BEGIN no manejada");
    }
}

void CollisionHandler::handlePreSolveCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact, const b2Manifold* oldManifold) {
    EntityType typeA = bodyA->getEntityType();
    EntityType typeB = bodyB->getEntityType();
    if (this->preSolveCollisionMap.find(typeA) != this->preSolveCollisionMap.end()) {
        (bodyB->*preSolveCollisionMap[typeA])(bodyA, contact, oldManifold);
    }
}

void CollisionHandler::handlePostSolveCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact, const b2ContactImpulse* impulse) {
    EntityType typeA = bodyA->getEntityType();
    EntityType typeB = bodyB->getEntityType();
    if (this->postSolveCollisionMap.find(typeA) != this->postSolveCollisionMap.end()) {
        (bodyB->*postSolveCollisionMap[typeA])(bodyA, contact, impulse);
    }
}

void CollisionHandler::handleEndCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact) {
    EntityType typeA = bodyA->getEntityType();
    EntityType typeB = bodyB->getEntityType();
    if (this->endCollisionMap.find(typeA) != this->endCollisionMap.end()) {
        (bodyB->*endCollisionMap[typeA])(bodyA, contact);
    }
}
