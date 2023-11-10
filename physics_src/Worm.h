#ifndef WORM_H
#define WORM_H

#include "Entity.h"
#include "Beam.h"
#include "Rocket.h"
#include "auxiliar_physics_functions.h"
#include "../game_src/worm_dto.h"

enum action {
    STANDING,
    MOVING,
    JUMPING,
    EJECTED,
};

class Worm : public Entity {
    private:
    int id;
    int team;
    float health;
    int direction;
    action currentAction;

    //weapons (Future update)

    void moveOnWalkableBeam(b2Body* worm, b2Vec2 normal);

    void jump(float maxHeight, float distance);


    public:
    Worm(b2Body* body, std::vector<b2Body*>& entitiesToRemove, int id, int team, int direction);

    virtual void beginCollisionWithBeam(Entity* otherBody, b2Contact* contact);
    virtual void beginCollisionWithWorm(Entity* otherBody, b2Contact* contact);
    virtual void beginCollisionWithRocket(Entity* otherBody, b2Contact* contact);

    virtual void preSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold);
    virtual void preSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold);
    virtual void preSolveCollisionWithRocket(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold);

    virtual void postSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse);
    virtual void postSolveCollisionWithWorm(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse);
    virtual void postSolveCollisionWithRocket(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse);

    virtual void endCollisionWithBeam(Entity* otherBody, b2Contact* contact);
    virtual void endCollisionWithWorm(Entity* otherBody, b2Contact* contact);
    virtual void endCollisionWithRocket(Entity* otherBody, b2Contact* contact);

    ~Worm() override;

    void takeDamage(float damage);

    void applyFallDamage(b2Vec2 vel);

    bool isDead();

    int getId();

    void move(int direction);

    void jumpForward();

    void jumpBackwards();

    void handleExplosion(float damage, b2Vec2 explosionCenter);

    WormDTO getDTO();
};

#endif