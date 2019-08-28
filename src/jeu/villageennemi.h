#ifndef VILLAGEENNEMI_H
#define VILLAGEENNEMI_H

#include <vector>
#include "batiments/batiment.h"
#include "batiments/hoteldeville.h"
#include "batiments/ressource/travailleur_or.h"
#include "batiments/ressource/travailleur_nourriture.h"
#include "batiments/ressource/conteneur_nourriture.h"
#include "batiments/ressource/conteneur_or.h"
#include "batiments/armee/campentrainement.h"
#include "batiments/armee/caserne.h"
#include "batiments/armee/portail.h"
#include "batiments/defense/canon.h"
#include "batiments/defense/tourelle.h"
#include "batiments/defense/mortier.h"
#include "Gestionattaquevillage.h"
#include "village.h"

class VillageEnnemi : public QObject
{
    Q_OBJECT

public:
    VillageEnnemi(QWidget* parent, QString pseudo, Village* village, Armee* armee, QLabel* texteInfoEnnemie, QPushButton* bouttonArtilleur, QPushButton* bouttonFantassin, QPushButton* boutonTank, QLabel* textVictoire, irr::scene::ITriangleSelector* triangleSelector);
    ~VillageEnnemi();
    virtual bool eventFilter(QObject *obj, QEvent *event);

    void genererVillage(QString fichier);
    void genererTypeBatiment(typeBatiment typeBat, QString fichier);

    void majSoldatSelectionne(irr::core::vector2di posMouse);
    bool collisionAvecBatiment();
    void montrerSoldat(bool vrai);

    void majTextBouttons();
    void majTextEnnemie();

private:
    QWidget* m_mainWindow;
    Village* m_village;
    bool m_enAction;
    irr::scene::ISceneCollisionManager* m_collisionSceneManager;
    irr::scene::ITriangleSelector* m_terrainSelector;

    GestionAttaqueVillage* m_gestionnaireAttaque;

    QString m_pseudo, m_pseudoEnnemi;

    Armee* m_armee;
    std::vector<Batiment*> m_listeBatiments;
    int m_valeurOrBatimentEnnemie, m_valeurNourritureBatimentEnnemie;
    int m_lvlEnnemi;
    int m_nbOrEnnemie, m_nbNourritureEnnemie;
    int m_nbArtilleur, m_nbFantassin, m_nbTank;
    bool m_pasDeSoldatSelectionnerEnReserve;

    Soldat* m_soldatActuelle;

    QLabel* m_textInfoEnnemie, *m_textVictoire;
    QPushButton* m_bouttonArtilleur, *m_bouttonFantassin, *m_boutonTank;

public slots:
    void genererVillageAuPif();
    void detruireVillage();

    void soldatActuelle_artilleur();
    void soldatActuelle_fantassin();
    void soldatActuelle_tank();

    void batimentDetruit();
};

#endif // VILLAGEENNEMI_H
