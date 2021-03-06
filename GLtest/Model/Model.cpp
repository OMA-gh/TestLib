
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
    mPolygonNum = (int)mIndexArray.size() * sizeof(int);
    setVertexBufferObject();
}

void Model::setVertexBufferObject() {
	// Create and populate the buffer objects
	glGenVertexArrays(1, &mVaoHandle);
	glBindVertexArray(mVaoHandle);

	glGenBuffers(5, mVboHandleArray);
	GLuint positionBufferHandle = mVboHandleArray[0];
	GLuint normalBufferHandle = mVboHandleArray[1];
	GLuint colorBufferHandle = mVboHandleArray[2];
	GLuint texcoordBufferHandle = mVboHandleArray[3];
	GLuint indexBufferHandle = mVboHandleArray[4];

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

	glBindBuffer(GL_ARRAY_BUFFER, texcoordBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, mTexCoordArray.size() * sizeof(glm::vec2), &mTexCoordArray.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);
	glEnableVertexAttribArray(3);  // Vertex texcoord

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndexArray.size() * sizeof(int), &mIndexArray.front(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}
void Model::setTextureInfo(Texture* texture){
	//Set Texture
    //mpTexture = GET_INSTANCE(TextureMgr)->load(mTextureName);
    mpTexture = texture;
    glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, mpTexture->getTextureIdPtr());
	glBindTexture(GL_TEXTURE_2D, mpTexture->getTextureId());
	glTexImage2D(
		GL_TEXTURE_2D, 0, mpTexture->getColorType(),
		mpTexture->getWidth(), mpTexture->getHeight(),
		0, mpTexture->getColorType(), GL_UNSIGNED_BYTE,
		mpTexture->getImageBitsPtr()
	);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void Model::render() const{
	glBindTexture(GL_TEXTURE_2D, mpTexture->getTextureId());
	glBindVertexArray(mVaoHandle);
	glDrawElements(GL_TRIANGLES, mPolygonNum, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
}
