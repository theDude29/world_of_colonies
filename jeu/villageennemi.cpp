#include "villageennemi.h"
#include "iostream"
#include "bdd/bdd.h"

VillageEnnemi::VillageEnnemi(QObject* parent, QString pseudo) : QObject(parent)
{
    m_pseudo = pseudo;
}

void VillageEnnemi::genererVillage(QString fichier)
{
    //info de tout
    QStringList listInfos = fichier.split('.');
    QStringList::iterator itInfos = listInfos.begin();

    //niveau (on sen fout)
    QStringList listInfosNiveau = (*itInfos).split(';');
    itInfos++;

    //nombre ressource (on sen fout)
    QStringList listInfosNbRessource = (*itInfos).split(',');
    itInfos++;

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
            batimentAConstuire = new Travailleur_Nourriture;
            break;

        case travailleurOr:
            batimentAConstuire = new Travailleur_Or;
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

    QString pseudoEnnemi = Bdd::getBdd()->getPseudoAuPif();
    while(pseudoEnnemi == m_pseudo)
    {
        pseudoEnnemi = Bdd::getBdd()->getPseudoAuPif();
    }
    std::cout<<pseudoEnnemi.toStdString()<<std::endl;

    QString fichierVillage = Bdd::getBdd()->getFichierVillage(pseudoEnnemi);

    genererVillage(fichierVillage);

}

void VillageEnnemi::detruireVillage()
{
    std::vector<Batiment*>::iterator it = m_listeBatiments.begin();
    for(it; it != m_listeBatiments.end(); ++it)
    {
        (*it)->kill();
    }

    for(unsigned int i = 0; i < m_listeBatiments.size(); ++i)
    {
        m_listeBatiments.pop_back();
    }
}

VillageEnnemi::~VillageEnnemi()
{
    detruireVillage();
}
