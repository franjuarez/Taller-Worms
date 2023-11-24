#ifndef TRAP_SUPPLY_BOX
#define TRAP_SUPPLY_BOX

#include "supply_box.h"
#include "../../query_handlers/explosion_handler.h"

class TrapSupplyBox : public SupplyBox{
public:

    TrapSupplyBox(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, int type);

    void beginCollisionWithWorm(Entity* otherBody, b2Contact* contact) override;

    ~TrapSupplyBox();
};

#endif