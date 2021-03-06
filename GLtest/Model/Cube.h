#pragma once
#include <glm\glm.hpp>

#include <gl/GL/glew.h>
#include <gl/GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Model.h"

class Cube : public Model {
public:
	Cube();
	~Cube() {};

	void update();
private:
	virtual void setIndexInfo() override;
};