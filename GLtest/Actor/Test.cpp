#include "Test.h"
#include "../System/Manager.h"

Test::Test() : Actor() {
}

void Test::prepare() {
    setPosition(glm::vec3(0.f, 0.f, 0.f));
    setScale(glm::vec3(1.f));
    setRotation(glm::vec3(1.f, 0.f, 0.f));

    physx::PxMaterial* material = GET_INSTANCE(Physics)->getPhysicsPtr()->createMaterial(0.5f, 0.5f, 0.5f);
    ConstructStaticPhysicsActor(physx::PxBoxGeometry(100.0f, 0.001f, 100.0f), *material);
}

void Test::update() {

}