#pragma once
#include <gl/GL/glut.h>
#include <glm/glm.hpp>

class Camera {
public:
	Camera() {
		x = y = z = 0;
		mTargetPos = glm::vec3(0.f);
		y = 6;
		z = 3;
		spd = 1;
		perspective = glm::mat4(1.0f);
		view = glm::mat4(1.0f);
		angleH = 0;
		angleY = 30;
		fovy = 60;
	}

	void update();

	void lookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 up);
	void perspectiveMatrix(float left, float right, float bottom, float top, float near_val, float far_val);
	void cameraMatrix(float fovy, float aspect, float near_val, float far_val);

public:
	double x, y, z;
	glm::vec3 mTargetPos;
	float fovy;
	double angleH, angleY;
	double spd;
	glm::mat4 perspective;
	glm::mat4 view;
};