#include "soldat.h"

Soldat::Soldat()
{

}

void Soldat::setPosition(irr::core::vector3df pos)
{
    m_meshSceneNode->setPosition(pos);
}

