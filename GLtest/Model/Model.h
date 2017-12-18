#pragma once
#include <glm\glm.hpp>

#include <gl/GL/glew.h>
#include <gl/GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <vector>

#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))

class Model {
public:
	Model();
	~Model() {};

    void init();
	void render() const;
	void setVertexBufferObject();

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

protected:
    virtual void setIndexInfo() {};

	std::vector<glm::vec3> mPositionArray;
	std::vector<glm::vec3> mColorArray;
	std::vector<glm::vec3> mNormalArray;
	std::vector<int> mIndexArray;
	int mPolygonNum;
	GLuint mVboHandleArray[4] = {};
	GLuint mVaoHandle;
};