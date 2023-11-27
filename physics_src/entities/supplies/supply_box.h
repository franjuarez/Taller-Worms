#ifndef SUPPLY_H
#define SUPPLY_H

#include "../entity.h"
#include "../worm.h"
#include "../../../game_src/supply_box_dto.h"

class SupplyBox : public Entity {
protected:
    int id;
    int supplyType;
    public:

    SupplyBox(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, int id, int type);

    int getId();
    int getSupplyType();
    SupplyBoxDTO getDTO();

    virtual void beginCollisionWithWorm(Entity* otherBody, b2Contact* contact) = 0;
    void beginCollisionWithWater(Entity* otherBody, b2Contact* contact) override;
    void beginCollisionWithProjectile(Entity* otherBody, b2Contact* contact) override;

    ~SupplyBox();
};

#endif
