#include "item.h"
#include "mainwindow.h"
#include "utilitaire/getcss.h"

Item::Item(QObject *parent, int maxPV) : QObject(parent)
{
    m_sceneCollisionManager = SceneManager::getSceneManager()->getSceneCollisionManager();
    m_maxPV = maxPV;
    m_pvActuelle = maxPV;
    m_pbPV = new QProgressBar(MainWindow::getMainWindow());
    m_pbPV->setFixedHeight(20);
    m_pbPV->setStyleSheet(getCSS("./gui/css/style_item.css"));
    m_pbPV->setFormat(QString("%v/%m"));
    m_pbPV->setMaximum(maxPV);
    m_pbPV->setMinimum(0);
    m_pbPV->setVisible(false);
    m_intact = true;
}

bool Item::isVisible()
{
    return m_meshSceneNode->isVisible();
}

cout Item::getCout()
{
    return m_cout;
}

void Item::setRotation(irr::core::vector3df rot)
{
    m_meshSceneNode->setRotation(rot);
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
    m_pbPV->setVisible(false);
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

bool Item::prendreDesPV(int nbPv)
{
    if(m_intact && !m_pbPV->isVisible())
    {
        m_pbPV->setVisible(true);

        m_intact = false;
    } //ne pas se faire taper si on quitte et que les tire sont encore la

    irr::core::vector2di screenPos = m_sceneCollisionManager->getScreenCoordinatesFrom3DPosition(getPosition());
    m_pbPV->move(screenPos.X, screenPos.Y);

    m_pvActuelle -= nbPv;
    m_pbPV->setValue(m_pvActuelle);

    if(m_pvActuelle <= 0)
    {
        return true;
    }

    return false;
}

Item::~Item()
{
    m_meshSceneNode->setVisible(false);
}
