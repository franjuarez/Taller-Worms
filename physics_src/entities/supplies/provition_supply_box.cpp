#include "provition_supply_box.h"
#include <iostream>

ProvitionsSupplyBox::ProvitionsSupplyBox(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, int id, int type) : 
    SupplyBox(body, entitiesToRemove, id, type) {}

void ProvitionsSupplyBox::beginCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    Worm* worm = (Worm*) otherBody;
    if(this->supplyType == HEALTH_SUPPLY){
        worm->addHealth(CONFIG.getWormInitialHealth());
    } else if(supplyType == MORTAR){
        worm->addAmmo(MORTAR, CONFIG.getMortarSupplyAmmo());
    }else if(supplyType == RED_GRENADE_SUPPLY){
        worm->addAmmo(RED_GRENADE, CONFIG.getRedGrenadeSupplyAmmo());
    }else if(supplyType == BANANA_SUPPLY){
        worm->addAmmo(BANANA, CONFIG.getBananaSupplyAmmo());
    }else if(supplyType == BAT_SUPPLY){
        worm->addAmmo(BAT, CONFIG.getBatSupplyAmmo());
    }else if(supplyType == TELEPORT_SUPPLY){
        worm->addAmmo(TELEPORT, CONFIG.getTeleportSupplyAmmo());
    }
    this->entitiesToRemove.insert(this->body);
}

ProvitionsSupplyBox::~ProvitionsSupplyBox() {}