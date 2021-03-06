#ifndef BATIMENT_H
#define BATIMENT_H

#include <QSize>
#include <QProgressBar>
#include "../../singleton/Driver.h"
#include "../item.h"

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
    Q_OBJECT

public:
    Batiment(QObject* parent, int maxPV, QSize taille, cout coutDeConstruction);
    virtual ~Batiment();
    virtual void kill(bool Detruit = false);

    void setPosition(irr::core::vector3df pos);
    void setIdFichierVillage(int id);
    void setId(int id);
    void setPseudo(QString pseudo);

    int getIdFichierVillage();
    int getType();
    int getId();

    virtual void estVise();
    virtual void estPlusVise();
    virtual void afficherBatimentConstruit();

protected:
    int m_id;
    int m_idFichierVillage;
    int m_typeBatiment;
    int m_tempsDeConstruction;
    QSize m_taille;
    QString m_pseudo;
    irr::scene::IMesh *m_meshBatiment;

signals:
    void detruit();
};

#endif // BATIMENT_H
