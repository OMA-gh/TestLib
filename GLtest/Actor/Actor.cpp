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

void Actor::prepare(CreateArg& arg) {
    //setPosition(getPosition() + glm::vec3(0.f, 0.f, 0.f));
    setPosition(glm::vec3(0.f, 5.f, 0.f));
    //setScale(getScale() + glm::vec3(0.01f, 0.01f, 0.01f));
    setScale(glm::vec3(1.f));
    setRotation(glm::mat4(1.f));

    physx::PxMaterial* material = GET_INSTANCE(Physics)->getPhysicsPtr()->createMaterial(0.5f, 0.5f, 0.5f);
    ConstructDynamicPhysicsActor(physx::PxBoxGeometry(1.0f, 1.9f, 1.0f), *material);
}

void Actor::SetPhysicsActor(PhysicsArg& arg) {
    physx::PxMaterial* material = GET_INSTANCE(Physics)->getPhysicsPtr->createMaterial(arg.centerPos);
    switch (arg.physicsType) {
    case PhysicsType::Box:
        ConstructDynamicPhysicsActor(physx::PxBoxGeometry(arg.scale.x, arg.scale.y, arg.scale.z), *material);
        break;
    case PhysicsType::Sphere:
        ConstructDynamicPhysicsActor(physx::PxSphereGeometry(), *material);
        break;
    default:
        printf("‘¶Ý‚µ‚È‚¢PhysicsType‚Å‚·");
        break;
    }
}

void Actor::ConstructDynamicPhysicsActor(const physx::PxGeometry& geometry, physx::PxMaterial& material) {
    mPhysicsActorPtr = GET_INSTANCE(Physics)->CreateDynamic(physx::PxTransform(getPosition().x, getPosition().y, getPosition().z), geometry, material);
};
void Actor::ConstructDynamicPhysicsActor(const physx::PxTransform& transform, const physx::PxGeometry& geometry, physx::PxMaterial& material) {
    mPhysicsActorPtr = GET_INSTANCE(Physics)->CreateDynamic(transform, geometry, material);
};
void Actor::ConstructStaticPhysicsActor(const physx::PxGeometry& geometry, physx::PxMaterial& material) {
    mPhysicsActorPtr = GET_INSTANCE(Physics)->CreateStatic(physx::PxTransform(getPosition().x, getPosition().y, getPosition().z), geometry, material);
};
void Actor::ConstructStaticPhysicsActor(const physx::PxTransform& transform, const physx::PxGeometry& geometry, physx::PxMaterial& material) {
    mPhysicsActorPtr = GET_INSTANCE(Physics)->CreateStatic(transform, geometry, material);
};

void Actor::render() const {
	mModel->render();
}

void Actor::renderCollision() const {
    glLineWidth(2.5);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(getPosition().x, getPosition().y, getPosition().z);
    glVertex3f(getPosition().x, getPosition().y+1, getPosition().z);
    glEnd();
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