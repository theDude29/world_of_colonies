#ifndef FANTASSIN_H
#define FANTASSIN_H

#include "soldat.h"

#define PV_FANTASSIN 200
#define DEGAT_FANTASSIN 15
#define VITESSE_ATTAQUE_FANTASSIN 1
#define VITESSE_FANTASSIN 6
#define PORTEE_FANTASSIN 150
#define COUT_OR_FANTASSIN 30
#define COUT_NOURRITURRE_FANTASSIN 130
#define XP_FANTASSIN 100
#define PLACE_FANTASSIN 5

class Fantassin : public Soldat
{
public:
    Fantassin(QObject* parent);
    static QString getInfo();
};

#endif // FANTASSIN_H
