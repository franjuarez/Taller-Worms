#include "projectile.h"
#include <iostream>
#include <cstdlib>

#define DEGTORAD 0.0174532925199432957f

Projectile::Projectile(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove,
    std::vector<createEntity>& entitiesToAdd, EntityType entityType, int id,float damage, float radius) : 
    Entity(body, entitiesToRemove, entityType), entitiesToAdd(entitiesToAdd), id(id), damage(damage), radius(radius) {}

ExplosivesDTO Projectile::getDTO(int projectileType){
    Position pos(this->body->GetPosition().x, this->body->GetPosition().y);
    b2Vec2 vel = this->body->GetLinearVelocity();
    ExplosivesDTO dto(projectileType, id, pos, vel.x, vel.y);
    return dto;
}

int Projectile::getId(){
    return this->id;
}

void Projectile::leaveFragments(){ }

void Projectile::explode(){
    b2Body* projectile = this->body;
    b2Vec2 projectilePos = projectile->GetPosition();
    b2World* world = projectile->GetWorld();
    int numberOfRays = 20;
    std::unordered_set<b2Body*> allFoundBodies;
    for(int i = 0; i < numberOfRays; i++){
        float angle = (i / (float)numberOfRays) * 360 * DEGTORAD;
        b2Vec2 rayDir( sinf(angle), cosf(angle) );
        b2Vec2 rayEnd = projectilePos + this->radius * rayDir;
        ExplosionQueryCallback callback(projectilePos, this->radius);
        world->RayCast(&callback, projectilePos, rayEnd);
        for(b2Body* body : callback.foundBodies) {
            if(allFoundBodies.find(body) != allFoundBodies.end()){
                continue;
            }
            //Assuming it just affects worms
            Worm* worm = (Worm*) body->GetUserData().pointer;
            b2Vec2 bodyPos = body->GetPosition();
            float distance = b2Distance(projectilePos, bodyPos);
            float damage = this->damage * (1 - distance / this->radius);
            worm->handleExplosion(damage, projectilePos);
            allFoundBodies.insert(body);
        }
    }
    leaveFragments();
    this->entitiesToRemove.insert(projectile);
}

Projectile::~Projectile() {}
