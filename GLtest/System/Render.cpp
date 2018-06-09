#include "Manager.h"
#include "../Camera.h"

Render *Render::s_pInstance = nullptr;

float PI = 3.141592653589f;

Render::Render() {
    mShadowWidth  = 512 * 8;
    mShadowHeight = 512 * 8;
}
Render::~Render() {

}

void Render::drawActor(int pass_index) {
    auto it = GET_INSTANCE(ActorMgr)->getActorArray().begin();
    auto end = GET_INSTANCE(ActorMgr)->getActorArray().end();
    for (; it != end; it++) {
        if (!(pass_index == 0 && it->second->isThroughLight())) {
            setActorMatrix(it->second.get());
            it->second->render();
        }
    }
}

void Render::DrawShadowMap() {
    Actor* test = GET_INSTANCE(ActorMgr)->getActorPtr("Test");
    Actor* light = GET_INSTANCE(ActorMgr)->getActorPtr("Light");
    // Pass1 (Shadow map)
    glBindFramebuffer(GL_FRAMEBUFFER, mShadowFbo);
    prog.setUniform("ShadowMap", 2);
    prog.setUniform("RenderTex", 0);
    glClear(GL_DEPTH_BUFFER_BIT);

    mModel = glm::mat4(1.f);
    mView = Camera::calcViewMatrix(light->getPosition(), glm::vec3(10, 8, 10), glm::vec3(0, 1, 0));
    mProjection = Camera::calcPerspectiveMatrix(60.0f, 1.0f, 0.1f, 1200.0f);
    this->resize(mShadowWidth, mShadowHeight);
    setMatrices();
    glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &mShadowPassIndex);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    drawActor(0);
    glDisable(GL_CULL_FACE);
}
void Render::DrawPass1() {
    // Pass2
    glBindFramebuffer(GL_FRAMEBUFFER, mFboHandle);
    prog.setUniform("ShadowMap", 2);
    prog.setUniform("RenderTex", 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mModel = glm::mat4(1.f);
    mView = GET_INSTANCE(Camera)->view;
    mProjection = GET_INSTANCE(Camera)->perspective;
    this->resize(960, 540);
    setMatrices();
    glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &mPass1Index);
    drawActor(1);
}
void Render::DrawPass2() {
    // Pass3
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    prog.setUniform("ShadowMap", 2);
    prog.setUniform("RenderTex", 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mModel = glm::mat4(1.f);
    mView = glm::mat4(1.f);
    mProjection = glm::mat4(1.f);
    mViewport = glm::mat4(1.f);
    setMatrices();
    glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &mPass2Index);
    glBindTexture(GL_TEXTURE_2D, mRenderTexture);
    //glBindTexture(GL_TEXTURE_2D, mDepthTex);
    glBindVertexArray(mFullScreenQuad);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    for (int i = 0; i < 1; i++) {
        glBindTexture(GL_TEXTURE_2D, mDepthTex);
        glBindVertexArray(mDebugQuad[0]);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}

void Render::init() {
    compileAndLinkShader();
    setFrameBuffer();
    setWhiteTextureInfo();
    setFullScreenQuad();
    setDebugQuad();

    mShadowPassIndex = glGetSubroutineIndex(prog.getHandle(), GL_FRAGMENT_SHADER, "recordDepth");
    mPass1Index = glGetSubroutineIndex(prog.getHandle(), GL_FRAGMENT_SHADER, "pass1");
    mPass2Index = glGetSubroutineIndex(prog.getHandle(), GL_FRAGMENT_SHADER, "pass2");

    prog.setUniform("Line.Width", 0.75f);
    prog.setUniform("Line.Color", vec4(0.05f, 0.0f, 0.05f, 1.0f));
    prog.setUniform("Material.Kd", 0.6f, 0.6f, 0.6f);
    prog.setUniform("Light.Ld", 1.0f, 1.0f, 1.0f);
    prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Light.La", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
    prog.setUniform("Light.Ls", 1.0f, 1.0f, 1.0f);
    prog.setUniform("Material.Shininess", 100.0f);
}

void Render::setMatrices()
{
    mat4 mv = mView * mModel;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("MVP", mProjection * mv);
    prog.setUniform("ViewportMatrix", mViewport);

    const glm::mat4 shadowBias = mat4(
        vec4(0.5f, 0.0f, 0.0f, 0.0f),
        vec4(0.0f, 0.5f, 0.0f, 0.0f),
        vec4(0.0f, 0.0f, 0.5f, 0.0f),
        vec4(0.5f, 0.5f, 0.5f, 1.0f)
    );

    glm::mat4 lightPV(0);
    Actor* light = GET_INSTANCE(ActorMgr)->getActorPtr("Light");
    prog.setUniform("Light.Position", glm::vec4(light->getPosition(), 1.f));
    mView = Camera::calcViewMatrix(light->getPosition(), glm::vec3(10, 8, 10), glm::vec3(0, 1, 0));
    mProjection = Camera::calcPerspectiveMatrix(60.0f, 1.0f, 0.1f, 1200.0f);
    lightPV = shadowBias * mProjection * mView;
    prog.setUniform("ShadowMatrix", lightPV * mModel);
}

void Render::setActorMatrix(Actor* actor) {
    prog.setUniform("ObjectPosition", actor->getPosition());
    prog.setUniform("ObjectScale", actor->getScale());
    prog.setUniform("ObjectRotation", actor->getRotation());
}

void Render::resetActorMatrix() {
    prog.setUniform("ObjectPosition", glm::vec3(0.f));
    prog.setUniform("ObjectScale", glm::vec3(1.f));
    prog.setUniform("ObjectRotation", glm::vec3(1.f, 0.f, 0.f));
}

void Render::compileAndLinkShader()
{
    if (!prog.compileShaderFromFile("shader/basic.vs", GLSLShader::VERTEX))
    {
        printf("Vertex shader failed to compile!\n%s",
            prog.log().c_str());
    }
    if (!prog.compileShaderFromFile("shader/basic.gs", GLSLShader::GEOMETRY))
    {
        printf("Geometry shader failed to compile!\n%s",
            prog.log().c_str());
    }
    if (!prog.compileShaderFromFile("shader/basic.fs", GLSLShader::FRAGMENT))
    {
        printf("Fragment shader failed to compile!\n%s",
            prog.log().c_str());
    }
    if (!prog.link())
    {
        printf("Shader program failed to link!\n%s",
            prog.log().c_str());
    }

    prog.use();

    prog.setUniform("ShadowMap", 2);
    prog.setUniform("RenderTex", 0);

    if (!prog.validate())
    {
        printf("Program failed to validate!\n%s",
            prog.log().c_str());
    }

}

void Render::setFrameBuffer() {
    GLfloat border[] = { 1.0f, 0.0f,0.0f,0.0f };

    // Create and set up the FBO
    glGenFramebuffers(1, &mShadowFbo);
    glBindFramebuffer(GL_FRAMEBUFFER, mShadowFbo);

    // The depth buffer texture
    glGenTextures(1, &mDepthTex);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, mDepthTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, mShadowWidth,
        mShadowHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LESS);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mDepthTex, 0);

    GLenum shadow_draw_buffers[] = { GL_NONE };
    glDrawBuffers(1, shadow_draw_buffers);

    // create and bind framebuffer
    glGenFramebuffers(1, &mFboHandle);
    glBindFramebuffer(GL_FRAMEBUFFER, mFboHandle);

    // create texture object
    glGenTextures(1, &mRenderTexture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mRenderTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 960, 540, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, mRenderTexture);

    //bind texture to fbo
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mRenderTexture, 0);

    //create depth buffer
    glGenRenderbuffers(1, &mDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, mDepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 960, 540);

    //bind depthbuffer to fbo
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthBuffer);

    //set fragment shader target
    GLenum draw_bufs[] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, draw_bufs);

    //unbind framebuffer
    GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (result == GL_FRAMEBUFFER_COMPLETE) {
        printf("Framebuffer is complete.\n");
    }
    else {
        printf("Framebuffer is not complete.\n");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Render::setWhiteTextureInfo() {
    // One pixel white texture
    GLubyte whiteTex[] = { 255, 255, 255, 255 };
    glActiveTexture(GL_TEXTURE1);
    glGenTextures(1, &mWhiteTexHandle);
    glBindTexture(GL_TEXTURE_2D, mWhiteTexHandle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, whiteTex);

    glActiveTexture(GL_TEXTURE0);
}

void Render::setFullScreenQuad() {
    // Array for full-screen quad
    GLfloat verts[] = {
        -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f
    };
    GLfloat tc[] = {
        0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };

    // Set up the buffers

    unsigned int handle[2];
    glGenBuffers(2, handle);

    glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
    glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(float), verts, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), tc, GL_STATIC_DRAW);

    // Set up the vertex array object

    glGenVertexArrays(1, &mFullScreenQuad);
    glBindVertexArray(mFullScreenQuad);

    glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));
    glEnableVertexAttribArray(0);  // Vertex position

    glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
    glVertexAttribPointer((GLuint)3, 2, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));
    glEnableVertexAttribArray(3);  // Texture coordinates

    glBindVertexArray(0);
}

void Render::setDebugQuad() {
    const int divide_num = 3;
    const float c_size = 1.f / divide_num;
    for (int i = 0; i < 1; i++) {
        float c_pos = -1.f / divide_num * (divide_num - 1) + 1.f / divide_num * i;
        GLfloat verts[] = {
            c_pos - c_size, c_pos - c_size, -0.001f,
            c_pos + c_size, c_pos - c_size, -0.001f,
            c_pos + c_size, c_pos + c_size, -0.001f,
            c_pos - c_size, c_pos - c_size, -0.001f,
            c_pos + c_size, c_pos + c_size, -0.001f,
            c_pos - c_size, c_pos + c_size, -0.001f
        };
        GLfloat tc[] = {
            0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
        };

        // Set up the buffers

        unsigned int handle[2];
        glGenBuffers(2, handle);

        glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
        glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(float), verts, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
        glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), tc, GL_STATIC_DRAW);

        // Set up the vertex array object

        glGenVertexArrays(1, &mDebugQuad[i]);
        glBindVertexArray(mDebugQuad[i]);

        glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
        glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));
        glEnableVertexAttribArray(0);  // Vertex position

        glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
        glVertexAttribPointer((GLuint)3, 2, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));
        glEnableVertexAttribArray(3);  // Texture coordinates

        glBindVertexArray(0);
    }
}

void Render::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    mWidth = w;
    mHeight = h;

    float w2 = mWidth / 2.0f;
    float h2 = mHeight / 2.0f;
    mViewport = mat4(vec4(w2, 0.0f, 0.0f, 0.0f),
        vec4(0.0f, h2, 0.0f, 0.0f),
        vec4(0.0f, 0.0f, 1.0f, 0.0f),
        vec4(w2 + 0, h2 + 0, 0.0f, 1.0f));
}
