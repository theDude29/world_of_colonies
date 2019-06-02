#ifndef SOLDAT_H
#define SOLDAT_H

#include "jeu/item.h"

class Soldat : public Item
{
public:
    Soldat();

protected:
    int m_degats, m_vitesseAttaque, m_dps;
    int m_pointsVies;
    int m_vitesse;
    int m_portee;
};

#endif // SOLDAT_H
