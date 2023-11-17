#include "red_grenade.h"

RedGrenade::RedGrenade(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove,
 std::vector<createEntity>& entitiesToAdd, int id, float damage, float radius, float explosionTimer) :
    DelayedProjectile(body, entitiesToRemove, entitiesToAdd, id, damage, radius, explosionTimer) {}


void RedGrenade::leaveFragments(){
    for(int i = 0; i < MORTAR_FRAGMENTS; i++){
       entitiesToAdd.push_back([this](int newId) -> b2Body* {
           ProjectileFragment* fragment = new ProjectileFragment(this->body, this->entitiesToRemove, this->entitiesToAdd, newId, FRAGMENT_DAMAGE, FRAGMENT_BLAST_RADIOUS);
           return fragment->createFragment();
       });
    }
}

RedGrenade::~RedGrenade() {}
