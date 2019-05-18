#include "defense.h"

Defense::Defense(int maxPV, QSize taille, cout coutDeConstruction) : Batiment(maxPV, taille, coutDeConstruction)
{
    m_texture = Driver::getDriver()->getTexture("mesh/texture/textureDefense.png");
    m_porte = 0;
}

void Defense::estVise()
{
    m_spherePorte->setPosition(m_meshSceneNode->getPosition());
    m_spherePorte->setVisible(true);
}

void Defense::estPlusVise()
{
    m_spherePorte->setVisible(false);
}

