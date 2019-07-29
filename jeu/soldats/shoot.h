#ifndef SHOOT_H
#define SHOOT_H

#include <QObject>
#include <irrlicht/irrlicht.h>
#include "jeu/item.h"

#define VITESSE 20

class Shoot : public Item
{
    Q_OBJECT
public:
    explicit Shoot(QObject *parent, irr::core::vector3df pos, int taille, irr::core::vector3df direction);

protected:
    irr::core::vector3df m_direction;
    irr::scene::ILightSceneNode* m_meshSceneNode;

signals:

public slots:
        void maj();
};

#endif // SHOOT_H
