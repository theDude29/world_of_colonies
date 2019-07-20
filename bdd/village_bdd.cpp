#include "jeu/village.h"

int Village::creerIdFichierVillage(int typeBat)
{
    if(typeBat == hdv)
    {
        return 1;
    }

    if(typeBat == travailleurNourriture)
    {
        m_nbMaison++;
        return m_nbMaison;
    }

    if(typeBat == travailleurOr)
    {
        m_nbUsine++;
        return m_nbUsine;
    }

    if(typeBat == conteneurNourriture)
    {
        m_nbEntrepot++;
        return m_nbEntrepot;
    }

    if(typeBat == conteneurOr)
    {
        m_nbBanque++;
        return m_nbBanque;
    }

    if(typeBat == campEntrainement)
    {
        m_nbCamp++;
        return m_nbCamp;
    }

    if(typeBat == caserne)
    {
        m_nbCaserne++;
        return m_nbCaserne;
    }

    if(typeBat == portail)
    {
        m_nbPortail++;
        return m_nbPortail;
    }

    if(typeBat == canon)
    {
        m_nbCanon++;
        return m_nbCanon;
    }

    if(typeBat == tourelle)
    {
        m_nbTourelle++;
        return m_nbTourelle;
    }

    if(typeBat == mortier)
    {
        m_nbMortier++;
        return m_nbMortier;
    }

    return -1;
}

void Village::supprimerIdFichierVillage(int typeBat, int id)
{
    //on actualise le nombre de batiment
    switch(typeBat)
    {
    case travailleurNourriture:
        m_nbMaison--;
        break;
    case travailleurOr:
        m_nbUsine--;
        break;
    case conteneurOr:
        m_nbBanque--;
        break;
    case conteneurNourriture:
        m_nbEntrepot--;
    case campEntrainement:
        m_nbCamp--;
        break;
    case caserne:
        m_nbCaserne--;
        break;
    case portail:
        m_nbPortail--;
        break;
    case canon:
        m_nbCanon--;
        break;
    case tourelle:
        m_nbTourelle--;
        break;
    case mortier:
        m_nbMortier--;
        break;
    }

    //on isole la classe de batiment concerne sans le batiment detruit
    std::vector<Batiment*> listBatsCible;
    for(std::vector<Batiment*>::iterator it = m_listeBatiments.begin(); it != m_listeBatiments.end(); ++it)
    {
        if((*it)->isVisible())
        {
            if((*it)->getType() == typeBat && (*it)->getIdFichierVillage() != id)
            {
                listBatsCible.push_back((*it));
            }
        }
    }

    //on redefinit les id dans le fichier village
    int newId = 1;
    for(std::vector<Batiment*>::iterator itBatsCible = listBatsCible.begin(); itBatsCible != listBatsCible.end(); ++itBatsCible)
    {
        (*itBatsCible)->setIdFichierVillage(newId);
        newId++;
    }
}

void Village::genererTypeBatiment(typeBatiment typeBat, QString fichier)
{
    //on separe les types d infos
    QStringList listInfos = fichier.split(';');
    QStringList::iterator itInfos = listInfos.begin();

    //le nombre de batiment est la premiere info
    irr::s32 nbBats = 0;
    nbBats = (*itInfos).toInt();
    itInfos++;

    for(int i = 0; i < nbBats; ++i)
    {
        Travailleur* travailleur;
        switch(typeBat)
        {
        case hdv:
            m_batimentADeplacer = new HotelDeVille;
            break;

        case travailleurNourriture:
            m_batimentADeplacer = new Travailleur_Nourriture;
            travailleur = (Travailleur*)m_batimentADeplacer;
            connect(travailleur, SIGNAL(gagneDesRessources(int)), this, SLOT(gagneNourriture(int)));
            break;

        case travailleurOr:
            m_batimentADeplacer = new Travailleur_Or;
            travailleur = (Travailleur*)m_batimentADeplacer;
            connect(travailleur, SIGNAL(gagneDesRessources(int)), this, SLOT(gagneOr(int)));
            break;

        case conteneurNourriture:
            m_batimentADeplacer = new Conteneur_nourriture;
            break;

        case conteneurOr:
            m_batimentADeplacer = new Conteneur_Or;
            break;

        case campEntrainement:
            m_batimentADeplacer = new CampEntrainement;
            break;

        case caserne:
            m_batimentADeplacer = new Caserne;
            break;

        case portail:
            m_batimentADeplacer = new Portail;
            break;

        case canon:
            m_batimentADeplacer = new Canon;
            break;

        case tourelle:
            m_batimentADeplacer = new Tourelle;
            break;

        case mortier:
            m_batimentADeplacer = new Mortier;
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

        m_batimentADeplacer->setPosition(irr::core::vector3df(pos_x, 1, pos_z));

        //rotation
        itInfos++;
        rot = (*itInfos).toInt();
        m_batimentADeplacer->setRotation(irr::core::vector3df(0, rot, 0));

        m_batimentADeplacer->afficherBatimentConstruit();
        construireBatiment(true);

        //on passe au paquet de position suivant
        itInfos++;
    }
}

void Village::genererVillage()
{
    QString fichierVillage = Bdd::getBdd()->getFichierVillage(m_pseudo);

    //info de tout
    QStringList listInfos = fichierVillage.split('.');
    QStringList::iterator itInfos = listInfos.begin();

    //niveau
    QStringList listInfosNiveau = (*itInfos).split(';');
    itInfos++;

    QStringList::iterator itInfosNiveau = listInfosNiveau.begin();
    int niveau = (*itInfosNiveau).toInt();
    itInfosNiveau++;
    int xp = (*itInfosNiveau).toInt();
    setNiveau(niveau, xp);

    //nombre ressource (on traitera cette infos a la fin
    //car il faut attendre que le stockagge soit definit
    //en construisant les banques etc... avant de mettre
    //de l argent dedans
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

    //tout les conteneurs sont construits on peut mainteneant
    //mettre de l argent dedans
    QStringList::iterator itInfosNbResssource = listInfosNbRessource.begin();
    gagneOr((*itInfosNbResssource).toInt());

    itInfosNbResssource++;
    gagneNourriture((*itInfosNbResssource).toInt());
}
