#include "villageennemi.h"
#include "iostream"
#include "bdd/bdd.h"
#include <QMouseEvent>

VillageEnnemi::VillageEnnemi(QWidget* parent, QString pseudo, Village* village, Armee* armee, QLabel* texteInfoEnnemie, QPushButton* bouttonArtilleur, QPushButton* bouttonFantassin, QPushButton* boutonTank, QLabel* textVictoire, irr::scene::ITriangleSelector* triangleSelector) : QObject(parent)
{
    m_mainWindow = parent;
    m_village = village;
    m_enAction = false;

    m_collisionSceneManager = SceneManager::getSceneManager()->getSceneCollisionManager();
    m_terrainSelector = triangleSelector;

    m_gestionnaireAttaque = new GestionAttaqueVillage(this, textVictoire);

    m_pseudo = pseudo;

    m_armee = armee;
    m_nbArtilleur = m_armee->getNbArtilleur();
    m_nbFantassin = m_armee->getNbFantassin();
    m_nbTank = m_armee->getNbTank();

    m_soldatActuelle = new Artilleur(this);

    m_pasDeSoldatSelectionnerEnReserve = false;

    m_textInfoEnnemie = texteInfoEnnemie;
    m_textVictoire = textVictoire;
    //
    m_bouttonArtilleur = bouttonArtilleur;
    connect(m_bouttonArtilleur, SIGNAL(clicked(bool)), this, SLOT(soldatActuelle_artilleur()));
    m_bouttonFantassin = bouttonFantassin;
    connect(m_bouttonFantassin, SIGNAL(clicked(bool)), this, SLOT(soldatActuelle_fantassin()));
    m_boutonTank = boutonTank;
    connect(m_boutonTank, SIGNAL(clicked(bool)), this, SLOT(soldatActuelle_tank()));
}

void VillageEnnemi::majSoldatSelectionne(irr::core::vector2di posMouse)
{
    irr::core::line3df line;
    line = m_collisionSceneManager->getRayFromScreenCoordinates(posMouse);

    irr::core::vector3df pos;
    irr::core::triangle3df tri;
    irr::scene::ISceneNode* node;
    if(m_collisionSceneManager->getCollisionPoint(line, m_terrainSelector, pos, tri, node))
    {
        m_soldatActuelle->setPosition(pos);
    }

    if(collisionAvecBatiment() || m_pasDeSoldatSelectionnerEnReserve)
    {
        m_soldatActuelle->getMeshSceneNode()->setMaterialTexture(0, Driver::getDriver()->getTexture("mesh/texture/rouge.jpg"));
    }

    else
    {
        m_soldatActuelle->getMeshSceneNode()->setMaterialTexture(0, Driver::getDriver()->getTexture("mesh/texture/vert.jpg"));
    }
}

bool VillageEnnemi::collisionAvecBatiment()
{
    irr::core::aabbox3df bb_soldatActuelle = m_soldatActuelle->getMeshSceneNode()->getTransformedBoundingBox();
    irr::core::aabbox3df bb_autreBatiment;
    bool collision = false;

    for(unsigned int i = 0; i < m_listeBatiments.size(); i++)
    {
            if(m_listeBatiments[i]->isVisible())
            {
                bb_autreBatiment =  m_listeBatiments[i]->getMeshSceneNode()->getTransformedBoundingBox();
                if(bb_autreBatiment.intersectsWithBox(bb_soldatActuelle))
                {
                    collision = true;
                }
            }
    }

   return collision;
}

bool VillageEnnemi::eventFilter(QObject *obj, QEvent *event)
{
        QMouseEvent* mouseEvent = NULL;

            switch(event->type())
            {
            case QEvent::MouseMove:
                mouseEvent = (QMouseEvent*)event;
                majSoldatSelectionne(irr::core::vector2di(mouseEvent->x(), mouseEvent->y()));
                break;

            case QEvent::MouseButtonPress:
                mouseEvent = (QMouseEvent*)event;
                if(mouseEvent->button() == Qt::LeftButton)
                {
                    if(!collisionAvecBatiment() && !m_pasDeSoldatSelectionnerEnReserve && m_enAction)
                    {
                        m_gestionnaireAttaque->ajouterTroupe(m_soldatActuelle->getType(), m_soldatActuelle->getPosition());

                        switch(m_soldatActuelle->getType())
                        {
                        case artilleur:
                            m_nbArtilleur--;
                            //Bdd::getBdd()->setNbArtilleur(m_pseudo, m_nbArtilleur);
                            soldatActuelle_artilleur();
                            break;
                        case fantassin:
                            m_nbFantassin--;
                            //Bdd::getBdd()->setNbFantassin(m_pseudo, m_nbFantassin);
                            soldatActuelle_fantassin();
                            break;
                        case tank:
                            m_nbTank--;
                            //Bdd::getBdd()->setNbTank(m_pseudo, m_nbTank);
                            soldatActuelle_tank();
                            break;
                        default: break;
                        }
                        majTextBouttons();
                    }
                }
                break;

            default : break;
            }

    return QObject::eventFilter(obj, event);
}

void VillageEnnemi::genererVillage(QString fichier)
{
    //info de tout
    QStringList listInfos = fichier.split('.');
    QStringList::iterator itInfos = listInfos.begin();

    //info joueur ennemie
    //niveau
    QStringList listInfosNiveau = (*itInfos).split(';');
    itInfos++;
    QStringList::iterator itInfosNiveau = listInfosNiveau.begin();
    m_lvlEnnemi = (*itInfosNiveau).toInt();
    //
    //nombre ressource
    QStringList listInfosNbRessource = (*itInfos).split(',');
    itInfos++;
    QStringList::iterator itInfosNbResssource = listInfosNbRessource.begin();
    m_nbOrEnnemie = (*itInfosNbResssource).toInt();
    itInfosNbResssource++;
    m_nbNourritureEnnemie = (*itInfosNbResssource).toInt();
    //
    majTextEnnemie();

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

void VillageEnnemi::majTextEnnemie()
{
    //info joueurs :
    //pseudo
    QString infoJoueur = m_pseudoEnnemi;
    //niveau
    infoJoueur += " (niveau " + QString::number(m_lvlEnnemi) + ") : ";
    //ressource
    infoJoueur += QString::number(m_nbOrEnnemie) + " or, " + QString::number(m_nbNourritureEnnemie) + " nourriture";
    //
    m_textInfoEnnemie->setText(infoJoueur);
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
            batimentAConstuire = new HotelDeVille(this);
            break;

        case travailleurNourriture:
            batimentAConstuire = new Travailleur_Nourriture(this, false);
            break;

        case travailleurOr:
            batimentAConstuire = new Travailleur_Or(this, false);
            break;

        case conteneurNourriture:
            batimentAConstuire = new Conteneur_nourriture(this);
            break;

        case conteneurOr:
            batimentAConstuire = new Conteneur_Or(this);
            break;

        case campEntrainement:
            batimentAConstuire = new CampEntrainement(this);
            break;

        case caserne:
            batimentAConstuire = new Caserne(this);
            break;

        case portail:
            batimentAConstuire = new Portail(this);
            break;

        case canon:
            batimentAConstuire = new Canon(this);
            break;

        case tourelle:
            batimentAConstuire = new Tourelle(this);
            break;

        case mortier:
            batimentAConstuire = new Mortier(this);
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

        connect(batimentAConstuire, SIGNAL(detruit()), this, SLOT(batimentDetruit()));
        m_listeBatiments.push_back(batimentAConstuire);

        //on passe au paquet de position suivant
        itInfos++;
    }
}

void VillageEnnemi::genererVillageAuPif()
{
    if(m_village->getNbOr() >= 50)
    {
        detruireVillage();
        m_enAction = true;
        m_textVictoire->setVisible(false);
        m_village->setNbOr(m_village->getNbOr() - 50);

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

        int nbBatiment = m_listeBatiments.size();
        double ratioBat = 1.0 / nbBatiment;
        m_valeurOrBatimentEnnemie = m_nbOrEnnemie * ratioBat;
        m_valeurNourritureBatimentEnnemie = m_nbNourritureEnnemie * ratioBat;

        m_gestionnaireAttaque->setListeBatiment(m_listeBatiments);
    }

    else
    {
        QMessageBox::critical(m_mainWindow, "Erreur", "Vous n'avez pas assez d'argent pour vous teleporter dans un village ennemie (50 or).");
    }
}

void VillageEnnemi::batimentDetruit()
{
    m_village->gagneDeLXp(300);
    m_village->setNbOr(m_village->getNbOr() + m_valeurOrBatimentEnnemie);
    m_nbOrEnnemie -= m_valeurOrBatimentEnnemie;
    m_village->setNbNourriture(m_village->getNbNourriture() + m_valeurNourritureBatimentEnnemie);
    m_nbNourritureEnnemie -= m_valeurNourritureBatimentEnnemie;

    Bdd::getBdd()->majNbRessource(m_pseudoEnnemi, m_nbOrEnnemie, m_nbNourritureEnnemie);

    majTextEnnemie();
}

void VillageEnnemi::detruireVillage()
{
    for(std::vector<Batiment*>::iterator it = m_listeBatiments.begin(); it != m_listeBatiments.end(); ++it)
    {
        (*it)->kill();
    }

    m_listeBatiments.clear();

    m_gestionnaireAttaque->detruireTroupe();

    m_enAction = false;

    m_textVictoire->setVisible(false);
}

void VillageEnnemi::soldatActuelle_artilleur()
{
    delete m_soldatActuelle;
    m_soldatActuelle = new Artilleur(this);

    if(m_nbArtilleur < 1)
    {
        m_pasDeSoldatSelectionnerEnReserve = true;
    }

    else
    {
        m_pasDeSoldatSelectionnerEnReserve = false;
    }
}

void VillageEnnemi::soldatActuelle_fantassin()
{
    delete m_soldatActuelle;
    m_soldatActuelle = new Fantassin(this);

    if(m_nbFantassin < 1)
    {
        m_pasDeSoldatSelectionnerEnReserve = true;
    }

    else
    {
        m_pasDeSoldatSelectionnerEnReserve = false;
    }
}

void VillageEnnemi::soldatActuelle_tank()
{
    delete m_soldatActuelle;
    m_soldatActuelle = new Tank(this);

    if(m_nbTank < 1)
    {
        m_pasDeSoldatSelectionnerEnReserve = true;
    }

    else
    {
        m_pasDeSoldatSelectionnerEnReserve = false;
    }
}

void VillageEnnemi::majTextBouttons()
{
    m_bouttonArtilleur->setText("Artilleur (" + QString::number(m_nbArtilleur) + " unite(s))");
    m_bouttonFantassin->setText("Fantassin (" + QString::number(m_nbFantassin) + " unite(s))");
    m_boutonTank->setText("Tank (" + QString::number(m_nbTank) + " unite(s))");
}

void VillageEnnemi::montrerSoldat(bool vrai)
{
    m_soldatActuelle->setVisible(vrai);
}

VillageEnnemi::~VillageEnnemi()
{
    delete m_gestionnaireAttaque;
    delete m_soldatActuelle;
    detruireVillage();
}
