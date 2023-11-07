#ifndef LISTENER_H
#define LISTENER_H

#include <box2d/box2d.h>
#include <iostream>
#include "physics_constants.h"
#include "collision_handler.h"

//For supressing unused variable warnings
#define UNUSED(x) (void)(x)

class Listener : public b2ContactListener{
public:
    b2World* world;
    std::set<b2Body*>& entitiesToRemove;
    CollisionHandler collisionHandler;

    Listener(b2World* world, std::set<b2Body*>& entitiesToRemove);

    void BeginContact(b2Contact* contact);

    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    
    void EndContact(b2Contact* contact);
};


#endif