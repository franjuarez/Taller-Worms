#ifndef WORM_H
#define WORM_H

#include "beam.h"
#include "../aux/auxiliar_functions.h"
#include "../query_handlers/melee_handler.h"
#include "../../game_src/worm_dto.h"

enum action {
    STANDING, //0
    MOVING, //1
    JUMPING, //2
    EJECTED, //3
};


class Worm : public Entity {
    private:
    int id;
    int team;
    float health;
    int direction;
    b2Fixture* footSensor;
    int onGrounds = 0;
    action currentAction;
    std::vector<int> weapons;
    int max_ammo_per_weapon[AMOUNT_OF_WEAPONS];
    bool invincible;

    void moveOnWalkableBeam(b2Body* worm, b2Vec2 normal);

    void jump(float maxHeight, float distance);


    public:
    Worm(b2Body* body, b2Fixture* footSensor, std::unordered_set<b2Body*>& entitiesToRemove, int id, int team, int direction, float health, std::vector<int> weapons);

    virtual void beginCollisionWithWater(Entity* otherBody, b2Contact* contact) override;
    virtual void beginCollisionWithBeam(Entity* otherBody, b2Contact* contact) override;
    virtual void beginCollisionWithProjectile(Entity* otherBody, b2Contact* contact) override;
    virtual void beginCollisionWithSupplyBox(Entity* otherBody, b2Contact* contact) override;

    virtual void preSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact, const b2Manifold* oldManifold) override;

    virtual void postSolveCollisionWithBeam(Entity* otherBody, b2Contact* contact, const b2ContactImpulse* impulse) override;

    virtual void endCollisionWithBeam(Entity* otherBody, b2Contact* contact) override;

    ~Worm() override;

    void takeDamage(float damage);

    void die();

    void applyFallDamage(b2Vec2 vel);

    bool isDead();

    int getId();

    void changeDirection(int direction);

    void move(int direction);

    void jumpForward();

    void jumpBackwards();

    void handleExplosion(float damage, b2Vec2 explosionCenter);

    void hitWithBat(int direction);
    
    bool hasAmmo(int weaponId);

    void reduceAmmo(int weaponId);

    void addAmmo(int weaponId, int amount);

    //cheats
    void addHealth(int additionalHealth);
    
    void getAllWeapons();

    void toggleInvincible();

    WormDTO getDTO();
};


#endif