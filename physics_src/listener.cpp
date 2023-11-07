#include "listener.h"

Listener::Listener(b2World* world, std::set<b2Body*>& entitiesToRemove) : world(world), entitiesToRemove(entitiesToRemove) {}

void Listener::BeginContact(b2Contact* contact) {
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    Entity* typeA = (Entity*) bodyA->GetUserData().pointer; 
    Entity* typeB = (Entity*) bodyB->GetUserData().pointer;

    collisionHandler.handleBeginCollision(typeA, typeB, entitiesToRemove);
}

void Listener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
    UNUSED(oldManifold);
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    Entity* typeA = (Entity*) bodyA->GetUserData().pointer; 
    Entity* typeB = (Entity*) bodyB->GetUserData().pointer;

    collisionHandler.handlePreSolveCollision(typeA, typeB, contact);
}

void Listener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
    UNUSED(impulse);
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    Entity* typeA = (Entity*) bodyA->GetUserData().pointer; 
    Entity* typeB = (Entity*) bodyB->GetUserData().pointer;

    collisionHandler.handlePostSolveCollision(typeA, typeB, contact);
}

void Listener::EndContact(b2Contact* contact) {
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    Entity* typeA = (Entity*) bodyA->GetUserData().pointer; 
    Entity* typeB = (Entity*) bodyB->GetUserData().pointer;

    collisionHandler.handleEndCollision(typeA, typeB, contact);
}   