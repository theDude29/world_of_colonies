#include "shoot.h"
#include "singleton/Driver.h"
#include <QTimer>
#include <iostream>

Shoot::Shoot(QObject* parent, int degat, std::vector<Batiment*> *listeBatiment, irr::core::vector3df pos, int taille, irr::core::vector3df direction) : Item(parent)
{
    m_shootMortier = false;
    m_listeBatiment = listeBatiment;
    m_listeSoldat = NULL;
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

Shoot::Shoot(QObject *parent, int degat, std::vector<Soldat *> *listeSoldat, irr::core::vector3df pos, int taille, irr::core::vector3df direction, irr::core::vector3df posCible) : Item(parent)
{
    m_shootMortier = false;
    m_listeBatiment = NULL;
    m_listeSoldat = listeSoldat;
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
    case 4:
        texture = Driver::getDriver()->getTexture("mesh/texture/particlewhite.bmp");
        break;
    case 6:
        texture = Driver::getDriver()->getTexture("mesh/texture/particlewhite.bmp");
        break;
    case 12:
        m_shootMortier = true;
        texture = Driver::getDriver()->getTexture("mesh/texture/particle.bmp");
        break;
    default : break;
    }

    if(m_shootMortier)
    {
        m_posCible = posCible;
        m_x = 0;
        irr::core::vector3df difference = m_posCible - m_meshSceneNode->getPosition();
        m_longueur = sqrt(pow(difference.X, 2) + pow(difference.Z, 2));
        m_hauteurMax = 100;
        //0 = m_coefficient*(m_longueur/2)^2 + m_hauteurMax;
        // m_coefficient -> x (a trouvve avec l equation) donc :
        m_coefficient = -m_hauteurMax / pow((m_longueur/2), 2);
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
    irr::core::vector3df newPos = m_meshSceneNode->getPosition() + (m_direction * VITESSE);
    
    if(m_shootMortier)
    {
        double y = m_coefficient*(m_x*m_x) + m_hauteurMax;
        m_x += (m_direction.getLength() * VITESSE);
        newPos.Y = y;
    }

    m_meshSceneNode->setPosition(newPos);

    irr::core::aabbox3df maBox = m_meshSceneNode->getTransformedBoundingBox();
    irr::core::aabbox3df boxEnnemi;

    if(m_listeBatiment != NULL)
    {
        for(std::vector<Batiment*>::iterator it = m_listeBatiment->begin(); it != m_listeBatiment->end(); it++)
        {
            if((*it)->isVisible())
            {
                boxEnnemi = (*it)->getMeshSceneNode()->getTransformedBoundingBox();
                if(boxEnnemi.intersectsWithBox(maBox))
                {
                    if((*it)->prendreDesPV(m_degat))
                    {
                        (*it)->kill(true);
                    }

                    this->kill();
                }
            }
        }
    }

    if(m_listeSoldat != NULL)
    {
        for(std::vector<Soldat*>::iterator it = m_listeSoldat->begin(); it != m_listeSoldat->end(); it++)
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
}

void Shoot::kill()
{
    m_timer->stop();
    m_meshSceneNode->setVisible(false);
}

