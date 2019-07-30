#ifndef SHOOT_H
#define SHOOT_H

#include <QObject>
#include <irrlicht/irrlicht.h>
#include "jeu/item.h"
#include <vector>
#include "jeu/batiments/batiment.h"

#define VITESSE 20

class Shoot : public Item
{
    Q_OBJECT
public:
    explicit Shoot(QObject *parent, int degat, std::vector<Batiment*> *listeBatiment, irr::core::vector3df pos, int taille, irr::core::vector3df direction);
    virtual void kill();

protected:
    irr::scene::ISceneCollisionManager* m_collisionManager;
    std::vector<Batiment*> *m_listeBatiment;
    irr::core::vector3df m_direction;
    int m_degat;
    irr::scene::ILightSceneNode* m_meshSceneNode;
    QTimer* m_timer;

signals:

public slots:
        void maj();
};

#endif // SHOOT_H
