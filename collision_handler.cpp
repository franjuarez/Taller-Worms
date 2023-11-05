#include "collision_handler.h"

CollisionHandler::CollisionHandler(){
    this->beginCollisionMap[std::string(typeid(Beam).name())] = &Entity::beginCollisionWithBeam;
    this->beginCollisionMap[std::string(typeid(Worm).name())] = &Entity::beginCollisionWithWorm;
    this->beginCollisionMap[std::string(typeid(Rocket).name())] = &Entity::beginCollisionWithRocket;

    this->preSolveCollisionMap[std::string(typeid(Beam).name())] = &Entity::preSolveCollisionWithBeam;
    this->preSolveCollisionMap[std::string(typeid(Worm).name())] = &Entity::preSolveCollisionWithWorm;
    this->preSolveCollisionMap[std::string(typeid(Rocket).name())] = &Entity::preSolveCollisionWithRocket;

    this->postSolveCollisionMap[std::string(typeid(Beam).name())] = &Entity::postSolveCollisionWithBeam;
    this->postSolveCollisionMap[std::string(typeid(Worm).name())] = &Entity::postSolveCollisionWithWorm;
    this->postSolveCollisionMap[std::string(typeid(Rocket).name())] = &Entity::postSolveCollisionWithRocket;

    this->endCollisionMap[std::string(typeid(Beam).name())] = &Entity::endCollisionWithBeam;
    this->endCollisionMap[std::string(typeid(Worm).name())] = &Entity::endCollisionWithWorm;
    this->endCollisionMap[std::string(typeid(Rocket).name())] = &Entity::endCollisionWithRocket;
}

void CollisionHandler::handleBeginCollision(Entity* bodyA, Entity* bodyB, std::set<b2Body*>& entitiesToRemove) {
    std::string typeA = typeid(*bodyA).name();
    std::string typeB = typeid(*bodyB).name();
    if (this->beginCollisionMap.find(typeA) == this->beginCollisionMap.end()) {
        throw std::runtime_error("No se encontro el tipo de entidad en el mapa de colisiones");
    }
    (bodyB->*beginCollisionMap[typeA])(bodyA, entitiesToRemove);
}

void CollisionHandler::handlePreSolveCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact) {
    std::string typeA = typeid(*bodyA).name();
    std::string typeB = typeid(*bodyB).name();
    if (this->preSolveCollisionMap.find(typeA) == this->preSolveCollisionMap.end()) {
        throw std::runtime_error("No se encontro el tipo de entidad en el mapa de colisiones");
    }
    (bodyB->*preSolveCollisionMap[typeA])(bodyA, contact);
}

void CollisionHandler::handlePostSolveCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact) {
    std::string typeA = typeid(*bodyA).name();
    std::string typeB = typeid(*bodyB).name();
    if (this->postSolveCollisionMap.find(typeA) == this->postSolveCollisionMap.end()) {
        throw std::runtime_error("No se encontro el tipo de entidad en el mapa de colisiones");
    }
    (bodyB->*postSolveCollisionMap[typeA])(bodyA, contact);
}

void CollisionHandler::handleEndCollision(Entity* bodyA, Entity* bodyB, b2Contact* contact) {
    std::string typeA = typeid(*bodyA).name();
    std::string typeB = typeid(*bodyB).name();
    if (this->endCollisionMap.find(typeA) == this->endCollisionMap.end()) {
        throw std::runtime_error("No se encontro el tipo de entidad en el mapa de colisiones");
    }
    (bodyB->*endCollisionMap[typeA])(bodyA, contact);
}
