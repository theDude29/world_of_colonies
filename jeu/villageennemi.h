#ifndef VILLAGEENNEMI_H
#define VILLAGEENNEMI_H

#include <vector>
#include "jeu/batiments/batiment.h"
#include "jeu/batiments/hoteldeville.h"
#include "jeu/batiments/ressource/travailleur_or.h"
#include "jeu/batiments/ressource/travailleur_nourriture.h"
#include "jeu/batiments/ressource/conteneur_nourriture.h"
#include "jeu/batiments/ressource/conteneur_or.h"
#include "jeu/batiments/armee/campentrainement.h"
#include "jeu/batiments/armee/caserne.h"
#include "jeu/batiments/armee/portail.h"
#include "jeu/batiments/defense/canon.h"
#include "jeu/batiments/defense/tourelle.h"
#include "jeu/batiments/defense/mortier.h"
#include "jeu/armee.h"

enum typeSoldat
{
    artilleur,
    fantassin,
    tank
};

class VillageEnnemi : public QObject
{
    Q_OBJECT

public:
    VillageEnnemi(QWidget* parent, QString pseudo, Armee* armee, QLabel* texteInfoEnnemie, QPushButton* bouttonArtilleur, QPushButton* bouttonFantassin, QPushButton* boutonTank, irr::scene::ITriangleSelector* triangleSelector);
    ~VillageEnnemi();
    void genererVillage(QString fichier);
    void genererTypeBatiment(typeBatiment typeBat, QString fichier);

    void majSoldatSelectionne();

    void majTextBouttons();

private:
    irr::scene::ISceneCollisionManager* m_collisionSceneManager;
    irr::scene::ITriangleSelector* m_terrainSelector;

    QString m_pseudo, m_pseudoEnnemi;

    Armee* m_armee;
    std::vector<Batiment*> m_listeBatiments;

    Soldat* m_soldatActuelle;

    QLabel* m_textInfoEnnemie;
    QPushButton* m_bouttonArtilleur, *m_bouttonFantassin, *m_boutonTank;

public slots:
    void genererVillageAuPif();
    void detruireVillage();

    void soldatActuelle_artilleur();
    void soldatActuelle_fantassin();
    void soldatActuelle_tank();
};

#endif // VILLAGEENNEMI_H
