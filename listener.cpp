#include "listener.h"

EntityType getEntityType(b2Body* body){
    return static_cast<EntityType>(body->GetUserData().pointer);
}

void moveWormOnWalkableBeam(b2Body* worm, b2Contact* contact){
    b2Vec2 vel = worm->GetLinearVelocity();
    b2Vec2 normal = contact->GetManifold()->localNormal;
    b2Vec2 perpendicular = b2Vec2(-normal.y, normal.x);
    int sign = (vel.x > 0) ? -1 : 1;
    worm->SetLinearDamping(0.35f);
    worm->SetGravityScale(0.0f);
    if(normal.y <= 0){
        if(normal.x != 0){
            return;
        }
        sign *=-1;
    }
    worm->SetLinearVelocity(b2Vec2(perpendicular.x * vel.Length() * sign, perpendicular.y * vel.Length() * sign));
}

void Listener::BeginContact(b2Contact* contact) {
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    EntityType typeA = getEntityType(bodyA);
    EntityType typeB = getEntityType(bodyB);

    if((typeA == Worm && typeB == WalkableBeam) || (typeA == WalkableBeam && typeB == Worm)){
        b2Body* worm = (typeA == Worm) ? bodyA : bodyB;
        worm->SetLinearVelocity(b2Vec2(0,0));
        worm->SetLinearDamping(INFINITE_DAMPING);
    }
}

void Listener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
    UNUSED(oldManifold);
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    EntityType typeA = getEntityType(bodyA);
    EntityType typeB = getEntityType(bodyB);

    if((typeA == Worm && typeB == WalkableBeam) || (typeA == WalkableBeam && typeB == Worm)){
        b2Body* worm = (typeA == Worm) ? bodyA : bodyB;
        moveWormOnWalkableBeam(worm, contact);
    }
}

void Listener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
    UNUSED(impulse);
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    EntityType typeA = getEntityType(bodyA);
    EntityType typeB = getEntityType(bodyB);

    if((typeA == Worm && typeB == WalkableBeam) || (typeA == WalkableBeam && typeB == Worm)){
        b2Body* worm = (typeA == Worm) ? bodyA : bodyB;
        worm->SetLinearDamping(INFINITE_DAMPING);
        worm->SetGravityScale(1.0f);
        if(worm->GetLinearVelocity().Length() < VELOCITY_SMOOTH_BREAK){
            worm->SetLinearVelocity(b2Vec2(0,0));
        }
    }
}

void Listener::EndContact(b2Contact* contact) {
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    EntityType typeA = getEntityType(bodyA);
    EntityType typeB = getEntityType(bodyB);
    if((typeA == Worm && typeB == WalkableBeam)){
    }
    if(typeA == WalkableBeam && typeB == Worm){
        bodyB->SetLinearDamping(WORM_DAMPING);
        bodyB->SetGravityScale(1.0f);
    }
}   