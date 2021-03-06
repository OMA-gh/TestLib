#pragma once
#include <glm\glm.hpp>

#include <gl/GL/glew.h>
#include <gl/GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Model.h"

#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))

#define FIELD_SIZE 40 // 辺の長さ
#define SIZE 250 // 分割数
#define GRID_SIZE SIZE*SIZE

class Terrain : public Model{
public:
	Terrain();
	~Terrain() {};

private:
	virtual void setIndexInfo() override;
};