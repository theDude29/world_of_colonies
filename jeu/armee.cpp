#include "armee.h"

Armee::Armee() : QObject()
{
    m_nbPlaceMax = m_nbPlaceOccupee = m_nbArtilleur = m_nbFantassin = m_nbTank = 0;
}

void Armee::ajouterArtilleur()
{
    m_nbArtilleur++;
}

void Armee::ajouterFantassin()
{
    m_nbFantassin++;
}

void Armee::ajouterTank()
{
    m_nbTank++;
}

int Armee::getNbArtilleur()
{
    m_nbPlaceOccupee += PLACE_ARTILLEUR;
    return m_nbArtilleur;
}

int Armee::getNbFantassin()
{
    m_nbPlaceOccupee += PLACE_FANTASSIN;
    return m_nbFantassin;
}

int Armee::getNbTank()
{
    m_nbPlaceOccupee += PLACE_TANK;
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
