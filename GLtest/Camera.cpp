#include "Camera.h"
#include <cmath>

#define PI 3.14159265359

void Camera::update() {
	if (angleH < 0)angleH += 360;
	if (angleH > 360)angleH -= 360;
	if (angleY < 0)angleY = 0;
	if (angleY > 90)angleY = 90;

	x = mTargetPos.x +cos(PI / 180 * angleH)*20.f;
	y = mTargetPos.y + sin(PI / 180 * angleY)*20.f;
	z = mTargetPos.z +sin(PI / 180 * angleH)*20.f;

	cameraMatrix(fovy, 960 / 540, 0.1f, 200.0f);
	// カメラ行列
	lookAt(
		glm::vec3(x, y, z), // ワールド空間でカメラは(4,3,3)にあります。
		mTargetPos, // 
		glm::vec3(0, 1, 0)  // 頭が上方向(0,-1,0にセットすると上下逆転します。)
	);
}

void Camera::lookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 up)
{
	float l;
	GLfloat* matrix = &view[0][0];

	/* z �� = e - t */
	target.x = pos.x - target.x;
	target.y = pos.y - target.y;
	target.z = pos.z - target.z;
	l = sqrtf(target.x * target.x + target.y * target.y + target.z * target.z);
	matrix[2] = target.x / l;
	matrix[6] = target.y / l;
	matrix[10] = target.z / l;

	/* x �� = up. x z �� */
	target.x = up.y * matrix[10] - up.z * matrix[6];
	target.y = up.z * matrix[2] - up.x * matrix[10];
	target.z = up.x * matrix[6] - up.y * matrix[2];
	l = sqrtf(target.x * target.x + target.y * target.y + target.z * target.z);
	matrix[0] = target.x / l;
	matrix[4] = target.y / l;
	matrix[8] = target.z / l;

	/* y �� = z �� x x �� */
	matrix[1] = matrix[6] * matrix[8] - matrix[10] * matrix[4];
	matrix[5] = matrix[10] * matrix[0] - matrix[2] * matrix[8];
	matrix[9] = matrix[2] * matrix[4] - matrix[6] * matrix[0];

	/* ���s�ړ� */
	matrix[12] = -(pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8]);
	matrix[13] = -(pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9]);
	matrix[14] = -(pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10]);

	/* �c�� */
	matrix[3] = matrix[7] = matrix[11] = 0.0f;
	matrix[15] = 1.0f;
	/*
	target.x = pos.x - target.x;
	target.y = pos.y - target.y;
	target.z = pos.z - target.z;
	l = sqrtf(target.x * target.x + target.y * target.y + target.z * target.z);
	view[0][2] = target.x / l;
	view[1][2] = target.y / l;
	view[2][2] = target.z / l;

	target.x = up.y * view[2][2] - up.z * view[1][2];
	target.y = up.z * view[0][2] - up.x * view[2][2];
	target.z = up.x * view[1][2] - up.y * view[0][2];
	l = sqrtf(target.x * target.x + target.y * target.y + target.z * target.z);
	view[0][0] = target.x / l;
	view[1][0] = target.y / l;
	view[2][0] = target.z / l;

	view[0][1] = view[1][2] * view[2][0] - view[2][2] * view[1][0];
	view[1][1] = view[2][2] * view[0][0] - view[0][2] * view[2][0];
	view[2][1] = view[0][2] * view[1][0] - view[1][2] * view[0][0];

	view[3][0] = -(pos.x * view[0][0] + pos.y * view[1][0] + pos.z * view[2][0]);
	view[3][1] = -(pos.x * view[0][1] + pos.y * view[1][1] + pos.z * view[2][1]);
	view[3][2] = -(pos.x * view[0][2] + pos.y * view[1][2] + pos.z * view[2][2]);

	view[0][3] = view[1][3] = view[2][3] = 0.0f;
	view[3][3] = 1.0f;
	*/
}

void Camera::perspectiveMatrix(float left, float right,	float bottom, float top,float near_val, float far_val)
{
	float dx = right - left;
	float dy = top - bottom;
	float dz = far_val - near_val;

	perspective[0][0] = 2.0f * near_val / dx;
	perspective[1][1] = 2.0f * near_val / dy;
	perspective[2][0] = (right + left) / dx;
	perspective[2][1] = (top + bottom) / dy;
	perspective[2][2] = -(far_val + near_val) / dz;
	perspective[2][3] = -1.0f;
	perspective[3][2] = -2.0f * far_val * near_val / dz;
	perspective[0][1] = perspective[0][2] = perspective[0][3] = perspective[1][0] =
		perspective[1][2] = perspective[1][3] = perspective[3][0] = perspective[3][1] = perspective[3][3] = 0.0f;
}

void Camera::cameraMatrix(float fovy, float aspect, float near_val, float far_val)
{
	float f = 1.0f / tanf(fovy * 0.5f * 3.141593f / 180.0f);
	float dz = far_val - near_val;
	GLfloat* matrix = &perspective[0][0];

	matrix[0] = f / aspect;
	matrix[5] = f;
	matrix[10] = -(far_val + near_val) / dz;
	matrix[11] = -1.0f;
	matrix[14] = -2.0f * far_val * near_val / dz;
	matrix[1] = matrix[2] = matrix[3] = matrix[4] =
		matrix[6] = matrix[7] = matrix[8] = matrix[9] =
		matrix[12] = matrix[13] = matrix[15] = 0.0f;
}
