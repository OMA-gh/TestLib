
#include "Plane.h"

Plane::Plane() : Model() {
}

void Plane::setIndexInfo() {
	for (int i = 0; i < 4; i++) {
		glm::vec3 push_pos(
			i % 2 == 0 ? -1 : 1,
			0,
			i / 2 == 0 ? -1 : 1
		);
		mPositionArray.push_back(push_pos);
	}
	for (int i = 0; i < 4; i++) {
		glm::vec3 push_color(
			0.5f,
			i*0.1f,
			1 - i*0.1f
		);
		glm::vec3 push_normal(
			0.f,
			1.f,
			0.f
		);
		glm::vec2 push_texcoord(
			i % 2 == 0 ? 0 : 1,
			i / 2 == 0 ? 0 : 1
		);
		mColorArray.push_back(push_color);
		mNormalArray.push_back(push_normal);
		mTexCoordArray.push_back(push_texcoord);
	}

	const int index_array_size = 2 * 3;

	int push_index_array[6] = {
		0,3,1,
		0,2,3
	};
	for (int i = 0; i < 6; i++) {
		mIndexArray.push_back(push_index_array[i]);
	}
}

void Plane::update() {
	for (int i = 0; i < 8; i++) {
		//mPositionArray[i].z += 0.01;
	}
}

