#include "projectile.h"
#include <iostream>
#include <cstdlib>

Projectile::Projectile(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove,
    std::vector<createEntity>& entitiesToAdd, EntityType projectileType, int id,float damage, float radius) : 
    Entity(body, entitiesToRemove, projectileType), entitiesToAdd(entitiesToAdd), id(id), damage(damage), radius(radius) {}

ExplosivesDTO Projectile::getDTO(){
    Position pos(this->body->GetPosition().x, this->body->GetPosition().y);
    b2Vec2 vel = this->body->GetLinearVelocity();
    ExplosivesDTO dto(0, id, pos, vel.x, vel.y);
    return dto;
}

void Projectile::leaveFragments(){ }

void Projectile::explode(){
    b2Body* projectile = this->body;
    b2Vec2 projectilePos = projectile->GetPosition();
    ExplosionQueryCallback explosionCallback(projectilePos, this->radius);
    b2AABB aabb;
    aabb.lowerBound = projectilePos - b2Vec2(this->radius, this->radius);
    aabb.upperBound = projectilePos + b2Vec2(this->radius, this->radius);
    b2World* world = projectile->GetWorld();
    world->QueryAABB( &explosionCallback, aabb);
    
    for(b2Body* body : explosionCallback.foundBodies) {
        //Assuming it just affects worms
        Worm* worm = (Worm*) body->GetUserData().pointer;
        b2Vec2 bodyPos = body->GetPosition();
        float distance = b2Distance(projectilePos, bodyPos);
        float damage = this->damage * (1 - distance / this->radius);
        worm->handleExplosion(damage, projectilePos);
    }
    leaveFragments();
    this->entitiesToRemove.insert(projectile);
}

Projectile::~Projectile() {}
