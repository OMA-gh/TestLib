#include "Simple.h"
#include "../System/Manager.h"

Simple::Simple() : Actor() {
}

void Simple::prepare() {
    //setPosition(getPosition() + glm::vec3(0.f, 0.f, 0.f));
    setPosition(glm::vec3( 0.f, 5.f, 0.f));
    //setScale(getScale() + glm::vec3(0.01f, 0.01f, 0.01f));
    setScale(glm::vec3(1.f));
    setRotation(glm::mat4(1.f));

    physx::PxMaterial* material = GET_INSTANCE(Physics)->getPhysicsPtr()->createMaterial(0.5f, 0.5f, 0.5f);
    ConstructDynamicPhysicsActor(physx::PxBoxGeometry(1.0f, 1.9f, 1.0f), *material);
}

void Simple::update() {
}

void Simple::reflectBody() {
    Actor::reflectBody();
    
    const glm::mat4 rotationMatrix = glm::mat4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    mRotation = mRotation* rotationMatrix;

    const glm::vec3 d_pos(0.f, 0.4f, 0.f);
    mPosition += d_pos;
}