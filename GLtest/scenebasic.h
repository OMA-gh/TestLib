#ifndef SCENEBASIC_H
#define SCENEBASIC_H

#include "scene.h"

#include "Model\Terrain.h"
#include "Model\Cube.h"
#include "Model\Plane.h"

#include "Actor\Test.h"

class SceneBasic : public Scene
{
private:

public:
    SceneBasic();

    void initScene();
    void update( float t );
    void render();

protected:

	Terrain mTerrain;
	Plane mPlane;
	Cube mCube;

};

#endif // SCENEBASIC_H
