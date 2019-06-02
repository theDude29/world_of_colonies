#ifndef BATIMENT_H
#define BATIMENT_H

#include <QSize>
#include <QProgressBar>
#include "singleton/SceneManager.h"
#include "singleton/Driver.h"
#include "jeu/item.h"

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

class Batiment : public Item
{
public:
    Batiment(int maxPV, QSize taille, cout coutDeConstruction);
    virtual ~Batiment();

    void setPosition(irr::core::vector3df pos);
    void setRotation(irr::core::vector3df rot);
    void setIdFichierVillage(int id);
    void setId(int id);
    void setPseudo(QString pseudo);

    int getIdFichierVillage();
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
    irr::scene::IMesh *m_meshBatiment;
};

#endif // BATIMENT_H
