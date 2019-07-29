#include "shoot.h"
#include "singleton/SceneManager.h"
#include "singleton/Driver.h"
#include <QTimer>

Shoot::Shoot(QObject* parent, irr::core::vector3df pos, int taille, irr::core::vector3df direction) : Item(parent)
{
    m_direction = direction;

    //
    m_meshSceneNode = SceneManager::getSceneManager()->addLightSceneNode();
    m_meshSceneNode->setRadius(300);
    pos.Y += 30;
    m_meshSceneNode->setPosition(pos);
    //billboard
    irr::video::ITexture* texture;
    switch(taille)
    {
    case 3:
        texture = Driver::getDriver()->getTexture("mesh/texture/particlegreen.jpg");
        break;
    case 5:
        texture = Driver::getDriver()->getTexture("mesh/texture/particlegreen.jpg");
        break;
    case 10:
        texture = Driver::getDriver()->getTexture("mesh/texture/particle.bmp");
        break;
    default : break;
    }

    irr::scene::IBillboardSceneNode* bill = SceneManager::getSceneManager()->addBillboardSceneNode(m_meshSceneNode, irr::core::dimension2df(10*taille,10*taille));
    bill->setMaterialTexture(0, texture);
    bill->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
    bill->setMaterialFlag(irr::video::EMF_LIGHTING, false);

    //timer pour maj
    QTimer* timer = new QTimer(this);
    timer->setInterval(40);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(maj()));
}

void Shoot::maj()
{
    m_meshSceneNode->setPosition(m_meshSceneNode->getPosition() + (m_direction * VITESSE));
}

