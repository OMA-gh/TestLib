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

#include "Actor\Test.h"
#include "Actor\Light.h"
#include "Actor\Simple.h"

#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))

SceneBasic::SceneBasic()
	:mTerrain()
	,mCube()
{
}

void SceneBasic::debugCommand() {
    static int actor_num = 0;
    std::string name("debug");
    name = name.append(std::to_string(actor_num));
    GET_INSTANCE(ActorMgr)->addActor(name, std::move(std::make_unique<Simple>()), GET_INSTANCE(ModelMgr)->getModelPtr("cube"));
    actor_num++;
}

void SceneBasic::initScene()
{
    GET_INSTANCE(Render)->init();
    GET_INSTANCE(Physics)->init();
    GET_INSTANCE(Camera)->init();

    GET_INSTANCE(ModelMgr)->addModel("plane", std::move(std::make_unique<Plane>()));
    GET_INSTANCE(ModelMgr)->addModel("cube", std::move(std::make_unique<Cube>()));
    GET_INSTANCE(ModelMgr)->addModel("torus", std::move(std::make_unique<Torus>()));
    GET_INSTANCE(ModelMgr)->addModel("terrain", std::move(std::make_unique<Terrain>()));

    if (GET_INSTANCE(ActorMgr)) {
        GET_INSTANCE(ActorMgr)->addActorDynamic("Test", std::move(std::make_unique<Simple>()), GET_INSTANCE(ModelMgr)->getModelPtr("cube"));
        GET_INSTANCE(ActorMgr)->addActorDynamic("Light", std::move(std::make_unique<Light>()), GET_INSTANCE(ModelMgr)->getModelPtr("cube"));
        GET_INSTANCE(ActorMgr)->addActorDynamic("Terrain", std::move(std::make_unique<Test>()), GET_INSTANCE(ModelMgr)->getModelPtr("terrain"));
    }
}

void SceneBasic::preCalc() {
    GET_INSTANCE(ActorMgr)->preCalc();
}

void SceneBasic::calc( float t )
{
    GET_INSTANCE(Camera)->update();
	GET_INSTANCE(ActorMgr)->calc();
    GET_INSTANCE(Physics)->calc();
}

void SceneBasic::postCalc() {
    GET_INSTANCE(ActorMgr)->postCalc();
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
