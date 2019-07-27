#include "item.h"

Item::Item() : QObject()
{

}

cout Item::getCout()
{
    return m_cout;
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
