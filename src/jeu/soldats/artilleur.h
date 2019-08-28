#ifndef ARTILLEUR_H
#define ARTILLEUR_H

#include "soldat.h"

#define PV_ARTILLEUR 50
#define DEGAT_ARTILLEUR 20
#define VITESSE_ATTAQUE_ARTILLEUR 1
#define VITESSE_ARTILLEUR 10
#define PORTEE_ARTILLEUR 250
#define COUT_OR_ARTILLEUR 50
#define COUT_NOURRITURRE_ARTILLEUR 150
#define XP_ARTILLEUR 100
#define PLACE_ARTILLEUR 5

class Artilleur : public Soldat
{
public:
    Artilleur(QObject* parent);
    static QString getInfo();
};

#endif // ARTILLEUR_H
