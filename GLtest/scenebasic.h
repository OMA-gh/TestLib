#ifndef SCENEBASIC_H
#define SCENEBASIC_H

#include "scene.h"

#include <gl/GL/glew.h>
#include <gl/GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "glslprogram.h"
#include "Camera.h"

#include "Model\Terrain.h"
#include "Model\Cube.h"
#include "Model\Plane.h"

#include "Actor\Test.h"

class SceneBasic : public Scene
{
private:
	GLSLProgram prog;

    int width, height;
	mat4 viewport;
    GLuint vaoHandle;

	void compileAndLinkShader();
	void setFullScreenQuad();
	void setMatrices();
	void setLightPos();
	void setActorMatrix(Actor* actor);
	void resetActorMatrix();

public:
    SceneBasic();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
	void setFrameBuffer();
	void setWhiteTextureInfo();

	GLuint getVertHandle() const {
		return mVertShader;
	}
	GLuint getFragHandle() const {
		return mFragShader;
	}
	GLuint getProgramHandle() const {
		return mProgramHandle;
	}
	const Camera& getCamera() const {
		return mCamera;
	}
	Camera* getCameraPtr() {
		return &mCamera;
	}

protected:
	glm::mat4 mModel, mView, mProjection;

	GLuint mVertShader;
	GLuint mFragShader;
	GLuint mProgramHandle;
	Camera mCamera;

	GLuint mFboHandle;
	GLuint mRenderTexture;
	GLuint mDepthBuffer;
	GLuint mWhiteTexHandle;
	GLenum mDrawBufs[1];
	GLuint mFullScreenQuad;

	Test mTest;
	Test mLight;

	Terrain mTerrain;
	Plane mPlane;
	Cube mCube;

	GLuint mPass1Index, mPass2Index;
};

#endif // SCENEBASIC_H
