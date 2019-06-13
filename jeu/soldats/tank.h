#ifndef TANK_H
#define TANK_H

#include "jeu/soldats/soldat.h"

#define PV_TANK 500
#define DEGAT_TANK 40
#define VITESSE_ATTAQUE_TANK 3
#define VITESSE_TANK 3
#define PORTEE_TANK 30
#define COUT_OR_TANK 200
#define COUT_NOURRITURRE_TANK 900
#define XP_TANK 150

class Tank : public Soldat
{
public:
    Tank();
    virtual QString getInfo();
};

#endif // TANK_H
