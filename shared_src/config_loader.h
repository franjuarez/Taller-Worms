#ifndef CONFIG_G
#define CONFIG_G

#include <yaml-cpp/yaml.h>
#include <string>

class ConfigLoader{
private:
    ConfigLoader(const YAML::Node& node);
    ~ConfigLoader();
    
    //maps
    std::string maps_file;

    //game
    int fps;
    int music_volume;
    int sfx_volume;
    int turn_time;
    int extra_time;
    
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
    int worm_additional_health;
    int worm_max_health;
    
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
    int bazooka_max_ammo;

    //green grenade
    float green_grenade_radius;
    float green_grenade_damage;
    int green_grenade_starting_ammo;
    int green_grenade_max_ammo;

    //mortar
    float mortar_radius;
    float mortar_damage;
    int mortar_fragments;
    int mortar_supply_ammo;
    int mortar_max_ammo;

    //red grenade
    float red_grenade_radius;
    float red_grenade_damage;
    int red_grenade_fragments;
    int red_grenade_supply_ammo;
    int red_grenade_max_ammo;

    //fragment
    float fragment_radius;
    float fragment_damage;

    //banana
    float banana_radius;
    float banana_damage;
    int banana_supply_ammo;
    float banana_bounciness;
    int banana_max_ammo;

    //bat
    float bat_damage;
    float bat_impulse_factor;
    int bat_supply_ammo;
    int bat_max_ammo;

    //holy grenade
    float holy_grenade_radius;
    float holy_grenade_damage;
    int holy_grenade_supply_ammo;
    int holy_grenade_max_ammo;

    //dynamite
    float dynamite_radius;
    float dynamite_damage;
    int dynamite_supply_ammo;
    int dynamite_max_ammo;

    //air attack
    int air_attack_missiles;
    int air_attack_supply_ammo;
    int air_attack_max_ammo;

    //air attack missiles
    float air_attack_missile_radius;
    float air_attack_missile_damage;

    //teleport
    int teleport_supply_ammo;
    int teleport_max_ammo;

    //supply box
    float supply_box_probability;
    float supply_box_health_probability;
    float supply_box_ammo_probability;
    float supply_box_trap_probability;
    float supply_box_health;
    float supply_box_trap_radius;
    float supply_box_trap_damage;

    //ammo probabilities
    float mortar_ammo_probability;
    float red_grenade_ammo_probability;
    float teleport_ammo_probability;
    float bat_ammo_probability;
    float banana_ammo_probability;
    float dynamite_ammo_probability;
    float air_attack_ammo_probability;
    float holy_grenade_ammo_probability;

public:

    static ConfigLoader& getInstance();

    //maps
    std::string getMapsFile();

    //game
    int getFps();
    int getMusicVolume();
    int getSfxVolume();
    int getTurnTime();
    int getExtraTime();

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
    int getWormAdditionalHealth();
    int getWormMaxHealth();

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
    int getBazookaMaxAmmo();

    //green grenade
    float getGreenGrenadeRadius();
    float getGreenGrenadeDamage();
    int getGreenGrenadeStartingAmmo();
    int getGreenGrenadeMaxAmmo();

    //mortar
    float getMortarRadius();
    float getMortarDamage();
    int getMortarFragments();
    int getMortarSupplyAmmo();
    int getMortarMaxAmmo();

    //red grenade
    float getRedGrenadeRadius();
    float getRedGrenadeDamage();
    int getRedGrenadeFragments();
    int getRedGrenadeSupplyAmmo();
    int getRedGrenadeMaxAmmo();

    //fragment
    float getFragmentRadius();
    float getFragmentDamage();

    //banana
    float getBananaRadius();
    float getBananaDamage();
    int getBananaSupplyAmmo();
    float getBananaBounciness();
    int getBananaMaxAmmo();

    //bat
    float getBatDamage();
    float getBatImpulseFactor();
    int getBatSupplyAmmo();
    int getBatMaxAmmo();

    //holy grenade
    float getHolyGrenadeRadius();
    float getHolyGrenadeDamage();
    int getHolyGrenadeSupplyAmmo();
    int getHolyGrenadeMaxAmmo();

    //dynamite
    float getDynamiteRadius();
    float getDynamiteDamage();
    int getDynamiteSupplyAmmo();
    int getDynamiteMaxAmmo();

    //air attack
    int getAirAttackMissiles();
    int getAirAttackSupplyAmmo();
    int getAirAttackMaxAmmo();

    //air attack missiles
    float getAirAttackMissileRadius();
    float getAirAttackMissileDamage();

    //teleport
    int getTeleportSupplyAmmo();
    int getTeleportMaxAmmo();

    //supply box
    float getSupplyBoxProbability();
    float getSupplyBoxHealthProbability();
    float getSupplyBoxAmmoProbability();
    float getSupplyBoxTrapProbability();
    float getSupplyBoxHealth();
    float getSupplyBoxTrapRadius();
    float getSupplyBoxTrapDamage();

    //ammo probabilities
    float getMortarAmmoProbability();
    float getRedGrenadeAmmoProbability();
    float getTeleportAmmoProbability();
    float getBatAmmoProbability();
    float getBananaAmmoProbability();
    float getDynamiteAmmoProbability();
    float getAirAttackAmmoProbability();
    float getHolyGrenadeAmmoProbability();

};

#endif
