#include "decor.h"
#include "../singleton/SceneManager.h"
#include "../singleton/Driver.h"

using namespace irr;

scene::ITriangleSelector *creerDecor()
{
    scene::ISceneManager* sceneManager = SceneManager::getSceneManager();
    video::IVideoDriver* driver = Driver::getDriver();

    scene::IMesh* plane = sceneManager->getGeometryCreator()->createPlaneMesh(core::dimension2df(10,10), core::dimension2du(100, 100));
    scene::IMeshSceneNode* ground = sceneManager->addMeshSceneNode(plane);
    ground->setMaterialTexture(0, driver->getTexture("sol.jpg"));
    ground->setMaterialFlag(video::EMF_LIGHTING, false);

    scene::ILightSceneNode* l = sceneManager->addLightSceneNode();
    l->setPosition(core::vector3df(500,1000, -1000));
    l->setRadius(10000);

    scene::IMeshSceneNode* hdv = sceneManager->addMeshSceneNode(sceneManager->getMesh("mesh/hdv.obj"));
    hdv->setRotation(core::vector3df(0,90,0));
    hdv->setScale(core::vector3df(10,10,10));
    hdv->setPosition(hdv->getPosition() + core::vector3df(100,1,0));
    //hdv->setMaterialFlag(video::EMF_LIGHTING, false);

    irr::scene::ITriangleSelector* slt = ground->getTriangleSelector();
    return slt;
}
