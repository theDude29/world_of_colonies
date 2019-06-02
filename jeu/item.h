#ifndef ITEM_H
#define ITEM_H

#include <irrlicht/IMeshSceneNode.h>
#include <QString>
#include <QObject>

struct cout
{
    int nbNourriture;
    int nbOr;
    int nbXp;
};

class Item : public QObject
{
    Q_OBJECT

public:
    Item();
    virtual QString getInfo() = 0;

protected:
    irr::scene::IMeshSceneNode* m_meshSceneNode;
    irr::video::ITexture* m_texture;
};

#endif // ITEM_H
