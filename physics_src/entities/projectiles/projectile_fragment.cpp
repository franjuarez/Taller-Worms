#include "projectile_fragment.h"
#include <iostream>
ProjectileFragment::ProjectileFragment(b2Body* fatherBody, std::unordered_set<b2Body*>& entitiesToRemove,
 std::vector<createEntity>& entitiesToAdd, int id, float damage, float radius) : 
        InstantProjectile(fatherBody, entitiesToRemove, entitiesToAdd, id, damage, radius) { }

float randomFloat(float lower, float upper) {
   float random = ((float) std::rand()) / (float) RAND_MAX;
   float diff = upper - (lower);
   float r = random * diff;
   return lower + r;
}

b2Vec2 getNormal(b2Body* body){
    b2Vec2 normal = b2Vec2(1, 1);
    for(b2ContactEdge* ce = body->GetContactList(); ce; ce = ce->next){
        b2Contact* c = ce->contact;
        if(c->IsTouching()){
            normal = c->GetManifold()->localNormal;
        }
    }
    return normal;
}

b2Body* ProjectileFragment::createFragment(){
    b2Body* fatherBody = this->body;
    b2BodyDef frag_bd;
    frag_bd.type = b2_dynamicBody;
    b2Vec2 normal = getNormal(fatherBody);
    float noiseX = randomFloat(0, 1.0f);
    float noiseY = randomFloat(0, 1.0f);
    float posX = fatherBody->GetPosition().x + FRAGMENT_WIDTH/2.0 + (noiseX * normal.x);
    float posY = fatherBody->GetPosition().y + FRAGMENT_HEIGHT/2.0 + (noiseY * normal.y);
    frag_bd.position.Set(posX, posY);
    b2Body* fragment = fatherBody->GetWorld()->CreateBody(&frag_bd);
    this->body = fragment;
    fragment->SetBullet(true);
    b2FixtureDef fd;
    b2PolygonShape shape;
    shape.SetAsBox(FRAGMENT_WIDTH/2, FRAGMENT_HEIGHT/2);
    fd.shape = &shape;
    fd.density = 1.0f;
    fragment->CreateFixture(&fd);
    float noiseImpulseX = randomFloat(-1.0f, 1.0f);
    float noiseImpulseY = randomFloat(-1.0f, 1.0f);
    float impulseX = normal.x == 0 ? noiseImpulseX/15 : normal.x/15 * noiseImpulseX;
    float impulseY = normal.y == 0 ? noiseImpulseY/15 : normal.y/15 * noiseImpulseY;
    b2Vec2 impulse = b2Vec2(impulseX, impulseY);
    fragment->ApplyLinearImpulseToCenter(impulse, true);
    ProjectileFragment* fragmentEntity = this;
    fragment->GetUserData().pointer = reinterpret_cast<uintptr_t>(fragmentEntity);
    return fragment;
}

ProjectileFragment::~ProjectileFragment() {}

// ProjectileDTO ProjectileFragment::getDTO(){

