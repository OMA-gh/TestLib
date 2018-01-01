#include <glm\glm.hpp>
#include "scenebasic.h"
#include "System\Manager.h"

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

SceneBasic::SceneBasic()
	:mTerrain()
	,mCube()
{
}

void SceneBasic::initScene()
{
    GET_INSTANCE(Render)->init();

	mPlane.init();
    mPlane.setTextureInfo(GET_INSTANCE(TextureMgr)->load(mPlane.getTextureName()));
    mCube.init();
    mCube.setTextureInfo(GET_INSTANCE(TextureMgr)->load(mPlane.getTextureName()));
    mTerrain.init();
    mTerrain.setTextureInfo(GET_INSTANCE(TextureMgr)->load(mPlane.getTextureName()));

    if (GET_INSTANCE(ActorMgr)) {
        GET_INSTANCE(ActorMgr)->requestCreateActor("Test", &mPlane);
        GET_INSTANCE(ActorMgr)->requestCreateActor("Light", &mCube);
        GET_INSTANCE(ActorMgr)->requestCreateActor("Terrain", &mTerrain);
    }
}

void SceneBasic::update( float t )
{
    GET_INSTANCE(Camera)->update();
	
    if (GET_INSTANCE(ActorMgr)) {
        GET_INSTANCE(ActorMgr)->update();
    }
    else {
        printf("ERROR:failed to get ActorMgr\n");
    }
}

void SceneBasic::render()
{
	/* 頂点データ，法線データ，テクスチャ座標の配列を有効にする */
	glEnableClientState(GL_VERTEX_ARRAY);

    GET_INSTANCE(Render)->DrawShadowMap();
    GET_INSTANCE(Render)->DrawPass1();
    GET_INSTANCE(Render)->DrawPass2();

	/* 頂点データ，法線データ，テクスチャ座標の配列を無効にする */
	glDisableClientState(GL_VERTEX_ARRAY);
}
