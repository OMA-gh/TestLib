#include "Test.h"
#include "../System/Manager.h"

Test::Test() : Actor() {
}

void Test::prepare() {
    setPosition(glm::vec3(0.f, 0.f, 0.f));
    setScale(glm::vec3(1.f));
    setRotation(glm::mat4(1.f));

    physx::PxMaterial* material = GET_INSTANCE(Physics)->getPhysicsPtr()->createMaterial(0.5f, 0.5f, 0.5f);
    ConstructStaticPhysicsActor(physx::PxBoxGeometry(20.0f, 0.001f, 20.0f), *material);
}

void Test::update() {

}