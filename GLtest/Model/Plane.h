#pragma once
#include <glm\glm.hpp>

#include <gl/GL/glew.h>
#include <gl/GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Model.h"

class Plane : public Model {
public:
	Plane();
	~Plane() {};

	void update();
private:
	virtual void setIndexInfo() override;
};