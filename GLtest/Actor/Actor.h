#pragma once

#include "../Model/Model.h"
#include <glm\glm.hpp>

class Actor {
public:
	Actor();

    virtual void update() { printf("WARNING|基底アクターのupdateです。\n"); };
	virtual void render() const;

	void setModel(Model* model) {
		mModel = model;
	}
	Model* getModelPtr() {
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
	const glm::vec3& getRotation() const {
		return mRotation;
	}
	void setRotation(const glm::vec3& rotate) {
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
	glm::vec3 mPosition;
	glm::vec3 mScale;
	glm::vec3 mRotation;
    std::string mName;
    int mCount;
    bool mIsThroughLight;

	Model* mModel;
};