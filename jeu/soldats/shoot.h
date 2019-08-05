#ifndef SHOOT_H
#define SHOOT_H

#include <QObject>
#include <vector>
#include <irrlicht/irrlicht.h>
#include "jeu/item.h"
#include "jeu/batiments/batiment.h"
#include "jeu/soldats/soldat.h"

#define VITESSE 20

class Shoot : public Item
{
    Q_OBJECT
public:
    Shoot(QObject *parent, int degat, std::vector<Batiment*> *listeBatiment, irr::core::vector3df pos, int taille, irr::core::vector3df direction);
    Shoot(QObject *parent, int degat, std::vector<Soldat*> *listeSoldat, irr::core::vector3df pos, int taille, irr::core::vector3df direction, irr::core::vector3df posCible);
    virtual void kill();

protected:
    irr::scene::ISceneCollisionManager* m_collisionManager;
    std::vector<Batiment*> *m_listeBatiment;
    std::vector<Soldat*> *m_listeSoldat;
    irr::core::vector3df m_direction;
    int m_degat;
    irr::scene::ILightSceneNode* m_meshSceneNode;
    QTimer* m_timer;

    //shoot mortier
    irr::core::vector3df m_posCible;
    bool m_shootMortier;
    double m_longueur;
    double m_coefficient;
    double m_hauteurMax;
    double m_x;

signals:

public slots:
        void maj();
};

#endif // SHOOT_H
