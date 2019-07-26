#include "villageennemi.h"
#include "iostream"
#include "bdd/bdd.h"

VillageEnnemi::VillageEnnemi(QWidget* parent, QString pseudo, Armee* armee, QLabel* texteInfoEnnemie, QPushButton* bouttonArtilleur, QPushButton* bouttonFantassin, QPushButton* boutonTank, irr::scene::ITriangleSelector* triangleSelector) : QObject(parent)
{
    m_collisionSceneManager = SceneManager::getSceneManager()->getSceneCollisionManager();
    m_terrainSelector = triangleSelector;

    m_pseudo = pseudo;

    m_armee = armee;

    m_soldatActuelle = new Artilleur;

    m_textInfoEnnemie = texteInfoEnnemie;
    //
    m_bouttonArtilleur = bouttonArtilleur;
    connect(m_bouttonArtilleur, SIGNAL(clicked(bool)), this, SLOT(soldatActuelle_artilleur()));
    m_bouttonFantassin = bouttonFantassin;
    connect(m_bouttonFantassin, SIGNAL(clicked(bool)), this, SLOT(soldatActuelle_fantassin()));
    m_boutonTank = boutonTank;
    connect(m_boutonTank, SIGNAL(clicked(bool)), this, SLOT(soldatActuelle_tank()));
}

void VillageEnnemi::majSoldatSelectionne()
{
    irr::core::line3df line;
    //line = m_collisionSceneManager->getRayFromScreenCoordinates(posMouse);

    irr::core::vector3df pos;
    irr::core::triangle3df tri;
    irr::scene::ISceneNode* node;
    if(m_collisionSceneManager->getCollisionPoint(line, m_terrainSelector, pos, tri, node))
    {
        m_soldatActuelle->setPosition(pos);
    }

    /*if(collisionEntreBatiment())
    {
        m_batimentADeplacer->getMeshSceneNode()->setMaterialTexture(0, Driver::getDriver()->getTexture("mesh/texture/rouge.jpg"));
    }

    else
    {
        m_batimentADeplacer->getMeshSceneNode()->setMaterialTexture(0, Driver::getDriver()->getTexture("mesh/texture/vert.jpg"));
    }*/
}

void VillageEnnemi::genererVillage(QString fichier)
{
    //info de tout
    QStringList listInfos = fichier.split('.');
    QStringList::iterator itInfos = listInfos.begin();

    //info joueurs :
    QString infoJoueur = m_pseudoEnnemi;

    //niveau
    QStringList listInfosNiveau = (*itInfos).split(';');
    itInfos++;
    QStringList::iterator itInfosNiveau = listInfosNiveau.begin();
    int niveau = (*itInfosNiveau).toInt();
    //
    infoJoueur += " (niveau " + QString::number(niveau) + ") : ";

    //nombre ressource (on
    QStringList listInfosNbRessource = (*itInfos).split(',');
    itInfos++;
    QStringList::iterator itInfosNbResssource = listInfosNbRessource.begin();
    int nombreOr = (*itInfosNbResssource).toInt();
    itInfosNbResssource++;
    int nombreNourriture = (*itInfosNbResssource).toInt();
    //
    infoJoueur += QString::number(nombreOr) + " or, " + QString::number(nombreNourriture) + " nourriture";

    m_textInfoEnnemie->setText(infoJoueur);

    //batiment :

    //hdv
    QString infosHdv = (*itInfos);
    itInfos++;
    genererTypeBatiment(hdv, infosHdv);

    //maison
    QString infosmaison = (*itInfos);
    itInfos++;
    genererTypeBatiment(travailleurNourriture, infosmaison);

    //usine
    QString infosUsine = (*itInfos);
    itInfos++;
    genererTypeBatiment(travailleurOr, infosUsine);

    //banque
    QString infosBanque = (*itInfos);
    itInfos++;
    genererTypeBatiment(conteneurOr, infosBanque);

    //entrepot
    QString infosEntrepot = (*itInfos);
    itInfos++;
    genererTypeBatiment(conteneurNourriture, infosEntrepot);

    //camp
    QString infosCamp = (*itInfos);
    itInfos++;
    genererTypeBatiment(campEntrainement, infosCamp);

    //caserne
    QString infosCaserne = (*itInfos);
    itInfos++;
    genererTypeBatiment(caserne, infosCaserne);

    //portail
    QString infosPortail = (*itInfos);
    itInfos++;
    genererTypeBatiment(portail, infosPortail);

    //canon
    QString infosCanon = (*itInfos);
    itInfos++;
    genererTypeBatiment(canon, infosCanon);

    //tourelle
    QString infosTourelle = (*itInfos);
    itInfos++;
    genererTypeBatiment(tourelle, infosTourelle);

    //mortier
    QString infosMortier = (*itInfos);
    itInfos++;
    genererTypeBatiment(mortier, infosMortier);
}

void VillageEnnemi::genererTypeBatiment(typeBatiment typeBat, QString fichier)
{
    //on separe les types d infos
    QStringList listInfos = fichier.split(';');
    QStringList::iterator itInfos = listInfos.begin();

    //le nombre de batiment est la premiere info
    irr::s32 nbBats = 0;
    nbBats = (*itInfos).toInt();
    itInfos++;

    Batiment* batimentAConstuire;
    for(int i = 0; i < nbBats; ++i)
    {
        switch(typeBat)
        {
        case hdv:
            batimentAConstuire = new HotelDeVille;
            break;

        case travailleurNourriture:
            batimentAConstuire = new Travailleur_Nourriture(false);
            break;

        case travailleurOr:
            batimentAConstuire = new Travailleur_Or(false);
            break;

        case conteneurNourriture:
            batimentAConstuire = new Conteneur_nourriture;
            break;

        case conteneurOr:
            batimentAConstuire = new Conteneur_Or;
            break;

        case campEntrainement:
            batimentAConstuire = new CampEntrainement;
            break;

        case caserne:
            batimentAConstuire = new Caserne;
            break;

        case portail:
            batimentAConstuire = new Portail;
            break;

        case canon:
            batimentAConstuire = new Canon;
            break;

        case tourelle:
            batimentAConstuire = new Tourelle;
            break;

        case mortier:
            batimentAConstuire = new Mortier;
            break;

        default:
            break;
        }

        //les positions sont les infos suivantes
        QStringList listPos;
        QStringList::iterator itPos;

        irr::f32 pos_x = 0, pos_z = 0;
        irr::s32 rot = 0;

        //on separe les coordonnees x et y
        listPos = (*itInfos).split(',');

        //on extrait les infos
        itPos = listPos.begin();
        pos_x = (*itPos).toFloat();
        itPos++;
        pos_z = (*itPos).toFloat();

        batimentAConstuire->setPosition(irr::core::vector3df(pos_x, 1, pos_z));

        //rotation
        itInfos++;
        rot = (*itInfos).toInt();
        batimentAConstuire->setRotation(irr::core::vector3df(0, rot, 0));

        //on construi
        batimentAConstuire->afficherBatimentConstruit();

        m_listeBatiments.push_back(batimentAConstuire);

        //on passe au paquet de position suivant
        itInfos++;
    }
}

void VillageEnnemi::genererVillageAuPif()
{
    detruireVillage();

    m_textInfoEnnemie->setVisible(true);
    majTextBouttons();

    QString pseudoEnnemi = Bdd::getBdd()->getPseudoAuPif();
    while(pseudoEnnemi == m_pseudo)
    {
        pseudoEnnemi = Bdd::getBdd()->getPseudoAuPif();
    }
    m_pseudoEnnemi = pseudoEnnemi;

    QString fichierVillage = Bdd::getBdd()->getFichierVillage(pseudoEnnemi);

    genererVillage(fichierVillage);

}

void VillageEnnemi::detruireVillage()
{
    for(std::vector<Batiment*>::iterator it = m_listeBatiments.begin(); it != m_listeBatiments.end(); ++it)
    {
        (*it)->kill();
    }

    for(unsigned int i = 0; i < m_listeBatiments.size(); ++i)
    {
        m_listeBatiments.pop_back();
    }
}

void VillageEnnemi::soldatActuelle_artilleur()
{
    delete m_soldatActuelle;
    m_soldatActuelle = new Artilleur;
}

void VillageEnnemi::soldatActuelle_fantassin()
{
    delete m_soldatActuelle;
    m_soldatActuelle = new Fantassin;
}

void VillageEnnemi::soldatActuelle_tank()
{
    delete m_soldatActuelle;
    m_soldatActuelle = new Tank;
}

void VillageEnnemi::majTextBouttons()
{
    m_bouttonArtilleur->setText("Artilleur (" + QString::number(m_armee->getNbArtilleur()) + " unite(s))");
    m_bouttonFantassin->setText("Fantassin (" + QString::number(m_armee->getNbFantassin()) + " unite(s))");
    m_boutonTank->setText("Tank (" + QString::number(m_armee->getNbTank()) + " unite(s))");
}

VillageEnnemi::~VillageEnnemi()
{
    delete m_soldatActuelle;
    detruireVillage();
}
