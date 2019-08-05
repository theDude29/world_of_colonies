#include "Gestionattaquevillage.h"
#include <QTimer>
#include <math.h>
#include <iostream>
#include <irrlicht/irrlicht.h>
#include <iostream>

GestionAttaqueVillage::GestionAttaqueVillage(QObject *parent, QLabel* textVictoire) : QObject(parent)
{
    m_textVictoire = textVictoire;

    //timer pour maj
    QTimer* timer = new QTimer(this);
    timer->setInterval(40);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(maj()));
}

void GestionAttaqueVillage::maj()
{
    majSoldat();
    majDefense();
}

void GestionAttaqueVillage::majDefense()
{
    irr::core::vector3df posSoldatLePlusPres;
    irr::core::vector3df direction;
    int distance;

    //on parcour tout les defense
    for(std::vector<Defense*>::iterator it = m_listeDefense.begin(); it != m_listeDefense.end(); ++it)
    {
        if((*it)->isVisible())
        {
            //on recupere le soldat le plus pres
            posSoldatLePlusPres = getItemLePlusPres((*it)->getPosition(), soldat);

            if(posSoldatLePlusPres.X != 10000) //cela voudrait dire que tout les soldats sont detruits
            {
                //la direction dans laquelle il se trouve
                direction = posSoldatLePlusPres - (*it)->getPosition();
                //on calcul la distance
                distance = sqrt(pow(direction.X,2) + pow(direction.Y,2) + pow(direction.Z,2));
                //si plus petite que porte on tape sinon fait rien
                if(distance < (*it)->getPorte())
                {
                    //on s oriente dans cette direction
                    (*it)->setRotation(direction.getHorizontalAngle());
                    (*it)->attaque(direction.normalize(), posSoldatLePlusPres, &m_listeSoldats);
                }
            }
        }
    }
}

bool GestionAttaqueVillage::gagner()
{
    bool gagner = true;
    for(std::vector<Batiment*>::iterator it = m_listeBatiments.begin(); it != m_listeBatiments.end(); ++it)
    {
        if((*it)->isVisible())
        {
            gagner = false;
        }
    }

    return gagner;
}

void GestionAttaqueVillage::majSoldat()
{
    irr::core::vector3df posBatLePlusPres;
    irr::core::vector3df direction;
    int distance;

    //on parcour tout les soldats
    for(std::vector<Soldat*>::iterator it = m_listeSoldats.begin(); it != m_listeSoldats.end(); ++it)
    {
        if((*it)->isVisible())
        {
            //on recupere le batiment le plus pres
            posBatLePlusPres = getItemLePlusPres((*it)->getPosition(), batiment);

            if(posBatLePlusPres.X != 10000) //cela veut dire que tout les batiments sont detruits
            {
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
                    (*it)->attaque(direction.normalize(), &m_listeBatiments);
                }
            }
        }
    }
}

irr::core::vector3df GestionAttaqueVillage::getItemLePlusPres(irr::core::vector3df posSoldat, int typeItem)
{
    //on teste victoire
    if(gagner())
    {
        m_textVictoire->setVisible(true);
    }

    std::vector<Item*> listeChoisi;

    if(typeItem == batiment) listeChoisi = convertBatimentToItem();
    else listeChoisi = convertSoldatToItem();

    irr::core::vector3df vecteurDistance;
    int longueur;
    int longueurLaPlusPetite = 100000;
    irr::core::vector3df posItemLePlusPres(10000,0,0);
    for(std::vector<Item*>::iterator it = listeChoisi.begin(); it != listeChoisi.end(); ++it)
    {
        if((*it)->isVisible())
        {
            vecteurDistance = (*it)->getPosition() - posSoldat;
            longueur = sqrt(pow(vecteurDistance.X,2) + pow(vecteurDistance.Y,2) + pow(vecteurDistance.Z,2));

            if(longueur < longueurLaPlusPetite)
            {
                longueurLaPlusPetite = longueur;
                posItemLePlusPres = (*it)->getPosition();
            }
        }
    }

    return posItemLePlusPres;
}

std::vector<Item*> GestionAttaqueVillage::convertBatimentToItem()
{
    std::vector<Item*> listItem;
    for(std::vector<Batiment*>::iterator it = m_listeBatiments.begin(); it != m_listeBatiments.end(); it++)
    {
        listItem.push_back((*it));
    }

    return listItem;
}

std::vector<Item*> GestionAttaqueVillage::convertSoldatToItem()
{
    std::vector<Item*> listItem;
    for(std::vector<Soldat*>::iterator it = m_listeSoldats.begin(); it != m_listeSoldats.end(); it++)
    {
        listItem.push_back((*it));
    }

    return listItem;
}

void GestionAttaqueVillage::setListeBatiment(std::vector<Batiment *> listeBats)
{
    m_listeBatiments = listeBats;

    //on extrait les defense
    for(std::vector<Batiment*>::iterator it = m_listeBatiments.begin(); it != m_listeBatiments.end(); ++it)
    {
        if((*it)->getType() == mortier || (*it)->getType() == canon || (*it)->getType() == tourelle)
        {
            Defense* def = (Defense*)(*it);
            m_listeDefense.push_back(def);
        }
    }
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

    m_listeSoldats.clear();
}

