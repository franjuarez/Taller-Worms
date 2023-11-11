#ifndef WORM_H
#define WORM_H

#include "entity.h"
#include "beam.h"
#include "rocket.h"
#include "../auxiliar_physics_functions.h"
#include "../query_handlers/melee_handler.h"
#include "../../game_src/worm_dto.h"


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

    //weapons (Future update)

    void moveOnWalkableBeam(b2Body* worm, b2Vec2 normal);

    void jump(float maxHeight, float distance);


    public:
    action currentAction;
    Worm(b2Body* body, std::vector<b2Body*>& entitiesToRemove, int id, int team, int direction);

    virtual void beginCollisionWithWater(Entity* otherBody, b2Contact* contact);
    virtual void beginCollisionWithBeam(Entity* otherBody, b2Contact* contact);
    virtual void beginCollisionWithWorm(Entity* otherBody, b2Contact* contact);
    virtual void beginCollisionWithRocket(Entity* otherBody, b2Contact* contact);

    virtual void preSolveCollisionWithWater(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold);
    virtual void preSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold);
    virtual void preSolveCollisionWithRocket(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold);

    virtual void postSolveCollisionWithWater(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse);
    virtual void postSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse);

    virtual void endCollisionWithBeam(Entity* otherBody, b2Contact* contact);

    ~Worm() override;

    void takeDamage(float damage);

    void applyFallDamage(b2Vec2 vel);

    bool isDead();

    int getId();

    void move(int direction);

    void jumpForward();

    void jumpBackwards();

    void handleExplosion(float damage, b2Vec2 explosionCenter);

    void hitWithBat();

    WormDTO getDTO();
};

#endif