#ifndef MORTIER_H
#define MORTIER_H

#include "jeu/batiments/defense/defense.h"

#define MAX_PV_MORTIER 200
#define TAILLE_MORTIER_X 8
#define TAILLE_MORTIER_Z 8
#define COUT_CONSTRUCTION_OR_MORTIER 1000
#define COUT_CONSTRUCTION_NOURRITURE_MORTIER 600
#define XP_MORTIER 600
#define PORTE_MORTIER 500
#define DPS_MORTIER 100

class Mortier : public Defense
{
public:
    Mortier();
    virtual QString getInfo();
};

#endif // MORTIER_H
