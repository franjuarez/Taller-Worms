#include "collision_handler.h"
#include <iostream>
CollisionHandler::CollisionHandler(){
    this->beginCollisionArr[EntityWorm] = &Entity::beginCollisionWithWorm;
    this->beginCollisionArr[EntityBeam] = &Entity::beginCollisionWithBeam;
    this->beginCollisionArr[EntityWater] = &Entity::beginCollisionWithWater;
    this->beginCollisionArr[EntityInstantProjectile] = &Entity::beginCollisionWithProjectile;
    this->beginCollisionArr[EntityDelayedProjectile] = &Entity::beginCollisionWithProjectile;

    this->preSolveCollisionArr[EntityWorm] = &Entity::preSolveCollisionWithWorm;
    this->preSolveCollisionArr[EntityBeam] = &Entity::preSolveCollisionWithBeam;
    this->preSolveCollisionArr[EntityWater] = nullptr;
    this->preSolveCollisionArr[EntityInstantProjectile] = nullptr;
    this->preSolveCollisionArr[EntityDelayedProjectile] = nullptr;

    this->postSolveCollisionArr[EntityWorm] = &Entity::postSolveCollisionWithWorm;
    this->postSolveCollisionArr[EntityBeam] = &Entity::postSolveCollisionWithBeam;
    this->postSolveCollisionArr[EntityWater] = nullptr;
    this->postSolveCollisionArr[EntityInstantProjectile] = nullptr;
    this->postSolveCollisionArr[EntityDelayedProjectile] = nullptr;

    this->endCollisionArr[EntityWorm] = &Entity::endCollisionWithWorm;
    this->endCollisionArr[EntityBeam] = &Entity::endCollisionWithBeam;
    this->endCollisionArr[EntityWater] = nullptr;
    this->endCollisionArr[EntityInstantProjectile] = nullptr;
    this->endCollisionArr[EntityDelayedProjectile] = nullptr;
}

void CollisionHandler::handleBeginCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact) {
    EntityType typeA = bodyA->getEntityType();
    EntityType typeB = bodyB->getEntityType();

    if (typeA >= EntityCount || typeB >= EntityCount) {
        throw std::runtime_error("Colision no manejada");
    }
    if (this->beginCollisionArr[typeA] != nullptr) {
        (bodyB->*beginCollisionArr[typeA])(bodyA, contact);
    }
}

void CollisionHandler::handlePreSolveCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact, const b2Manifold* oldManifold) {
    EntityType typeA = bodyA->getEntityType();
    EntityType typeB = bodyB->getEntityType();

    if (typeA >= EntityCount || typeB >= EntityCount) {
        throw std::runtime_error("Colision no manejada");
    }
    if (this->preSolveCollisionArr[typeA] != nullptr) {
        (bodyB->*preSolveCollisionArr[typeA])(bodyA, contact, oldManifold);
    }
}

void CollisionHandler::handlePostSolveCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact, const b2ContactImpulse* impulse) {
    EntityType typeA = bodyA->getEntityType();
    EntityType typeB = bodyB->getEntityType();

    if (typeA >= EntityCount || typeB >= EntityCount) {
        throw std::runtime_error("Colision no manejada");
    }
    if(this->postSolveCollisionArr[typeA] != nullptr){
        (bodyB->*postSolveCollisionArr[typeA])(bodyA, contact, impulse);
    }
}

void CollisionHandler::handleEndCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact) {
    EntityType typeA = bodyA->getEntityType();
    EntityType typeB = bodyB->getEntityType();

    if (typeA >= EntityCount || typeB >= EntityCount) {
        throw std::runtime_error("Colision no manejada");
    }
    if(this->endCollisionArr[typeA] != nullptr){
        (bodyB->*endCollisionArr[typeA])(bodyA, contact);
    }
}
