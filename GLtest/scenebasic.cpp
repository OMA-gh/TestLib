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

SceneBasic::SceneBasic()
	:mTerrain()
	,mCube()
{
}

void SceneBasic::initScene()
{
    GET_INSTANCE(Render)->init();
    GET_INSTANCE(Camera)->init();

    GET_INSTANCE(ModelMgr)->addModel("plane", std::move(std::make_unique<Plane>()));
    GET_INSTANCE(ModelMgr)->addModel("cube", std::move(std::make_unique<Cube>()));
    GET_INSTANCE(ModelMgr)->addModel("terrain", std::move(std::make_unique<Terrain>()));

    /*
	mPlane.init();
    mPlane.setTextureInfo(GET_INSTANCE(TextureMgr)->load(mPlane.getTextureName()));
    mCube.init();
    mCube.setTextureInfo(GET_INSTANCE(TextureMgr)->load(mPlane.getTextureName()));
    mTerrain.init();
    mTerrain.setTextureInfo(GET_INSTANCE(TextureMgr)->load(mPlane.getTextureName()));
    */
    if (GET_INSTANCE(ActorMgr)) {
        GET_INSTANCE(ActorMgr)->requestCreateActor("Test", GET_INSTANCE(ModelMgr)->getModelPtr("plane"));
        GET_INSTANCE(ActorMgr)->requestCreateActor("Light", GET_INSTANCE(ModelMgr)->getModelPtr("cube"));
        GET_INSTANCE(ActorMgr)->requestCreateActor("Terrain", GET_INSTANCE(ModelMgr)->getModelPtr("terrain"));
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

    //GET_INSTANCE(Render)->DrawShadowMap();
    GET_INSTANCE(Render)->DrawPass1();
    GET_INSTANCE(Render)->DrawPass2();

	/* 頂点データ，法線データ，テクスチャ座標の配列を無効にする */
	glDisableClientState(GL_VERTEX_ARRAY);
}
