#include "Actor.h"
#include "../System/Manager.h"

Actor::Actor() 
	: mPosition(0.f)
	, mScale(0.f)
	, mRotation(0.f)
    , mName("")
    , mCount(0)
    , mIsThroughLight(false)
{	
};

void Actor::ConstructDynamicPhysicsActor(const physx::PxGeometry& geometry, physx::PxMaterial& material) {
    mPhysicsActorPtr = GET_INSTANCE(Physics)->CreateDynamic(physx::PxTransform(getPosition().x, getPosition().y, getPosition().z), geometry, material);
};
void Actor::ConstructStaticPhysicsActor(const physx::PxGeometry& geometry, physx::PxMaterial& material) {
    mPhysicsActorPtr = GET_INSTANCE(Physics)->CreateStatic(physx::PxTransform(getPosition().x, getPosition().y, getPosition().z), geometry, material);
};

void Actor::render() const {
	mModel->render();
}

void Actor::reflectBody()
{
    if (mPhysicsActorPtr != nullptr) {
        physx::PxVec3 pos(mPhysicsActorPtr->getWorldBounds().getCenter());
        setPosition(glm::vec3(pos.x, pos.y, pos.z));
    }
}