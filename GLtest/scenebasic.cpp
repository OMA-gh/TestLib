﻿#include <glm\glm.hpp>
#include "scenebasic.h"

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <fstream>
using std::ifstream;
#include <sstream>
using std::ostringstream;

#include "glutils.h"

#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))

static GLuint index_buffer;

float PI = 3.141592653589f;

SceneBasic::SceneBasic()
	:mTerrain()
	,mCube()
	,mTest()
	,mLight()
{
}

void SceneBasic::initScene()
{
	compileAndLinkShader();
	setFrameBuffer();
	setWhiteTextureInfo();
	
	prog.setUniform("Line.Width", 0.75f);
	prog.setUniform("Line.Color", vec4(0.05f, 0.0f, 0.05f, 1.0f));
	prog.setUniform("Material.Kd", 0.6f, 0.6f, 0.6f);
	prog.setUniform("Light.Ld", 1.0f, 1.0f, 1.0f);
	prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
	prog.setUniform("Light.La", 0.4f, 0.4f, 0.4f);
	prog.setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
	prog.setUniform("Light.Ls", 1.0f, 1.0f, 1.0f);
	prog.setUniform("Material.Shininess", 100.0f);

	mPlane.init();
    mCube.init();
    mTerrain.init();

	mTest.setModel(&mPlane);
	mLight.setModel(&mCube);
}

void SceneBasic::setFrameBuffer() {
	// create and bind framebuffer
	glGenFramebuffers(1, &mFboHandle);
	glBindFramebuffer(GL_FRAMEBUFFER, mFboHandle);

	// create texture object
	glGenTextures(1, &mRenderTexture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mRenderTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//bind texture to fbo
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mRenderTexture, 0);

	//create depth buffer
	glGenRenderbuffers(1, &mDepthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, mDepthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 512, 512);

	//bind depthbuffer to fbo
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthBuffer);

	//set fragment shader target
	mDrawBufs[0] = GL_COLOR_ATTACHMENT0;
	glDrawBuffers(1, mDrawBufs);

	//unbind framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SceneBasic::setWhiteTextureInfo() {
	// One pixel white texture
	GLubyte whiteTex[] = { 255, 255, 255, 255 };
	glActiveTexture(GL_TEXTURE1);
	glGenTextures(1, &mWhiteTexHandle);
	glBindTexture(GL_TEXTURE_2D, mWhiteTexHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, whiteTex);
}

void SceneBasic::setMatrices()
{
	static int count = 0;
	glm::vec3 light_pos;
	light_pos = glm::vec3(FIELD_SIZE / 2 * (1 + cos(PI / 180 * count)), 10, FIELD_SIZE / 2 * (1 + sin(PI / 180 * count)));
	//light_pos = glm::vec3(0.f, 0.f, 0.f);
	mLight.setPosition(light_pos);
	mLight.setScale(glm::vec3(1.f));
	prog.setUniform("Light.Position", light_pos.x, light_pos.y, light_pos.z,1.f);

	glm::mat4 model = glm::mat4(1.0f);  // 各モデルを変える！
	mat4 mv = getCamera().view * model;
	prog.setUniform("ModelViewMatrix", mv);
	prog.setUniform("NormalMatrix",
		mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
	prog.setUniform("MVP",getCamera().perspective * mv);
	prog.setUniform("ViewportMatrix", viewport);

	count++;
	if (count > 360) {
		count -= 360;
	}
}

void SceneBasic::setActorMatrix(Actor* actor) {
	prog.setUniform("ObjectPosition", actor->getPosition());
	prog.setUniform("ObjectScale", actor->getScale());
	prog.setUniform("ObjectRotation", actor->getRotation());
}

void SceneBasic::resetActorMatrix() {
	prog.setUniform("ObjectPosition", glm::vec3(0.f));
	prog.setUniform("ObjectScale", glm::vec3(1.f));
	prog.setUniform("ObjectRotation", glm::vec3(1.f, 0.f, 0.f));
}

void SceneBasic::compileAndLinkShader()
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

	if (!prog.validate())
	{
		printf("Program failed to validate!\n%s",
			prog.log().c_str());
	}

	prog.use();
}

void SceneBasic::update( float t )
{
	mCamera.update();

	mTest.update();
}

void SceneBasic::render()
{
	setMatrices();

	/* 頂点データ，法線データ，テクスチャ座標の配列を有効にする */
	glEnableClientState(GL_VERTEX_ARRAY);

	glBindFramebuffer(GL_FRAMEBUFFER, mFboHandle);
	prog.setUniform("Tex1", 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	setActorMatrix(&mLight);
	mLight.render();
	resetActorMatrix();
	mTerrain.render();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	prog.setUniform("Tex1", 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mTest.getModelPtr()->getTexturePtr()->forceSetTextureId(mRenderTexture);
	setActorMatrix(&mTest);
	mTest.render();

	/* 頂点データ，法線データ，テクスチャ座標の配列を無効にする */
	glDisableClientState(GL_VERTEX_ARRAY);
}

void SceneBasic::resize(int w, int h)
{
    glViewport(0,0,w,h);
	width = w;
	height = h;

	float w2 = width / 2.0f;
	float h2 = height / 2.0f;
	viewport = mat4(vec4(w2, 0.0f, 0.0f, 0.0f),
		vec4(0.0f, h2, 0.0f, 0.0f),
		vec4(0.0f, 0.0f, 1.0f, 0.0f),
		vec4(w2 + 0, h2 + 0, 0.0f, 1.0f));
}
