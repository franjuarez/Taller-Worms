#ifndef LISTENER_H
#define LISTENER_H

#include <box2d/box2d.h>
#include <iostream>
#include "physics_constants.h"

//For supressing unused variable warnings
#define UNUSED(x) (void)(x)

enum EntityType{
    Worm,
    WalkableBeam,
    SlidingBeam,
};

class Listener : public b2ContactListener{
public:
    void BeginContact(b2Contact* contact);

    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    
    void EndContact(b2Contact* contact);
};


#endif