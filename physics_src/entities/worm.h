#ifndef WORM_H
#define WORM_H

#include "beam.h"
#include "../aux/auxiliar_functions.h"
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
    std::vector<int> weapons;

    void moveOnWalkableBeam(b2Body* worm, b2Vec2 normal);

    void jump(float maxHeight, float distance);


    public:
    action currentAction;
    Worm(b2Body* body, std::unordered_set<b2Body*>& entitiesToRemove, int id, int team, int direction, float health, std::vector<int> weapons);

    virtual void beginCollisionWithWater(Entity* otherBody, b2Contact* contact) override;
    virtual void beginCollisionWithBeam(Entity* otherBody, b2Contact* contact) override;
    virtual void beginCollisionWithWorm(Entity* otherBody, b2Contact* contact) override;
    virtual void beginCollisionWithProjectile(Entity* otherBody, b2Contact* contact) override;

    virtual void preSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold) override;

    virtual void postSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse) override;

    virtual void endCollisionWithBeam(Entity* otherBody, b2Contact* contact) override;

    ~Worm() override;

    void takeDamage(float damage);

    void die();

    void applyFallDamage(b2Vec2 vel);

    bool isDead();

    int getId();

    void move(int direction);

    void jumpForward();

    void jumpBackwards();

    void handleExplosion(float damage, b2Vec2 explosionCenter);

    void hitWithBat();

    void addHealth(int health);
    
    void reduceAmmo(int weaponId);

    void getAllWeapons();

    WormDTO getDTO();
};


#endif