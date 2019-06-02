#ifndef ARTILLEUR_H
#define ARTILLEUR_H

#include "jeu/soldats/soldat.h"

#define PV_ARTILLEUR 50
#define DEGAT_ARTILLEUR 20
#define VITESSE_ATTAQUE_ARTILLEUR 1
#define VITESSE_ARTILLEUR 10
#define PORTEE_ARTILLEUR 100
#define COUT_OR_ARTILLEUR 100
#define COUT_NOURRITURRE_ARTILLEUR 400
#define XP_ARTILLEUR 100

class Artilleur : public Soldat
{
public:
    Artilleur();
    virtual QString getInfo();
};

#endif // ARTILLEUR_H
