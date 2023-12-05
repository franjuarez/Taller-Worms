#include "provition_supply_box.h"
#include <iostream>

ProvitionsSupplyBox::ProvitionsSupplyBox(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, int id, int type) : 
    SupplyBox(body, entitiesToRemove, id, type) {}

void ProvitionsSupplyBox::beginCollisionWithWorm(Entity* otherBody, b2Contact* contact) {
    Worm* worm = (Worm*) otherBody;
    if(worm->isDead()) return;
    if(this->supplyType == HEALTH_SUPPLY){
        worm->addHealth(CONFIG.getSupplyBoxHealth());
    } else if(supplyType == MORTAR_SUPPLY){
        worm->addAmmo(MORTAR, CONFIG.getMortarSupplyAmmo());
    }else if(supplyType == RED_GRENADE_SUPPLY){
        worm->addAmmo(RED_GRENADE, CONFIG.getRedGrenadeSupplyAmmo());
    }else if(supplyType == BANANA_SUPPLY){
        worm->addAmmo(BANANA, CONFIG.getBananaSupplyAmmo());
    }else if(supplyType == BAT_SUPPLY){
        worm->addAmmo(BAT, CONFIG.getBatSupplyAmmo());
    }else if(supplyType == REMOTE_OPERATED_SUPPLY){
        worm->addAmmo(REMOTE_OPERATED, CONFIG.getTeleportSupplyAmmo());
    } else if(supplyType == HOLY_GRENADE_SUPPLY){
        worm->addAmmo(HOLY_GRENADE, CONFIG.getHolyGrenadeSupplyAmmo());
    } else if(supplyType == DYNAMITE_SUPPLY){
        worm->addAmmo(DYNAMITE, CONFIG.getDynamiteSupplyAmmo());
    } else if(supplyType == AIR_ATTACK_SUPPLY){
        worm->addAmmo(AIR_ATTACK, CONFIG.getAirAttackSupplyAmmo());
    }
    this->entitiesToRemove.insert(this->body);
}

ProvitionsSupplyBox::~ProvitionsSupplyBox() {}