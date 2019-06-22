#include "armee.h"
#include "bdd/bdd.h"

Armee::Armee(QString pseudo) : QObject()
{
    m_pseudo = pseudo;

    m_nbPlaceMax = m_nbPlaceOccupee = m_nbArtilleur = m_nbFantassin = m_nbTank = 0;

    //on met a jour les stats
    m_nbArtilleur = Bdd::getBdd()->getNbArtilleur(m_pseudo);
    m_nbTank = Bdd::getBdd()->getNbTank(m_pseudo);
    m_nbFantassin = Bdd::getBdd()->getNbFantassin(m_pseudo);

    m_nbPlaceOccupee = m_nbArtilleur*PLACE_ARTILLEUR + m_nbFantassin*PLACE_FANTASSIN + m_nbTank*PLACE_TANK;
}

void Armee::ajouterArtilleur()
{
    m_nbPlaceOccupee += PLACE_ARTILLEUR;
    m_nbArtilleur++;
    Bdd::getBdd()->setNbArtilleur(m_pseudo, m_nbArtilleur);
}

void Armee::ajouterFantassin()
{
    m_nbPlaceOccupee += PLACE_FANTASSIN;
    m_nbFantassin++;
    Bdd::getBdd()->setNbFantassin(m_pseudo, m_nbFantassin);
}

void Armee::ajouterTank()
{
    m_nbPlaceOccupee += PLACE_TANK;
    m_nbTank++;
    Bdd::getBdd()->setNbTank(m_pseudo, m_nbTank);
}

int Armee::getNbArtilleur()
{
    return m_nbArtilleur;
}

int Armee::getNbFantassin()
{
    return m_nbFantassin;
}

int Armee::getNbTank()
{
    return m_nbTank;
}

void Armee::majPlaceMax(int nbCaserne)
{
    m_nbPlaceMax = nbCaserne * 50;
}

int Armee::getNbPlaceMax()
{
    return m_nbPlaceMax;
}

int Armee::getNbPlaceOccupe()
{
    return m_nbPlaceOccupee;
}
