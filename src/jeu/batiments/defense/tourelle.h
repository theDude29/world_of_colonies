#ifndef TOURELLE_H
#define TOURELLE_H

#include "defense.h"

#define MAX_PV_TOURELLE 250
#define TAILLE_TOURELLE_X 10
#define TAILLE_TOURELLE_Z 10
#define COUT_CONSTRUCTION_OR_TOURELLE 1500
#define COUT_CONSTRUCTION_NOURRITURE_TOURELLE 600
#define XP_TOURELLE 600
#define PORTE_TOURELLE 350
#define DEGAT_TOURELLE 40
#define VITESSE_ATTAQUE_TOURELLE 1

class Tourelle : public Defense
{
public:
    Tourelle(QObject* parent);
    virtual QString getInfo();
};

#endif // TOURELLE_H
