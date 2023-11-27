#include "projectile.h"
#include <iostream>
#include <cstdlib>

Projectile::Projectile(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove,
    std::vector<createEntity>& entitiesToAdd, EntityType entityType, int id,float damage, float radius) : 
    Entity(body, entitiesToRemove, entityType), entitiesToAdd(entitiesToAdd), id(id), damage(damage), radius(radius) {}

ExplosivesDTO Projectile::getDTO(int projectileType){
    Position pos(this->body->GetPosition().x, this->body->GetPosition().y);
    b2Vec2 vel = this->body->GetLinearVelocity();
    ExplosivesDTO dto(projectileType, id, pos, vel.x, vel.y);
    return dto;
}

void Projectile::beginCollisionWithSupplyBox(Entity* otherBody, b2Contact* contact) {
    explode();
    entitiesToRemove.insert(otherBody->body);
}

int Projectile::getId(){
    return this->id;
}

void Projectile::leaveFragments(){ }

void Projectile::explode(){
    //from aux_functions.cpp
    explosiveExplode(this->body, this->damage, this->radius);
    leaveFragments();
    this->entitiesToRemove.insert(this->body);
}

Projectile::~Projectile() {}
