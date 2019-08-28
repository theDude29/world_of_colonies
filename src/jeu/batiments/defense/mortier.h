#ifndef MORTIER_H
#define MORTIER_H

#include "defense.h"

#define MAX_PV_MORTIER 200
#define TAILLE_MORTIER_X 8
#define TAILLE_MORTIER_Z 8
#define COUT_CONSTRUCTION_OR_MORTIER 1000
#define COUT_CONSTRUCTION_NOURRITURE_MORTIER 600
#define XP_MORTIER 600
#define PORTE_MORTIER 500
#define DEGAT_MORTIER 100
#define VITESSE_ATTAQUE_MORTIER 3

class Mortier : public Defense
{
public:
    Mortier(QObject* parent);
    virtual QString getInfo();
};

#endif // MORTIER_H
