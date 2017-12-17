#pragma once
#include <glm\glm.hpp>

#include <gl/GL/glew.h>
#include <gl/GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Model.h"

#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))

class Cube : public Model {
public:
	Cube();
	~Cube() {};

	void update();
private:
	virtual void setIndexInfo() override;
};