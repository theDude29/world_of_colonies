#ifndef TANK_H
#define TANK_H

#include "jeu/soldats/soldat.h"

#define PV_TANK 500
#define DEGAT_TANK 35
#define VITESSE_ATTAQUE_TANK 2
#define VITESSE_TANK 2
#define PORTEE_TANK 180
#define COUT_OR_TANK 100
#define COUT_NOURRITURRE_TANK 200
#define XP_TANK 150
#define PLACE_TANK 15

class Tank : public Soldat
{
public:
    Tank(QObject* parent);
    static QString getInfo();
};

#endif // TANK_H
