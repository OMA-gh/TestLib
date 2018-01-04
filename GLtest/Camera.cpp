#include "Camera.h"
#include <cmath>

#define PI 3.14159265359

Camera *Camera::s_pInstance = nullptr;

void Camera::update() {
	if (angleH < 0)angleH += 360;
	if (angleH > 360)angleH -= 360;
	if (angleY < 0)angleY = 0;
	if (angleY > 90)angleY = 90;

	x = mTargetPos.x +cos(PI / 180 * angleH)*20.f;
	y = mTargetPos.y + sin(PI / 180 * angleY)*100.f;
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
}

glm::mat4 Camera::calcViewMatrix(glm::vec3 pos, glm::vec3 target, glm::vec3 up)
{
	glm::mat4 ret_mat(0);
	float l;
	GLfloat* matrix = &ret_mat[0][0];

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

	return ret_mat;
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

glm::mat4 Camera::calcPerspectiveMatrix(float fovy, float aspect, float near_val, float far_val)
{
	glm::mat4 ret_mat(0);
	float f = 1.0f / tanf(fovy * 0.5f * 3.141593f / 180.0f);
	float dz = far_val - near_val;
	GLfloat* matrix = &ret_mat[0][0];

	matrix[0] = f / aspect;
	matrix[5] = f;
	matrix[10] = -(far_val + near_val) / dz;
	matrix[11] = -1.0f;
	matrix[14] = -2.0f * far_val * near_val / dz;
	matrix[1] = matrix[2] = matrix[3] = matrix[4] =
		matrix[6] = matrix[7] = matrix[8] = matrix[9] =
		matrix[12] = matrix[13] = matrix[15] = 0.0f;

	return ret_mat;
}