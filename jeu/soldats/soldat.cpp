#include "soldat.h"
#include "singleton/Driver.h"

Soldat::Soldat()
{
    m_texture = Driver::getDriver()->getTexture("mesh/texture/texture_troupes.png");
}

void Soldat::setPosition(irr::core::vector3df pos)
{
    m_meshSceneNode->setPosition(pos);
}

