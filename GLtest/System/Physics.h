#pragma once

#include "Singleton.h"

#include <PxPhysicsAPI.h>

class Physics : public Singleton<Physics> {
public:
    friend class Singleton<Physics>;//Singletonでのインスタンス作成は許可

public:
    Physics();
    ~Physics();

    const physx::PxPhysics& getPhysics() {
        return *mPhysicsPtr;
    }
    physx::PxPhysics* getPhysicsPtr() {
        return mPhysicsPtr;
    }
    physx::PxScene* getScenePtr() {
        return mScenePtr;
    }

    void init();
    void calc();

    physx::PxActor* CreateDynamic(const physx::PxTransform& t, const physx::PxGeometry& geometry, physx::PxMaterial& material);
    physx::PxActor* CreateStatic(const physx::PxTransform& t, const physx::PxGeometry& geometry, physx::PxMaterial& material);

private:
    physx::PxDefaultAllocator mAllocator;
    physx::PxDefaultErrorCallback mErrorCallback;
    physx::PxFoundation* mFoundationPtr;
    physx::PxPhysics* mPhysicsPtr;
    physx::PxDefaultCpuDispatcher* mDispatcherPtr;
    physx::PxScene* mScenePtr;
    physx::PxPvd* mPvdPtr;
};