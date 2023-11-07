#ifndef BEAM_H
#define BEAM_H

#include "Entity.h"
#include "Worm.h"
#include "Rocket.h"
#include <set>

class Worm;

class Beam : public Entity {
    private:
    bool walkable;

    public:
    Beam(b2Body* body, bool isWalkable);

    bool isWalkable();
    
    void beginCollisionWithBeam(Entity* otherBody, std::set<b2Body*>& entitiesToRemove) override;
    void beginCollisionWithWorm(Entity* otherBody, std::set<b2Body*>& entitiesToRemove) override;
    void beginCollisionWithRocket(Entity* otherBody, std::set<b2Body*>& entitiesToRemove) override;

    void preSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact) override;
    void preSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact) override;
    void preSolveCollisionWithRocket(Entity* otherBody, b2Contact* contact) override;

    void postSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact) override;
    void postSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact) override;
    void postSolveCollisionWithRocket(Entity* otherBody, b2Contact* contact) override;

    void endCollisionWithBeam(Entity* otherBody, b2Contact* contact) override;
    void endCollisionWithWorm(Entity* otherBody, b2Contact* contact) override;
    void endCollisionWithRocket(Entity* otherBody, b2Contact* contact) override;

    ~Beam() override;
};

#endif