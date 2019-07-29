#ifndef CONTENEUR_OR_H
#define CONTENEUR_OR_H

#include "jeu/batiments/ressource/conteneur.h"

#define MAX_PV_CONTENEUR_OR 100
#define COUT_CONSTRUCTION_CONTENEUR_OR_OR 100
#define COUT_CONSTRUCTION_CONTENEUR_OR_NOURRITURE 50
#define TAILLE_CONTENEUR_OR_W 10
#define TAILLE_CONTENEUR_OR_H 10
#define CONTENANCE_MAX_CONTENEUR_OR 300

class Conteneur_Or : public Conteneur
{
public:
    Conteneur_Or(QObject* parent);
    virtual ~Conteneur_Or();

    virtual QString getInfo();
};

#endif // CONTENEUR_OR_H
