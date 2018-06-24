#include "Manager.h"

Physics *Physics::s_pInstance = nullptr;

Physics::Physics() {
}
Physics::~Physics() {
}

void Physics::init() {
    mFoundationPtr = PxCreateFoundation(PX_FOUNDATION_VERSION, mAllocator, mErrorCallback);

    // PVD(PhysX Visual Debugger) setting. To use PVD, we need to build the project as Debug mode.
    mPvdPtr = PxCreatePvd(*mFoundationPtr);
    physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
    mPvdPtr->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

    mPhysicsPtr = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundationPtr, physx::PxTolerancesScale(), true, mPvdPtr);

    // Scene setting
    physx::PxSceneDesc sceneDesc(mPhysicsPtr->getTolerancesScale());
    sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);          // Right-hand coordinate system, Y-UP.
    mDispatcherPtr = physx::PxDefaultCpuDispatcherCreate(1);         // The number of worker threads is one.
    sceneDesc.cpuDispatcher = mDispatcherPtr;
    sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
    mScenePtr = mPhysicsPtr->createScene(sceneDesc);

    // PVD setting
    physx::PxPvdSceneClient* pvdClient = mScenePtr->getScenePvdClient();
    if (pvdClient)
    {
        pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
        pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
        pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
    }
}

void Physics::calc() {
    mScenePtr->simulate(1.0f / 60.0f);
    mScenePtr->fetchResults(true);
}

physx::PxRigidActor* Physics::CreateDynamic(const physx::PxTransform& t, const physx::PxGeometry& geometry, physx::PxMaterial& material) {
    physx::PxRigidDynamic* dynamic = physx::PxCreateDynamic(*mPhysicsPtr, t, geometry, material, 10.0f);
    mScenePtr->addActor(*dynamic);
    return dynamic;
}

physx::PxRigidActor* Physics::CreateStatic(const physx::PxTransform& t, const physx::PxGeometry& geometry, physx::PxMaterial& material) {
    physx::PxRigidStatic* static_actor = physx::PxCreateStatic(*mPhysicsPtr, t, geometry, material);
    mScenePtr->addActor(*static_actor);
    return static_actor;
}