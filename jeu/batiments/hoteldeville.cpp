#include "hoteldeville.h"

HotelDeVille::HotelDeVille() : Conteneur(MAX_PV_HDV, QSize(TAILLE_HDV_W, TAILLE_HDV_H), cout{0,0,0}, CONTENANCE_MAX_HDV)
{
    m_typeBatiment = hdv;
    m_texture = Driver::getDriver()->getTexture("mesh/texture/texture_hdv.png");

    m_meshSceneNode = SceneManager::getSceneManager()->addMeshSceneNode(SceneManager::getSceneManager()->getMesh("mesh/hdv.obj"));
    m_meshSceneNode->setMaterialTexture(0, m_texture);
    m_meshSceneNode->setScale(irr::core::vector3df(10,10,10));
    m_meshSceneNode->setRotation(m_meshSceneNode->getRotation() + irr::core::vector3df(0,90,0));
}

QString HotelDeVille::getInfo()
{
    return QString("singe");
}

HotelDeVille::~HotelDeVille()
{

}
