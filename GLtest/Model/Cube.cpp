
#include "Cube.h"

Cube::Cube() : Model() {
}

void Cube::setIndexInfo() {
	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < 4; i++) {
			glm::vec3 push_pos(
				i / 2 == 0 ? -1 : 1,
				(k == 0 ? 1 : -1),
				i % 2 == 0 ? -1 : 1
			);
			mPositionArray.push_back(push_pos);
		}
	}
	for (int i = 0; i < 8; i++) {
		glm::vec3 push_color(
			0.5f,
			i*0.1f,
			1 - i*0.1f
		);
		glm::vec3 push_normal(
			mPositionArray[i].x,
			mPositionArray[i].y,
			mPositionArray[i].z
		);
		mColorArray.push_back(push_color);
		mNormalArray.push_back(push_normal);
	}

	const int index_array_size = 6 * 2 * 3;

	int push_index_array[36] = {
		0,1,2,
		1,3,2,
		1,5,3,
		5,7,3,
		3,7,2,
		7,6,2,
		2,6,0,
		6,4,0,
		0,4,1,
		4,5,1,
		7,6,5,
		6,4,5
	};
	for (int i = 0; i < 36; i++) {
		mIndexArray.push_back(push_index_array[i]);
	}
}

void Cube::update() {
	for (int i = 0; i < 8; i++) {
		//mPositionArray[i].z += 0.01;
	}
	int hoge[36] = {};
	printf("pos size:%d, default:%d\n", sizeof(mPositionArray), sizeof(hoge));
	printf("index size:%d,%d\n", sizeof(mIndexArray),sizeof(int));
	printf("-------------------------\n");
}

