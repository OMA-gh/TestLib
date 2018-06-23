#pragma once
#include <glm\glm.hpp>

#include <gl/GL/glew.h>
#include <gl/GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../Dependencies/SOIL2/SOIL2.h"

#include <vector>

//#include "../System/Manager.h"
#include "Texture.h"

#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))

class Model {
public:
	Model();
	~Model() {};

    void init();
	virtual void render() const;
	void setVertexBufferObject();
	void setTextureInfo(Texture* texture);

	std::vector<glm::vec3>* getPositionArrayPtr() {
		return &mPositionArray;
	}
	std::vector<glm::vec3>* getColorArrayPtr() {
		return &mColorArray;
	}
	std::vector<glm::vec3>* getNormalArrayPtr() {
		return &mNormalArray;
	}
	std::vector<int>* getIndexArrayPtr() {
		return &mIndexArray;
	}
	Texture* getTexturePtr() {
		return mpTexture;
	}
    std::string& getTextureName() {
        return mTextureName;
    }

protected:
    virtual void setIndexInfo() {};

	std::vector<glm::vec3> mPositionArray;
	std::vector<glm::vec3> mColorArray;
	std::vector<glm::vec3> mNormalArray;
	std::vector<glm::vec2> mTexCoordArray;
	std::vector<int> mIndexArray;
	Texture* mpTexture;
	std::string mTextureName;
	int mPolygonNum;
	GLuint mVboHandleArray[5] = {};
	GLuint mVaoHandle;
};