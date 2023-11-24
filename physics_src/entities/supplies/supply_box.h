#ifndef SUPPLY_H
#define SUPPLY_H

#include "../entity.h"
#include "../worm.h"

class Worm;

class SupplyBox : public Entity {
protected:
    int supplyType;
    public:

    SupplyBox(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, int type);

    int getSupplyType();

    virtual void beginCollisionWithWorm(Entity* otherBody, b2Contact* contact) = 0;
    void beginCollisionWithWater(Entity* otherBody, b2Contact* contact) override;

    ~SupplyBox();
};

#endif
