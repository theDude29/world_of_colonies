#ifndef CASERNE_H
#define CASERNE_H

#include "jeu/batiments/batiment.h"

#define MAX_PV_CASERNE 300
#define TAILLE_CASERNE_X 20
#define TAILLE_CASERNE_Z 20
#define COUT_CONSTRUCTION_OR_CASERNE 1000
#define COUT_CONSTRUCTION_NOURRITURE_CASERNE 400
#define XP_CASERNE 800

class Caserne : public Batiment
{
public:
    Caserne(QObject* parent);
    virtual QString getInfo();
};

#endif // CASERNE_H
