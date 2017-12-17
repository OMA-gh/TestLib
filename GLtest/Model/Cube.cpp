
#include "Cube.h"

Cube::Cube() : Model() {
	setIndexInfo();
}

void Cube::setIndexInfo() {
	//position_array->resize(size_t(8));
	//color_array->resize(size_t(8));
	//normal_array->resize(size_t(8));

	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < 4; i++) {
			glm::vec3 push_pos(
				i / 2 == 0 ? -1 : 1,
				(k == 0 ? 1 : -1),
				i % 2 == 0 ? -1 : 1
			);
			mPositionArray.push_back(push_pos);
			/*
			mPositionArray[i + k * 4].x = i / 2 == 0 ? -1 : 1;
			mPositionArray[i + k * 4].y = 7+(k == 0 ? 1 : -1);
			mPositionArray[i + k * 4].z = i % 2 == 0 ? -1 : 1;
			*/
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

		/*
		mColorArray[i].x = 0.5f;
		mColorArray[i].y = i*0.1f;
		mColorArray[i].z = 1 - i*0.1f;

		mNormalArray[i].x = mPositionArray[i].x;
		mNormalArray[i].y = mPositionArray[i].y-7;
		mNormalArray[i].z = mPositionArray[i].z;
		*/
	}

	const int index_array_size = 6 * 2 * 3;
	setPolygonNum(index_array_size);
	//index_array->resize(index_array_size);

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
	/*
	int i = 0;
	i = 0; mIndexArray[i * 3] = 0;	mIndexArray[i * 3 + 1] = 1;	mIndexArray[i * 3 + 2] = 2;
	i = 1; mIndexArray[i * 3] = 1;	mIndexArray[i * 3 + 1] = 3;	mIndexArray[i * 3 + 2] = 2;

	i = 2; mIndexArray[i * 3] = 1;	mIndexArray[i * 3 + 1] = 5;	mIndexArray[i * 3 + 2] = 3;
	i = 3; mIndexArray[i * 3] = 5;	mIndexArray[i * 3 + 1] = 7;	mIndexArray[i * 3 + 2] = 3;
	
	i = 4; mIndexArray[i * 3] = 3;	mIndexArray[i * 3 + 1] = 7;	mIndexArray[i * 3 + 2] = 2;
	i = 5; mIndexArray[i * 3] = 7;	mIndexArray[i * 3 + 1] = 6;	mIndexArray[i * 3 + 2] = 2;
	
	i = 6; mIndexArray[i * 3] = 2;	mIndexArray[i * 3 + 1] = 6;	mIndexArray[i * 3 + 2] = 0;
	i = 7; mIndexArray[i * 3] = 6;	mIndexArray[i * 3 + 1] = 4;	mIndexArray[i * 3 + 2] = 0;

	i = 8; mIndexArray[i * 3] = 0;	mIndexArray[i * 3 + 1] = 4;	mIndexArray[i * 3 + 2] = 1;
	i = 9; mIndexArray[i * 3] = 4;	mIndexArray[i * 3 + 1] = 5;	mIndexArray[i * 3 + 2] = 1;

	i = 10; mIndexArray[i * 3] = 7;	mIndexArray[i * 3 + 1] = 6;	mIndexArray[i * 3 + 2] = 5;
	i = 11; mIndexArray[i * 3] = 6;	mIndexArray[i * 3 + 1] = 4;	mIndexArray[i * 3 + 2] = 5;
	*/
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

