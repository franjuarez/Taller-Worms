#ifndef PROVISION_SUPPLY_H
#define PROVISION_SUPPLY_H

#include "supply_box.h"

class Worm;

class ProvitionsSupplyBox : public SupplyBox {
public:

    ProvitionsSupplyBox(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, int id, int type);

    void beginCollisionWithWorm(Entity* otherBody, b2Contact* contact) override;

    ~ProvitionsSupplyBox();
};

#endif
