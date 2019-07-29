#include "Gestionattaquevillage.h"
#include <QTimer>
#include <math.h>
#include <iostream>
#include <irrlicht/irrlicht.h>

GestionAttaqueVillage::GestionAttaqueVillage(QObject *parent) : QObject(parent)
{
    //timer pour maj
    QTimer* timer = new QTimer(this);
    timer->setInterval(40);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(maj()));
}

void GestionAttaqueVillage::maj()
{
    irr::core::vector3df posBatLePlusPres;
    irr::core::vector3df direction;
    int distance;

    //on parcour tout les soldats
    for(std::vector<Soldat*>::iterator it = m_listeSoldats.begin(); it != m_listeSoldats.end(); ++it)
    {
        //on recupere le batiment le plus pres
        posBatLePlusPres = getBatLePlusPres((*it)->getPosition());
        //la direction dans laquelle il se trouve
        direction = posBatLePlusPres - (*it)->getPosition();
        //on s oriente dans cette direction
        (*it)->setRotation(direction.getHorizontalAngle());

        //on calcul la distance
        distance = sqrt(pow(direction.X,2) + pow(direction.Y,2) + pow(direction.Z,2));
        //si plus petite que porte on tape sinon on se rapproche
        if(distance > (*it)->getPorte())
        {
            (*it)->setPosition((*it)->getPosition() + (direction.normalize() * (*it)->getVitesse()));
        }

        else
        {
            (*it)->attaque(direction.normalize());
        }
    }
}

irr::core::vector3df GestionAttaqueVillage::getBatLePlusPres(irr::core::vector3df posSoldat)
{
    irr::core::vector3df vecteurDistance;
    int longueur;
    int longueurLaPlusPetite = 100000;
    irr::core::vector3df posDuBatLePlusPres;
    for(std::vector<Batiment*>::iterator it = m_listeBatiments.begin(); it != m_listeBatiments.end(); ++it)
    {
        vecteurDistance = (*it)->getPosition() - posSoldat;
        longueur = sqrt(pow(vecteurDistance.X,2) + pow(vecteurDistance.Y,2) + pow(vecteurDistance.Z,2));

        if(longueur < longueurLaPlusPetite)
        {
            longueurLaPlusPetite = longueur;
            posDuBatLePlusPres = (*it)->getPosition();
        }
    }

    return posDuBatLePlusPres;
}

void GestionAttaqueVillage::setListeBatiment(std::vector<Batiment *> listeBats)
{
    m_listeBatiments = listeBats;
}


void GestionAttaqueVillage::ajouterTroupe(int typeDuSoldat, irr::core::vector3df pos)
{
    Soldat* soldat;

    switch(typeDuSoldat)
    {
    case artilleur:
        soldat = new Artilleur(this);
        break;
    case fantassin:
        soldat = new Fantassin(this);
        break;
    case tank:
        soldat = new Tank(this);
        break;
    default : break;
    }
    soldat->setPosition(pos);

    m_listeSoldats.push_back(soldat);
}

void GestionAttaqueVillage::detruireTroupe()
{
    for(std::vector<Soldat*>::iterator it = m_listeSoldats.begin(); it != m_listeSoldats.end(); ++it)
    {
        (*it)->kill();
    }

    for(unsigned int i = 0; i < m_listeSoldats.size(); ++i)
    {
        m_listeSoldats.pop_back();
    }
}

