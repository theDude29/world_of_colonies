#include "Gestionattaquevillage.h"

GestionAttaqueVillage::GestionAttaqueVillage(QObject *parent) : QObject(parent)
{

}

void GestionAttaqueVillage::ajouterTroupe(int typeDuSoldat, irr::core::vector3df pos)
{
    Soldat* soldat;

    switch(typeDuSoldat)
    {
    case artilleur:
        soldat = new Artilleur;
        break;
    case fantassin:
        soldat = new Fantassin;
        break;
    case tank:
        soldat = new Tank;
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

