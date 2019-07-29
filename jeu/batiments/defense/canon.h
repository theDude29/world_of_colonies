#ifndef CANON_H
#define CANON_H

#include "jeu/batiments/defense/defense.h"

#define MAX_PV_CANON 150
#define TAILLE_CANON_X 8
#define TAILLE_CANON_Z 8
#define COUT_CONSTRUCTION_OR_CANON 500
#define COUT_CONSTRUCTION_NOURRITURE_CANON 200
#define XP_CANON 400
#define PORTE_CANON 200
#define DPS_CANON 20

class Canon : public Defense
{
public:
    Canon(QObject* parent);
    virtual QString getInfo();
};

#endif // CANON_H
