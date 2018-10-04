#pragma once
#include <glm\glm.hpp>

#include <gl/GL/glew.h>
#include <gl/GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <vector>

#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))

class Line {
public:
    Line();
    ~Line() {
        glDeleteBuffers(3, mVboHandleArray);
        glDeleteBuffers(1, &mVaoHandle);    
    };

    void init();
    virtual void render() const;
    void setVertexBufferObject();

    std::vector<glm::vec3>* getPositionArrayPtr() {
        return &mPositionArray;
    }
    std::vector<glm::vec3>* getColorArrayPtr() {
        return &mColorArray;
    }

protected:
    virtual void setIndexInfo();

    std::vector<glm::vec3> mPositionArray;
    std::vector<glm::vec3> mColorArray;
    std::vector<int> mIndexArray;
    int mPolygonNum;
    GLuint mVboHandleArray[3] = {};
    GLuint mVaoHandle;
};