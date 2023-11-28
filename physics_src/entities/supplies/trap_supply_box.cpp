#include "trap_supply_box.h"

TrapSupplyBox::TrapSupplyBox(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, int id, int type) : 
    SupplyBox(body, entitiesToRemove, id, type) {}

void TrapSupplyBox::beginCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    //from aux_functions.cpp
    explosiveExplode(this->body, CONFIG.getSupplyBoxTrapDamage(), CONFIG.getSupplyBoxTrapRadius());
    this->entitiesToRemove.insert(this->body);
}

TrapSupplyBox::~TrapSupplyBox() {}