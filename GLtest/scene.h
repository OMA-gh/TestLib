#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
    /**
      Load textures, initialize shaders, etc.
      */
    virtual void initScene() = 0;

    /**
      This is called prior to every frame.  Use this
      to update your animation.
      */
    virtual void calc( float t ) = 0;

    /**
      Draw your scene.
      */
    virtual void render() = 0;

};

#endif // SCENE_H
