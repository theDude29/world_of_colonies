#ifndef TRAVAILLEUR_NOURRITURE_H
#define TRAVAILLEUR_NOURRITURE_H

#include "jeu/batiments/ressource/travailleur.h"

#define MAX_PV_TRAVAILLEUR_NOURRITURE 50
#define COUT_CONSTRUCTION_TRAVAILLEUR_NOURRITURE_OR 70
#define COUT_CONSTRUCTION_TRAVAILLEUR_NOURRITURE_NOURRITURE 30
#define TAILLE_TRAVAILLEUR_NOURRITURE_W 10
#define TAILLE_TRAVAILLEUR_NOURRITURE_H 10
#define CONTENANCE_MAX_TRAVAILLEUR_NOURRITURE 80
#define PRODUCTIVITE_TRAVAILLEUR_NOURRITURE 10

class Travailleur_Nourriture : public Travailleur
{
public:
    Travailleur_Nourriture(bool active = true);
    virtual ~Travailleur_Nourriture();

    virtual QString getInfo();
};

#endif // TRAVAILLEUR_NOURRITURE_H
