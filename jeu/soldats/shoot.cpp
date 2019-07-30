#include "shoot.h"
#include "singleton/Driver.h"
#include <QTimer>

Shoot::Shoot(QObject* parent, int degat, std::vector<Batiment*> *listeBatiment, irr::core::vector3df pos, int taille, irr::core::vector3df direction) : Item(parent)
{
    m_listeBatiment = listeBatiment;
    m_direction = direction;
    m_degat = degat;
    m_collisionManager = SceneManager::getSceneManager()->getSceneCollisionManager();

    //
    m_meshSceneNode = SceneManager::getSceneManager()->addLightSceneNode();
    m_meshSceneNode->setRadius(5);
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
    m_timer = new QTimer(this);
    m_timer->setInterval(40);
    m_timer->start();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(maj()));
}

void Shoot::maj()
{
    m_meshSceneNode->setPosition(m_meshSceneNode->getPosition() + (m_direction * VITESSE));
    
    irr::core::aabbox3df maBox = m_meshSceneNode->getTransformedBoundingBox();
    irr::core::aabbox3df boxEnnemi;
    for(std::vector<Batiment*>::iterator it = m_listeBatiment->begin(); it != m_listeBatiment->end(); it++)
    {
        if((*it)->isVisible())
        {
            boxEnnemi = (*it)->getMeshSceneNode()->getTransformedBoundingBox();
            if(boxEnnemi.intersectsWithBox(maBox))
            {
                if((*it)->prendreDesPV(m_degat))
                {
                    (*it)->kill();
                }

                this->kill();
            }
        }
    }
}

void Shoot::kill()
{
    m_timer->stop();
    m_meshSceneNode->setVisible(false);
}

