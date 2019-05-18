#ifndef BATIMENT_H
#define BATIMENT_H

#include <QSize>
#include <QObject>
#include <QString>
#include <QProgressBar>
#include <irrlicht/IMeshSceneNode.h>
#include "singleton/SceneManager.h"
#include "singleton/Driver.h"

struct cout
{
    int nbNourriture;
    int nbOr;
    int nbXp;
};

enum typeBatiment
{
    hdv,
    travailleurNourriture,
    travailleurOr,
    conteneurOr,
    conteneurNourriture,
    campEntrainement,
    caserne,
    portail,
    canon,
    tourelle,
    mortier
};

class Batiment : public QObject
{
    Q_OBJECT

public:
    Batiment(int maxPV, QSize taille, cout coutDeConstruction);
    virtual ~Batiment();

    void setPosition(irr::core::vector3df pos);
    void setRotation(irr::core::vector3df rot);
    void setIdFichierVillage(int id);
    void setId(int id);
    void setPseudo(QString pseudo);

    int getIdFichierVillage();
    virtual QString getInfo() = 0;
    cout getCout();
    int getType();
    irr::video::ITexture* getTexture();
    irr::scene::IMeshSceneNode* getMeshSceneNode();
    irr::core::vector3df getPosition();
    irr::core::vector3df getRotation();
    int getId();
    bool isVisible();

    virtual void estVise();
    virtual void estPlusVise();
    virtual void kill();
    virtual void afficherBatimentConstruit();

protected:
    int m_id;
    int m_idFichierVillage;
    int m_typeBatiment;
    int m_maxPV;
    int m_tempsDeConstruction;
    irr::scene::ISceneCollisionManager* m_sceneCollisionManager;
    QSize m_taille;
    QString m_pseudo;
    cout m_cout;
    irr::scene::IMeshSceneNode* m_meshSceneNode;
    irr::scene::IMesh *m_meshBatiment;
    irr::video::ITexture* m_texture;
};

#endif // BATIMENT_H
