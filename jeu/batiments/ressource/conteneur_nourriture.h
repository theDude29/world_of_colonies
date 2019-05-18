#ifndef CONTENEUR_NOURRITURE_H
#define CONTENEUR_NOURRITURE_H

#include "jeu/batiments/ressource/conteneur.h"

#define MAX_PV_CONTENEUR_NOURRITURE 100
#define COUT_CONSTRUCTION_CONTENEUR_NOURRITURE_OR 100
#define COUT_CONSTRUCTION_CONTENEUR_NOURRITURE_NOURRITURE 50
#define TAILLE_CONTENEUR_NOURRITURE_W 10
#define TAILLE_CONTENEUR_NOURRITURE_H 10
#define CONTENANCE_MAX_CONTENEUR_NOURRITURE 300

class Conteneur_nourriture : public Conteneur
{
public:
    Conteneur_nourriture();
    virtual ~Conteneur_nourriture();

    virtual QString getInfo();
};

#endif // CONTENEUR_NOURRITURE_H
