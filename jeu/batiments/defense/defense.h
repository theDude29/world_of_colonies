#ifndef DEFENSE_H
#define DEFENSE_H

#include "jeu/batiments/batiment.h"
#include "jeu/soldats/soldat.h"

class Defense : public Batiment
{
public:
    Defense(QObject* parent, int maxPV, QSize taille, cout coutDeConstruction);
    void attaque(irr::core::vector3df direction,irr::core::vector3df posCible, std::vector<Soldat*> *listeSoldats);
    virtual void estVise();
    virtual void estPlusVise();
    int getPorte();

protected:
    irr::ITimer* m_timer;
    irr::u32 m_heureDerniereAttaque;
    int m_porte, m_vitesseAttaque, m_degat, m_tailleProjectile;
    irr::scene::IMeshSceneNode* m_spherePorte;
    int m_dps;
};

#endif // DEFENSE_H
