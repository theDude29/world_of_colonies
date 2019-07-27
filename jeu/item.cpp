#include "item.h"

Item::Item() : QObject()
{

}

cout Item::getCout()
{
    return m_cout;
}

irr::core::vector3df Item::getPosition()
{
    return m_meshSceneNode->getPosition();
}

irr::core::vector3df Item::getRotation()
{
    return m_meshSceneNode->getRotation();
}

void Item::kill()
{
    m_meshSceneNode->setVisible(false);
}

irr::video::ITexture* Item::getTexture()
{
    return m_texture;
}

void Item::setVisible(bool visible)
{
    m_meshSceneNode->setVisible(visible);
}

irr::scene::IMeshSceneNode* Item::getMeshSceneNode()
{
    return m_meshSceneNode;
}

Item::~Item()
{
    m_meshSceneNode->setVisible(false);
}
