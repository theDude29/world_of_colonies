#ifndef SCENEMANAGER
#define SCENEMENAGER

#include <irrlicht/irrlicht.h>

class SceneManager
{
public:
    static irr::scene::ISceneManager* getSceneManager();

private:
    SceneManager();
    static irr::scene::ISceneManager* m_instance;
};
#endif // DEVICE
