#ifndef DEFENSE_H
#define DEFENSE_H

#include "jeu/batiments/batiment.h"

class Defense : public Batiment
{
public:
    Defense(QObject* parent, int maxPV, QSize taille, cout coutDeConstruction);
    virtual void estVise();
    virtual void estPlusVise();

protected:
    int m_porte;
    irr::scene::IMeshSceneNode* m_spherePorte;
    int m_dps;
};

#endif // DEFENSE_H
