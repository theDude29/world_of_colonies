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
    Q_OBJECT;

public:
    Item();
    ~Item();
    static QString getInfo();
    virtual cout getCout();
    void setVisible(bool visible);
    irr::scene::IMeshSceneNode* getMeshSceneNode();

protected:
    cout m_cout;
    irr::scene::IMeshSceneNode* m_meshSceneNode;
    irr::video::ITexture* m_texture;
};

#endif // ITEM_H
