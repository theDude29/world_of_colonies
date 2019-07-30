#ifndef TRAVAILLEUR_H
#define TRAVAILLEUR_H

#include <irrlicht/irrlicht.h>
#include "jeu/batiments/ressource/conteneur.h"
#include <QPushButton>
#include <QCoreApplication>
#include <QLabel>

#define XP_TRAVAILLEUR 30
#define TEMPS_CONSTRUCTION_TRAVAILLEUR 2

class Travailleur : public Conteneur
{
    Q_OBJECT

public:
    Travailleur(QObject* parent, int maxPV, QSize taille, cout coutDeConstruction, int contenanceMax, int productivite, bool active = true);

    void majPosBoutonCollecte(int hauteur);
    void cacherBoutonCollecte();
    virtual void kill(bool Detruit = false);

protected:
    int m_productivite;
    QPushButton* m_boutonCollecte;

public slots:
    void verifierTiming();
    void recolterRessource();

signals:
    void gagneDesRessources(int nb);
};

#endif // TRAVAILLEUR_H
