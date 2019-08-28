#include "conteneur.h"

Conteneur::Conteneur(QObject *parent, int maxPV, QSize taille, cout coutDeConstruction, int contenanceMax) : Batiment(parent, maxPV, taille, coutDeConstruction)
{
    m_texture = Driver::getDriver()->getTexture("mesh/texture/textureRessource.png");
    m_contenanceMax = contenanceMax;
    m_contenance = 0;
    m_tempsDeConstruction = TEMPS_CONSTRUCTION_CONTENEUR;
}

int Conteneur::getContenanceMax()
{
    return m_contenanceMax;
}

