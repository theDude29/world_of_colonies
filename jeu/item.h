#ifndef ITEM_H
#define ITEM_H

#include <irrlicht/irrlicht.h>
#include <QString>
#include <QObject>
#include <QProgressBar>
#include "singleton/SceneManager.h"

struct cout
{
    int nbNourriture;
    int nbOr;
    int nbXp;
};

class Item : public QObject
{
    Q_OBJECT;

public:
    Item(QObject* parent, int maxPV = 0);
    ~Item();
    static QString getInfo();
    virtual cout getCout();
    irr::video::ITexture* getTexture();
    irr::core::vector3df getPosition();
    irr::core::vector3df getRotation();
    void setRotation(irr::core::vector3df rot);
    virtual void kill();
    void setVisible(bool visible);
    irr::scene::IMeshSceneNode* getMeshSceneNode();
    bool prendreDesPV(int nbPv);

protected:
    int m_maxPV, m_pvActuelle;
    bool m_intact;
    cout m_cout;
    irr::scene::IMeshSceneNode* m_meshSceneNode;
    irr::video::ITexture* m_texture;
    QProgressBar* m_pbPV;
    irr::scene::ISceneCollisionManager* m_sceneCollisionManager;
};

#endif // ITEM_H
