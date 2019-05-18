#ifndef TRAVAILLEUR_OR_H
#define TRAVAILLEUR_OR_H

#include "jeu/batiments/ressource/travailleur.h"

#define MAX_PV_TRAVAILLEUR_OR 50
#define COUT_CONSTRUCTION_TRAVAILLEUR_OR_OR 70
#define COUT_CONSTRUCTION_TRAVAILLEUR_OR_NOURRITURE 30
#define TAILLE_TRAVAILLEUR_OR_W 10
#define TAILLE_TRAVAILLEUR_OR_H 10
#define CONTENANCE_MAX_TRAVAILLEUR_OR 80
#define PRODUCTIVITE_TRAVAILLEUR_OR 10

class Travailleur_Or : public Travailleur
{
public:
    Travailleur_Or(bool active = true);
    virtual ~Travailleur_Or();

    virtual QString getInfo();
};

#endif // TRAVAILLEUR_OR_H
