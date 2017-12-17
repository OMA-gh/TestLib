
#include "Model.h"

Model::Model() :
	mPositionArray()
	, mColorArray()
	, mNormalArray()
	, mIndexArray()
{
}
/*
void Model::setIndexInfo() {
	auto& position_array =

		for (int k = 0; k < 2; k++) {
			for (int i = 0; i < 4; i++) {
				mPositionArray[i + k * 4].x = i / 2 == 0 ? -1 : 1;
				mPositionArray[i + k * 4].y = 7 + (k == 0 ? 1 : -1);
				mPositionArray[i + k * 4].z = i % 2 == 0 ? -1 : 1;
			}
		}
	for (int i = 0; i < 8; i++) {
		mColorArray[i].x = 0.5f;
		mColorArray[i].y = i*0.1f;
		mColorArray[i].z = 1 - i*0.1f;

		mNormalArray[i].x = mPositionArray[i].x;
		mNormalArray[i].y = mPositionArray[i].y - 7;
		mNormalArray[i].z = mPositionArray[i].z;
	}

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

}
*/
void Model::setVertexBufferObject() {
	// Create and populate the buffer objects
	glGenVertexArrays(1, &mVaoHandle);
	glBindVertexArray(mVaoHandle);

	glGenBuffers(4, mVboHandleArray);
	GLuint positionBufferHandle = mVboHandleArray[0];
	GLuint normalBufferHandle = mVboHandleArray[1];
	GLuint colorBufferHandle = mVboHandleArray[2];
	GLuint indexBufferHandle = mVboHandleArray[3];

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, mPositionArray.size() * sizeof(glm::vec3), &mPositionArray.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);
	glEnableVertexAttribArray(0);  // Vertex position

	glBindBuffer(GL_ARRAY_BUFFER, normalBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, mNormalArray.size() * sizeof(glm::vec3), &mNormalArray.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);
	glEnableVertexAttribArray(1);  // Vertex normal

	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, mColorArray.size() * sizeof(glm::vec3), &mColorArray.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);
	glEnableVertexAttribArray(2);  // Vertex color

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndexArray.size() * sizeof(int), &mIndexArray.front(), GL_STATIC_DRAW);

	glBindVertexArray(0);

}

void Model::render() {
	glBindVertexArray(mVaoHandle);
	glDrawElements(GL_TRIANGLES, mIndexArray.size() * sizeof(int), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
}
