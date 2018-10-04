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
    friend class Singleton<Render>;//Singletonでのインスタンス作成は許可

public:
    Render();
    ~Render();

    void init();
    void resize(int, int);

    void DrawShadowMap();
    void DrawPass1();
    void DrawPass2();
    void DrawDebugLine();
private:
    void drawActor(int pass_index);
    void drawCollision_();
    void setMatrices();
    void setActorMatrix(const Actor& actor);
    void resetActorMatrix();
    void compileAndLinkShader();
    void setFrameBuffer();
    void setWhiteTextureInfo();
    void setFullScreenQuad();
    void setDebugQuad();
private:
    int mWidth, mHeight;//スクリーンのサイズ
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