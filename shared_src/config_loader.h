#ifndef CONFIG_G
#define CONFIG_G

#include <yaml-cpp/yaml.h>

class ConfigLoader{
private:
    ConfigLoader(const YAML::Node& node);
    ~ConfigLoader();

    //game
    int fps;
    int turn_time;
    
    //frontend
    int viewfield_x;
    int viewfield_y;
    int camera_speed;

    //world
    int world_width;
    int world_height;
    float world_gravity_x;
    float world_gravity_y;

    //beam
    float beam_large_length;
    float beam_small_length;
    float beam_friction;
    int beam_max_walkable_angle;

    //worm
    int worm_initial_health;
    
    //move
    float worm_move_velocity;

    //jump
    float jump_forward_movement_x;
    float jump_forward_movement_y;
    float jump_backwards_movement_x;
    float jump_backwards_movement_y;

    //height damage
    float min_height_to_damage;
    float max_height_damage;

    //projectile
    float projectile_max_speed;
    float projectile_impulse_factor_x;
    float projectile_impulse_factor_y;

    //bazooka
    float bazooka_radius;
    float bazooka_damage;
    int bazooka_starting_ammo;

    //green grenade
    float green_grenade_radius;
    float green_grenade_damage;
    int green_grenade_starting_ammo;

    //mortar
    float mortar_radius;
    float mortar_damage;
    int mortar_fragments;
    int mortar_starting_ammo;

    //red grenade
    float red_grenade_radius;
    float red_grenade_damage;
    int red_grenade_fragments;
    int red_grenade_starting_ammo;

    //fragment
    float fragment_radius;
    float fragment_damage;

    //banana
    float banana_radius;
    float banana_damage;
    int banana_starting_ammo;
    float banana_bounciness;

    //bat
    float bat_damage;
    float bat_impulse_factor_x;
    int bat_starting_ammo;

    //holy grenade
    float holy_grenade_radius;
    float holy_grenade_damage;
    int holy_grenade_starting_ammo;

    //dynamite
    float dynamite_radius;
    float dynamite_damage;
    int dynamite_starting_ammo;

    //air attack
    float air_attack_missiles;
    float air_attack_starting_ammo;

    //air attack missiles
    float air_attack_missile_radius;
    float air_attack_missile_damage;
public:

    static ConfigLoader& getInstance();

    //game
    int getFps();
    int getTurnTime();

    //frontend
    int getViewfieldX();
    int getViewfieldY();
    int getCameraSpeed();
    
    //world
    int getWorldWidth();
    int getWorldHeight();
    float getWorldGravityX();
    float getWorldGravityY();

    //beam
    float getBeamLargeLength();
    float getBeamSmallLength();
    float getBeamFriction();
    int getBeamMaxWalkableAngle();

    //worm
    int getWormInitialHealth();

    //move
    float getWormMoveVelocity();
    
    //jump
    float getJumpForwardMovementX();
    float getJumpForwardMovementY();
    float getJumpBackwardsMovementX();
    float getJumpBackwardsMovementY();

    //height damage
    float getMinHeightToDamage();
    float getMaxHeightDamage();

    //projectile
    float getProjectileMaxSpeed();
    float getProjectileImpulseFactorX();
    float getProjectileImpulseFactorY();

    //bazooka
    float getBazookaRadius();
    float getBazookaDamage();
    int getBazookaStartingAmmo();

    //green grenade
    float getGreenGrenadeRadius();
    float getGreenGrenadeDamage();
    int getGreenGrenadeStartingAmmo();

    //mortar
    float getMortarRadius();
    float getMortarDamage();
    int getMortarFragments();
    int getMortarStartingAmmo();

    //red grenade
    float getRedGrenadeRadius();
    float getRedGrenadeDamage();
    int getRedGrenadeFragments();
    int getRedGrenadeStartingAmmo();

    //fragment
    float getFragmentRadius();
    float getFragmentDamage();

    //banana
    float getBananaRadius();
    float getBananaDamage();
    int getBananaStartingAmmo();
    float getBananaBounciness();
    
    //bat
    float getBatDamage();
    float getBatImpulseFactorX();
    int getBatStartingAmmo();

    //holy grenade
    float getHolyGrenadeRadius();
    float getHolyGrenadeDamage();
    int getHolyGrenadeStartingAmmo();

    //dynamite
    float getDynamiteRadius();
    float getDynamiteDamage();
    int getDynamiteStartingAmmo();

    //air attack
    float getAirAttackMissiles();
    float getAirAttackStartingAmmo();

    //air attack missiles
    float getAirAttackMissileRadius();
    float getAirAttackMissileDamage();

};

#endif
