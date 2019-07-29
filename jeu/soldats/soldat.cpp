#include "soldat.h"
#include "singleton/Driver.h"
#include "singleton/Device.h"
#include <iostream>
#include <time.h>
#include "jeu/soldats/shoot.h"

Soldat::Soldat(QObject *parent) : Item(parent)
{
    m_timer = Device::getDevice()->getTimer();
    m_heureDerniereAttaque = 0;

    m_texture = Driver::getDriver()->getTexture("mesh/texture/texture_troupes.png");
}

void Soldat::attaque(irr::core::vector3df direction)
{
    if(m_heureDerniereAttaque < (m_timer->getRealTime() - m_vitesseAttaque * 1000))
    {
        m_heureDerniereAttaque = m_timer->getRealTime();
        new Shoot(this, this->getPosition(), m_tailleProjectile, direction);
    }
}

void Soldat::setPosition(irr::core::vector3df pos)
{
    m_meshSceneNode->setPosition(pos);
}

int Soldat::getType()
{
    return m_type;
}

int Soldat::getVitesse()
{
    return m_vitesse;
}

int Soldat::getPorte()
{
    return m_portee;
}

Soldat::~Soldat()
{

}
