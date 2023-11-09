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
    Worm(b2Body* body, int id, int team, int direction);


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

    ~Worm() override;

    void takeDamage(float damage);

    bool isDead();

    int getId();

    void move(int direction);

    void jumpForward();

    void jumpBackwards();

    WormDTO getDTO();
};

#endif