
#include "Model.h"

Model::Model() :
	mPositionArray()
	, mColorArray()
	, mNormalArray()
	, mIndexArray()
{
}

void Model::init() {
    setIndexInfo();
    mPolygonNum = mIndexArray.size() * sizeof(int);
    setVertexBufferObject();
}

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
	glDrawElements(GL_TRIANGLES, mPolygonNum, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
}
