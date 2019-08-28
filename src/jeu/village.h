#ifndef VILLAGE_H
#define VILLAGE_H

#include <irrlicht/irrlicht.h>
#include <QObject>
#include <QEvent>
#include <QProgressBar>
#include <QLabel>
#include <QMouseEvent>
#include <QMessageBox>
#include <vector>
#include "../gui/widgetoptionsbatiments.h"
#include "../singleton/Driver.h"
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
#include "../bdd/bdd.h"
#include "armee.h"

#define TAILLE_CASE 20

class Village : public QObject
{
    Q_OBJECT

public:
    Village(QWidget* parent, QString pseudo, QProgressBar* pbNiveau, QLabel* lbNiveau, QProgressBar* pbOr, QProgressBar* pbNourriture);
    ~Village();
    virtual bool eventFilter(QObject *obj, QEvent *event);

    std::vector<Travailleur*> getListeTravailleur();
    int getNbOr();
    int getNbNourriture();
    irr::scene::ITriangleSelector* getTerrainSelector();
    void perdreRessource(cout nb);
    void setArmee(Armee* armee);
    void setNiveau(int niveau, int xp);
    void setNbOr(int nbOr);
    void setNbNourriture(int nbNourriture);
    bool PortailDansLeVillage();
    bool campEntrainementDansLeVillage();
    void afficherBoutonRessource(bool vrai);

    bool essayerConstruireBatiment(Batiment *batiment);
    void majPosBatimentAConstruire(irr::core::vector2di posMouse);
    bool collisionEntreBatiment();
    void construireBatiment(bool gratuitement = false);
    void ajouterBatiment();
    void gagneDeLXp(int xp);
    bool batimentVise(irr::core::vector2di posMouse);

    int creerIdFichierVillage(int typeBat);
    void supprimerIdFichierVillage(int typeBat, int id);
    void genererVillage();
    void genererTypeBatiment(typeBatiment typeBat, QString fichier);

private:
    QWidget* m_mainWindow;

    //partie importante de irrlicht;
    irr::scene::ISceneManager* m_sceneManager;
    irr::video::IVideoDriver* m_driver;
    irr::scene::ISceneCollisionManager* m_collisionManager;

    //
    Armee* m_armee;

    //stat
    QString m_pseudo;
    int m_nbMaxOr, m_nbOr, m_nbMaxNourriture, m_nbNourriture,
    m_nbXpMax, m_nbXp, m_niveau;

    QProgressBar* m_pbNiveau, *m_pbOr, *m_pbNourriture;
    QLabel* m_lbNiveau;

    int m_nbMaison, m_nbUsine, m_nbBanque, m_nbEntrepot
    ,m_nbCamp, m_nbCaserne, m_nbPortail,
    m_nbCanon, m_nbTourelle, m_nbMortier;

    //terrain
    irr::scene::IMeshSceneNode* m_terrain;
    irr::scene::ITriangleSelector* m_terrainSelector;
    std::vector<irr::scene::ITriangleSelector*> m_batsSelectors;

    //autre
    WidgetOptionsBatiments* m_WidgetOptionsBats;
    Batiment* m_batimentSelectionne;
    Batiment* m_batimentADeplacer;
    bool m_leBatimentEtaitDejaConstruit;
    std::vector<Batiment*> m_listeBatiments;

signals:
    void onPlaceBatiment();
    void onArretePlacerBatiment();

    void majNbCaserne(int nb);

public slots:
    void cacherBatiments();
    void afficherBatiments();

    void deplacerBatiment();
    void vendreBatiment();
    void pivoterDroite();
    void pivoterGauche();
    void quitterOptionBat();

    void gagneNourriture(int nbNourriture);
    void gagneOr(int nbOr);
};

#endif // VILLAGE_H
