#include "mortar.h"
#include <iostream>
#include <cstdlib>
Mortar::Mortar(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, std::vector<createEntity>& entitiesToAdd, int id, float damage, float radius) : 
        InstantProjectile(body, entitiesToRemove, entitiesToAdd, id, damage, radius) {}

Mortar::~Mortar() {}

void Mortar::leaveFragments(){
    for(int i = 0; i < CONFIG.getMortarFragments(); i++){
       entitiesToAdd.push_back([this](int newId) -> b2Body* {
           ProjectileFragment* fragment = new ProjectileFragment(this->body, this->entitiesToRemove, this->entitiesToAdd, newId, CONFIG.getFragmentDamage(), CONFIG.getFragmentRadius());
           return fragment->createFragment();
       });
    }
}

ExplosivesDTO Mortar::getDTO() {
    return Projectile::getDTO(MORTAR);
}

