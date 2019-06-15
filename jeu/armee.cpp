#include "armee.h"

Armee::Armee() : QObject()
{
    m_nbPlaceMax = m_nbPlaceOccupee = m_nbArtilleur = m_nbFantassin = m_nbTank = 0;
}

void Armee::ajouterArtilleur()
{
    m_nbPlaceOccupee += PLACE_ARTILLEUR;
    m_nbArtilleur++;
}

void Armee::ajouterFantassin()
{
    m_nbPlaceOccupee += PLACE_FANTASSIN;
    m_nbFantassin++;
}

void Armee::ajouterTank()
{
    m_nbPlaceOccupee += PLACE_TANK;
    m_nbTank++;
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
