
#include "Line.h"

Line::Line() :
    mPositionArray()
    , mIndexArray()
{
}

void Line::init() {
    setIndexInfo();
    mPolygonNum = (int)mIndexArray.size() * sizeof(int);
    setVertexBufferObject();
}

void Line::setIndexInfo() {
    for (int i = 0; i < 3; i++) {
        glm::vec3 push_pos(
            i*5,
            i * 10,
            i*5
        );
        mPositionArray.push_back(push_pos);
    }
    for (int i = 0; i < 3; i++) {
        glm::vec3 push_color(
            1.0f,
            1.0f,
            1.0f
        );
        mColorArray.push_back(push_color);
    }
    mIndexArray.push_back(0);
    mIndexArray.push_back(1);
    mIndexArray.push_back(2);
}

void Line::setVertexBufferObject() {
    // Create and populate the buffer objects
    glGenVertexArrays(1, &mVaoHandle);
    glBindVertexArray(mVaoHandle);

    glGenBuffers(2, mVboHandleArray);
    GLuint positionBufferHandle = mVboHandleArray[0];
    GLuint colorBufferHandle = mVboHandleArray[1];

    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, mPositionArray.size() * sizeof(glm::vec3), &mPositionArray.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);
    glEnableVertexAttribArray(0);  // Vertex position

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, mColorArray.size() * sizeof(glm::vec3), &mColorArray.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);
    glEnableVertexAttribArray(1);  // Vertex color

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Line::render() const {
    glBindVertexArray(mVaoHandle);
    glDrawArrays(GL_LINES, 0, 3);
}
