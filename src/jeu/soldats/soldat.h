#ifndef SOLDAT_H
#define SOLDAT_H

#include <irrlicht/ITimer.h>
#include <vector>
#include "../batiments/batiment.h"

enum typeSoldat
{
    artilleur,
    fantassin,
    tank
};

class Soldat : public Item
{
public:
    Soldat(QObject* parent, int maxPV);
    virtual ~Soldat();
    void attaque(irr::core::vector3df direction, std::vector<Batiment *> *listeBatiment);

    void setPosition(irr::core::vector3df pos);
    int getType();
    int getPorte();
    int getVitesse();

protected:
    int m_degats, m_vitesseAttaque, m_dps;
    irr::u32 m_heureDerniereAttaque;
    irr::ITimer* m_timer;
    int m_vitesse;
    int m_portee;
    int m_place;
    int m_tailleProjectile;
    typeSoldat m_type;
};

#endif // SOLDAT_H
