#ifndef CONTENEUR_H
#define CONTENEUR_H

#include "../batiment.h"

#define XP_CONTENEUR 50
#define TEMPS_CONSTRUCTION_CONTENEUR 5

class Conteneur : public Batiment
{
public:
    Conteneur(QObject* parent, int maxPV, QSize taille, cout coutDeConstruction, int contenanceMax);
    virtual int getContenanceMax();

protected:
    int m_contenanceMax;
    int m_contenance;
};

#endif // CONTENEUR_H
