#ifndef SCENEBASIC_H
#define SCENEBASIC_H

#include "scene.h"

#include "Model\Terrain.h"
#include "Model\Cube.h"
#include "Model\Plane.h"
#include "Model\Torus.h"

class SceneBasic : public Scene
{
private:

public:
    SceneBasic();

    void initScene();
    void calc( float t );
    void postCalc();
    void render();

protected:

	Terrain mTerrain;
	Plane mPlane;
	Cube mCube;

};

#endif // SCENEBASIC_H
