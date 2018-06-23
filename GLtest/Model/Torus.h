#pragma once
#include <glm\glm.hpp>

#include <gl/GL/glew.h>
#include <gl/GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Model.h"

class Torus : public Model {
public:
    Torus();
    ~Torus() {};

    void update();
    virtual void render() const override;
private:
    virtual void setIndexInfo() override;
};