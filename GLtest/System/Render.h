#pragma once
#include <glm\glm.hpp>

#include <gl/GL/glew.h>
#include <gl/GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../glslprogram.h"

#include "Singleton.h"

#include "../Actor/Actor.h"

class Render : public Singleton<Render> {
public:
    friend class Singleton<Render>;//Singleton�ł̃C���X�^���X�쐬�͋���

public:
    Render();
    ~Render();

    void init();
    void resize(int, int);

    void DrawShadowMap();
    void DrawPass1();
    void DrawPass2();
private:
    void drawActor(int pass_index);
    void setMatrices();
    void setActorMatrix(Actor* actor);
    void resetActorMatrix();
    void compileAndLinkShader();
    void setFrameBuffer();
    void setWhiteTextureInfo();
    void setFullScreenQuad();
    void setDebugQuad();
private:
    int mWidth, mHeight;//�X�N���[���̃T�C�Y
    glm::mat4 mModel, mView, mProjection;
    mat4 mViewport;

    GLSLProgram prog;
    GLuint mPass1Index, mPass2Index, mShadowPassIndex;
    //shadow map
    GLuint mShadowFbo;
    int mShadowWidth, mShadowHeight;
    GLuint mDepthTex;
    //fbo
    GLuint mFboHandle;
    GLuint mRenderTexture;
    GLuint mDepthBuffer;
    GLuint mWhiteTexHandle;

    GLuint mFullScreenQuad;
    GLuint mDebugQuad[1];
};