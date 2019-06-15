#ifndef FANTASSIN_H
#define FANTASSIN_H

#include "jeu/soldats/soldat.h"

#define PV_FANTASSIN 200
#define DEGAT_FANTASSIN 15
#define VITESSE_ATTAQUE_FANTASSIN 1
#define VITESSE_FANTASSIN 8
#define PORTEE_FANTASSIN 10
#define COUT_OR_FANTASSIN 80
#define COUT_NOURRITURRE_FANTASSIN 380
#define XP_FANTASSIN 100
#define PLACE_FANTASSIN 5

class Fantassin : public Soldat
{
public:
    Fantassin();
    virtual QString getInfo();
};

#endif // FANTASSIN_H
