#pragma once

#include "../Model/Model.h"
#include <glm\glm.hpp>

class Actor {
public:
	Actor();

	virtual void update() {};
	virtual void render() const;

	void setModel(Model* model) {
		mModel = model;
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
	void setTranslation(const glm::vec3& rotate) {
		mRotation = rotate;
	}

private:
	glm::vec3 mPosition;
	glm::vec3 mScale;
	glm::vec3 mRotation;

	Model* mModel;
};