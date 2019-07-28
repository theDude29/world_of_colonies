#ifndef SOLDAT_H
#define SOLDAT_H

#include "jeu/item.h"

enum typeSoldat
{
    artilleur,
    fantassin,
    tank
};

class Soldat : public Item
{
public:
    Soldat();
    void setPosition(irr::core::vector3df pos);
    int getType();
    int getPorte();
    int getVitesse();

protected:
    int m_degats, m_vitesseAttaque, m_dps;
    int m_pointsVies;
    int m_vitesse;
    int m_portee;
    int m_place;
    typeSoldat m_type;
};

#endif // SOLDAT_H
