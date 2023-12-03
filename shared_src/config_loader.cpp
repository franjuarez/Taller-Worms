#include "config_loader.h"

#define PATH_TO_CONFIG_FILE "/etc/TPworms/configuration.yaml"

ConfigLoader::ConfigLoader(const YAML::Node& node) :
    //maps
    maps_file(node["maps_file"].as<std::string>()),

    //game
    fps(node["game"]["FPS"].as<int>()),
    music_volume(node["game"]["music_volume"].as<int>()),
    sfx_volume(node["game"]["music_volume"].as<int>()),
    turn_time(node["game"]["turn_time"].as<int>()),
    extra_time(node["game"]["extra_time"].as<int>()),
    
    //frontend
    viewfield_x(node["camera"]["viewfield_x"].as<int>()),
    viewfield_y(node["camera"]["viewfield_y"].as<int>()),
    camera_speed(node["camera"]["camera_speed"].as<int>()),
    
    //world
    world_width(node["world"]["width"].as<int>()),
    world_height(node["world"]["height"].as<int>()),
    world_gravity_x(node["world"]["gravity_x"].as<float>()),
    world_gravity_y(node["world"]["gravity_y"].as<float>()),
    
    //beam
    beam_large_length(node["beam"]["large_length"].as<float>()),
    beam_small_length(node["beam"]["small_length"].as<float>()),
    beam_friction(node["beam"]["friction"].as<float>()),
    beam_max_walkable_angle(node["beam"]["max_walkable_angle"].as<int>()),
    
    //worm
    worm_initial_health(node["worm"]["initial_health"].as<int>()),
    worm_additional_health(node["worm"]["additional_health"].as<int>()),
    worm_max_health(node["worm"]["max_health"].as<int>()),
    
    //move
    worm_move_velocity(node["move"]["move_velocity"].as<float>()),
    
    //jump
    jump_forward_movement_x(node["jump"]["jump_forward_movement_x"].as<float>()),
    jump_forward_movement_y(node["jump"]["jump_forward_movement_y"].as<float>()),
    jump_backwards_movement_x(node["jump"]["jump_backwards_movement_x"].as<float>()),
    jump_backwards_movement_y(node["jump"]["jump_backwards_movement_y"].as<float>()),
    
    //height damage
    min_height_to_damage(node["height_damage"]["min_height_to_damage"].as<float>()),
    max_height_damage(node["height_damage"]["max_height_damage"].as<float>()),
    
    //projectile
    projectile_max_speed(node["projectile"]["max_speed"].as<float>()),
    projectile_impulse_factor_x(node["projectile"]["impulse_factor_x"].as<float>()),
    projectile_impulse_factor_y(node["projectile"]["impulse_factor_y"].as<float>()),
    
    //bazooka
    bazooka_radius(node["bazooka"]["radius"].as<float>()),
    bazooka_damage(node["bazooka"]["damage"].as<float>()),
    bazooka_starting_ammo(node["bazooka"]["starting_ammo"].as<int>()),
    bazooka_max_ammo(node["bazooka"]["max_ammo"].as<int>()),
    
    //green grenade
    green_grenade_radius(node["green_grenade"]["radius"].as<float>()),
    green_grenade_damage(node["green_grenade"]["damage"].as<float>()),
    green_grenade_starting_ammo(node["green_grenade"]["starting_ammo"].as<int>()),
    green_grenade_max_ammo(node["green_grenade"]["max_ammo"].as<int>()),
    
    //mortar
    mortar_radius(node["mortar"]["radius"].as<float>()),
    mortar_damage(node["mortar"]["damage"].as<float>()),
    mortar_fragments(node["mortar"]["fragments"].as<int>()), // Added missing mortar_fragments
    mortar_supply_ammo(node["mortar"]["supply_ammo"].as<int>()),
    mortar_max_ammo(node["mortar"]["max_ammo"].as<int>()),

    //red grenade
    red_grenade_radius(node["red_grenade"]["radius"].as<float>()),
    red_grenade_damage(node["red_grenade"]["damage"].as<float>()),
    red_grenade_fragments(node["red_grenade"]["fragments"].as<int>()),
    red_grenade_supply_ammo(node["red_grenade"]["supply_ammo"].as<int>()),
    red_grenade_max_ammo(node["red_grenade"]["max_ammo"].as<int>()),
    
    //fragment
    fragment_radius(node["fragments"]["radius"].as<float>()),
    fragment_damage(node["fragments"]["damage"].as<float>()),
    
    //banana
    banana_radius(node["banana"]["radius"].as<float>()),
    banana_damage(node["banana"]["damage"].as<float>()),
    banana_supply_ammo(node["banana"]["supply_ammo"].as<int>()),
    banana_bounciness(node["banana"]["bounciness"].as<float>()),
    banana_max_ammo(node["banana"]["max_ammo"].as<int>()),
    
    //bat
    bat_damage(node["bat"]["damage"].as<float>()),
    bat_impulse_factor(node["bat"]["impulse_factor"].as<float>()),
    bat_supply_ammo(node["bat"]["supply_ammo"].as<int>()),
    bat_max_ammo(node["bat"]["max_ammo"].as<int>()),
    
    //holy grenade
    holy_grenade_radius(node["holy_grenade"]["radius"].as<float>()),
    holy_grenade_damage(node["holy_grenade"]["damage"].as<float>()),
    holy_grenade_supply_ammo(node["holy_grenade"]["supply_ammo"].as<int>()),
    holy_grenade_max_ammo(node["holy_grenade"]["max_ammo"].as<int>()),
    
    //dynamite
    dynamite_radius(node["dynamite"]["radius"].as<float>()),
    dynamite_damage(node["dynamite"]["damage"].as<float>()),
    dynamite_supply_ammo(node["dynamite"]["supply_ammo"].as<int>()),
    dynamite_max_ammo(node["dynamite"]["max_ammo"].as<int>()),
    
    //air attack
    air_attack_missiles(node["air_attack"]["missiles"].as<int>()),
    air_attack_supply_ammo(node["air_attack"]["supply_ammo"].as<int>()),
    air_attack_max_ammo(node["air_attack"]["max_ammo"].as<int>()),
    
    //air attack missiles
    air_attack_missile_radius(node["air_attack"]["missile_radius"].as<float>()),
    air_attack_missile_damage(node["air_attack"]["missile_damage"].as<float>()), 
    
    //teleport
    teleport_supply_ammo(node["teleport"]["supply_ammo"].as<int>()),
    teleport_max_ammo(node["teleport"]["max_ammo"].as<int>()),

    //supply box
    supply_box_probability(node["supply_box"]["probability"].as<float>()),
    supply_box_health_probability(node["supply_box"]["probability_health"].as<float>()),
    supply_box_ammo_probability(node["supply_box"]["probability_ammo"].as<float>()),
    supply_box_trap_probability(node["supply_box"]["probability_trap"].as<float>()),
    supply_box_health(node["supply_box"]["health"].as<int>()),
    supply_box_trap_radius(node["supply_box"]["trap_radius"].as<float>()),
    supply_box_trap_damage(node["supply_box"]["trap_damage"].as<float>()),

    //ammo probabilities
    mortar_ammo_probability(node["ammo_box_probabilities"]["probability_mortar"].as<float>()),
    red_grenade_ammo_probability(node["ammo_box_probabilities"]["probability_red_grenade"].as<float>()),
    banana_ammo_probability(node["ammo_box_probabilities"]["probability_banana"].as<float>()),
    teleport_ammo_probability(node["ammo_box_probabilities"]["probability_teleport"].as<float>()),
    bat_ammo_probability(node["ammo_box_probabilities"]["probability_bat"].as<float>()),
    dynamite_ammo_probability(node["ammo_box_probabilities"]["probability_dynamite"].as<float>()),
    air_attack_ammo_probability(node["ammo_box_probabilities"]["probability_air_attack"].as<float>()),
    holy_grenade_ammo_probability(node["ammo_box_probabilities"]["probability_holy_grenade"].as<float>())
    {}

ConfigLoader& ConfigLoader::getInstance() {
    static ConfigLoader instance(YAML::LoadFile(PATH_TO_CONFIG_FILE));
    return instance;
}

ConfigLoader::~ConfigLoader() {}

std::string ConfigLoader::getMapsFile() {
    return maps_file;
}

int ConfigLoader::getFps() {
    return fps;
}

int ConfigLoader::getMusicVolume() {
    return music_volume;
}

int ConfigLoader::getSfxVolume() {
    return sfx_volume;
}

int ConfigLoader::getTurnTime() {
    return turn_time;
}

int ConfigLoader::getExtraTime() {
    return extra_time;
}

int ConfigLoader::getViewfieldX() {
    return viewfield_x;
}

int ConfigLoader::getViewfieldY() {
    return viewfield_y;
}

int ConfigLoader::getCameraSpeed() {
    return camera_speed;
}

int ConfigLoader::getWorldWidth() {
    return world_width;
}

int ConfigLoader::getWorldHeight() {
    return world_height;
}

float ConfigLoader::getWorldGravityX() {
    return world_gravity_x;
}

float ConfigLoader::getWorldGravityY() {
    return world_gravity_y;
}

float ConfigLoader::getBeamLargeLength() {
    return beam_large_length;
}

float ConfigLoader::getBeamSmallLength() {
    return beam_small_length;
}

float ConfigLoader::getBeamFriction() {
    return beam_friction;
}

int ConfigLoader::getBeamMaxWalkableAngle() {
    return beam_max_walkable_angle;
}

int ConfigLoader::getWormInitialHealth() {
    return worm_initial_health;
}

int ConfigLoader::getWormAdditionalHealth() {
    return worm_additional_health;
}

int ConfigLoader::getWormMaxHealth() {
    return worm_max_health;
}

float ConfigLoader::getWormMoveVelocity() {
    return worm_move_velocity;
}

float ConfigLoader::getJumpForwardMovementX() {
    return jump_forward_movement_x;
}

float ConfigLoader::getJumpForwardMovementY() {
    return jump_forward_movement_y;
}

float ConfigLoader::getJumpBackwardsMovementX() {
    return jump_backwards_movement_x;
}

float ConfigLoader::getJumpBackwardsMovementY() {
    return jump_backwards_movement_y;
}

float ConfigLoader::getMinHeightToDamage() {
    return min_height_to_damage;
}

float ConfigLoader::getMaxHeightDamage() {
    return max_height_damage;
}

float ConfigLoader::getProjectileMaxSpeed() {
    return projectile_max_speed;
}

float ConfigLoader::getProjectileImpulseFactorX() {
    return projectile_impulse_factor_x;
}

float ConfigLoader::getProjectileImpulseFactorY() {
    return projectile_impulse_factor_y;
}

float ConfigLoader::getBazookaRadius() {
    return bazooka_radius;
}

float ConfigLoader::getBazookaDamage() {
    return bazooka_damage;
}

int ConfigLoader::getBazookaStartingAmmo() {
    return bazooka_starting_ammo;
}

int ConfigLoader::getBazookaMaxAmmo() {
    return bazooka_max_ammo;
}

float ConfigLoader::getGreenGrenadeRadius() {
    return green_grenade_radius;
}

float ConfigLoader::getGreenGrenadeDamage() {
    return green_grenade_damage;
}

int ConfigLoader::getGreenGrenadeStartingAmmo() {
    return green_grenade_starting_ammo;
}

int ConfigLoader::getGreenGrenadeMaxAmmo() {
    return green_grenade_max_ammo;
}

float ConfigLoader::getMortarRadius() {
    return mortar_radius;
}

float ConfigLoader::getMortarDamage() {
    return mortar_damage;
}

int ConfigLoader::getMortarFragments() {
    return mortar_fragments;
}

int ConfigLoader::getMortarSupplyAmmo() {
    return mortar_supply_ammo;
}

int ConfigLoader::getMortarMaxAmmo() {
    return mortar_max_ammo;
}

float ConfigLoader::getRedGrenadeRadius() {
    return red_grenade_radius;
}

float ConfigLoader::getRedGrenadeDamage() {
    return red_grenade_damage;
}

int ConfigLoader::getRedGrenadeFragments() {
    return red_grenade_fragments;
}

int ConfigLoader::getRedGrenadeSupplyAmmo() {
    return red_grenade_supply_ammo;
}

int ConfigLoader::getRedGrenadeMaxAmmo() {
    return red_grenade_max_ammo;
}

float ConfigLoader::getFragmentRadius() {
    return fragment_radius;
}

float ConfigLoader::getFragmentDamage() {
    return fragment_damage;
}

float ConfigLoader::getBananaRadius() {
    return banana_radius;
}

float ConfigLoader::getBananaDamage() {
    return banana_damage;
}

int ConfigLoader::getBananaSupplyAmmo() {
    return banana_supply_ammo;
}

float ConfigLoader::getBananaBounciness() {
    return banana_bounciness;
}

int ConfigLoader::getBananaMaxAmmo() {
    return banana_max_ammo;
}

float ConfigLoader::getBatDamage() {
    return bat_damage;
}

float ConfigLoader::getBatImpulseFactor() {
    return bat_impulse_factor;
}

int ConfigLoader::getBatSupplyAmmo() {
    return bat_supply_ammo;
}

int ConfigLoader::getBatMaxAmmo() {
    return bat_max_ammo;
}

float ConfigLoader::getHolyGrenadeRadius() {
    return holy_grenade_radius;
}

float ConfigLoader::getHolyGrenadeDamage() {
    return holy_grenade_damage;
}

int ConfigLoader::getHolyGrenadeSupplyAmmo() {
    return holy_grenade_supply_ammo;
}

int ConfigLoader::getHolyGrenadeMaxAmmo() {
    return holy_grenade_max_ammo;
}

float ConfigLoader::getDynamiteRadius() {
    return dynamite_radius;
}

float ConfigLoader::getDynamiteDamage() {
    return dynamite_damage;
}

int ConfigLoader::getDynamiteSupplyAmmo() {
    return dynamite_supply_ammo;
}

int ConfigLoader::getDynamiteMaxAmmo() {
    return dynamite_max_ammo;
}

int ConfigLoader::getAirAttackMissiles() {
    return air_attack_missiles;
}

int ConfigLoader::getAirAttackSupplyAmmo() {
    return air_attack_supply_ammo;
}

int ConfigLoader::getAirAttackMaxAmmo() {
    return air_attack_max_ammo;
}

float ConfigLoader::getAirAttackMissileRadius() {
    return air_attack_missile_radius;
}

float ConfigLoader::getAirAttackMissileDamage() {
    return air_attack_missile_damage;
}

int ConfigLoader::getTeleportSupplyAmmo() {
    return teleport_supply_ammo;
}

int ConfigLoader::getTeleportMaxAmmo() {
    return teleport_max_ammo;
}

float ConfigLoader::getSupplyBoxProbability() {
    return supply_box_probability;
}

float ConfigLoader::getSupplyBoxHealthProbability() {
    return supply_box_health_probability;
}

float ConfigLoader::getSupplyBoxAmmoProbability() {
    return supply_box_ammo_probability;
}

float ConfigLoader::getSupplyBoxTrapProbability() {
    return supply_box_trap_probability;
}

float ConfigLoader::getSupplyBoxHealth() {
    return supply_box_health;
}

float ConfigLoader::getSupplyBoxTrapRadius() {
    return supply_box_trap_radius;
}

float ConfigLoader::getSupplyBoxTrapDamage() {
    return supply_box_trap_damage;
}

float ConfigLoader::getMortarAmmoProbability() {
    return mortar_ammo_probability;
}

float ConfigLoader::getRedGrenadeAmmoProbability() {
    return red_grenade_ammo_probability;
}

float ConfigLoader::getBananaAmmoProbability() {
    return banana_ammo_probability;
}

float ConfigLoader::getTeleportAmmoProbability() {
    return teleport_ammo_probability;
}

float ConfigLoader::getBatAmmoProbability() {
    return bat_ammo_probability;
}

float ConfigLoader::getDynamiteAmmoProbability() {
    return dynamite_ammo_probability;
}

float ConfigLoader::getAirAttackAmmoProbability() {
    return air_attack_ammo_probability;
}

float ConfigLoader::getHolyGrenadeAmmoProbability() {
    return holy_grenade_ammo_probability;
}


