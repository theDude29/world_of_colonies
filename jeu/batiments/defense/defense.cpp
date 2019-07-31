#include "defense.h"
#include "singleton/Device.h"
#include "jeu/soldats/shoot.h"

Defense::Defense(QObject* parent, int maxPV, QSize taille, cout coutDeConstruction) : Batiment(parent, maxPV, taille, coutDeConstruction)
{
    m_timer = Device::getDevice()->getTimer();
    m_texture = Driver::getDriver()->getTexture("mesh/texture/textureDefense.png");
    m_porte = 0;
}

void Defense::attaque(irr::core::vector3df direction, std::vector<Soldat*> *listeSoldats)
{
    if(m_heureDerniereAttaque < (m_timer->getRealTime() - m_vitesseAttaque * 1000))
    {
        m_heureDerniereAttaque = m_timer->getRealTime();
        new Shoot(this, m_degat, listeSoldats, this->getPosition(), m_tailleProjectile, direction);
    }
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

int Defense::getPorte()
{
    return m_porte;
}

