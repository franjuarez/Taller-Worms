#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <vector>
#include <functional>
#include "../worm.h"
#include "../../query_handlers/explosion_handler.h"
#include "../../../game_src/explosives_dto.h"

typedef std::function<b2Body*(int newId)> createEntity;

class Projectile : public Entity {
protected:
    std::vector<createEntity>& entitiesToAdd;
    int id;
    float damage;
    float radius;

    virtual ExplosivesDTO getDTO(int projectileType);
public:
    Projectile(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, std::vector<createEntity>& entitiesToAdd,
     EntityType entityType, int id, float damage, float radius);
    
    virtual void explode();
    virtual void leaveFragments();

    virtual void beginCollisionWithWater(Entity* otherBody, b2Contact* contact) = 0;
    virtual void beginCollisionWithBeam(Entity* otherBody, b2Contact* contact) = 0;
    virtual void beginCollisionWithWorm(Entity* otherBody, b2Contact* contact) = 0;

    virtual ExplosivesDTO getDTO() = 0;

    ~Projectile();
};

#endif