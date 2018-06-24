#pragma once

#include "../Model/Model.h"
#include <glm\glm.hpp>
#include <PxPhysics.h>

class Actor {
public:
	Actor();

    virtual void prepare() {};
    virtual void update() { printf("WARNING|基底アクターのupdateです。\n"); };
	virtual void render() const;

    void reflectBody();

	void setModel(const Model* const model) {
		mModel = model;
	}
	const Model* const getModelPtr() {
		return mModel;
	}

	const glm::vec3& getPosition() const{
		return mPosition;
	}
	void setPosition(const glm::vec3& pos) {
		mPosition = pos;
	}
	const glm::vec3& getScale() const {
		return mScale;
	}
	void setScale(const glm::vec3& scale) {
		mScale = scale;
	}
	const glm::mat4& getRotation() const {
		return mRotation;
	}
	void setRotation(const glm::mat4& rotate) {
		mRotation = rotate;
	}
    const std::string& getName() const {
        return mName;
    }
    void setName(std::string& name) {
        mName = name;
    }
    bool isThroughLight() {
        return mIsThroughLight;
    }

protected:
    void ConstructDynamicPhysicsActor(const physx::PxGeometry& geometry, physx::PxMaterial& material);
    void ConstructStaticPhysicsActor(const physx::PxGeometry& geometry, physx::PxMaterial& material);

protected:
	glm::vec3 mPosition;
	glm::vec3 mScale;
	glm::mat4 mRotation;
    std::string mName;
    int mCount;
    bool mIsThroughLight;

	const Model* mModel;
    physx::PxRigidActor* mPhysicsActorPtr;
};