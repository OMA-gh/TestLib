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
        physx::PxShape* shapes[1];
        mPhysicsActorPtr->getShapes(shapes, mPhysicsActorPtr->getNbShapes());
        for (int i = 0; i < 1; i++) {
            const physx::PxMat44 shapePose(physx::PxShapeExt::getGlobalPose(*shapes[i], *mPhysicsActorPtr));
            mRotation = glm::mat4(
                shapePose[0][0], shapePose[0][1], shapePose[0][2], shapePose[0][3],
                shapePose[1][0], shapePose[1][1], shapePose[1][2], shapePose[1][3],
                shapePose[2][0], shapePose[2][1], shapePose[2][2], shapePose[2][3],
                shapePose[3][0], shapePose[3][1], shapePose[3][2], shapePose[3][3]
                );
        }
        physx::PxVec3 pos(mPhysicsActorPtr->getWorldBounds().getCenter());
        setPosition(glm::vec3(pos.x, pos.y, pos.z));
    }
}