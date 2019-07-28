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
    void setIdFichierVillage(int id);
    void setId(int id);
    void setPseudo(QString pseudo);

    int getIdFichierVillage();
    int getType();
    int getId();
    bool isVisible();

    virtual void estVise();
    virtual void estPlusVise();
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
    irr::scene::IMesh *m_meshBatiment;
};

#endif // BATIMENT_H
