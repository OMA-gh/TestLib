#ifndef SCENEBASIC_H
#define SCENEBASIC_H

#include "scene.h"

class SceneBasic : public Scene
{
private:

public:
    SceneBasic();

    void debugCommand();

    void initScene();
    void preCalc();
    void calc( float t );
    void postCalc();
    void render();

protected:
};

#endif // SCENEBASIC_H
