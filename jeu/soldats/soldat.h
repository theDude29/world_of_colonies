#ifndef SOLDAT_H
#define SOLDAT_H

#include "jeu/item.h"
#include <irrlicht/ITimer.h>

enum typeSoldat
{
    artilleur,
    fantassin,
    tank
};

class Soldat : public Item
{
public:
    Soldat(QObject* parent);
    virtual ~Soldat();
    void attaque(irr::core::vector3df direction);

    void setPosition(irr::core::vector3df pos);
    int getType();
    int getPorte();
    int getVitesse();

protected:
    int m_degats, m_vitesseAttaque, m_dps;
    irr::u32 m_heureDerniereAttaque;
    irr::ITimer* m_timer;
    int m_pointsVies;
    int m_vitesse;
    int m_portee;
    int m_place;
    int m_tailleProjectile;
    typeSoldat m_type;
};

#endif // SOLDAT_H
