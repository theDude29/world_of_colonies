#include <QString>
#include <QStringList>
#include "bdd.h"
#include <QDateTime>

Bdd* Bdd::m_instance = NULL;

Bdd::Bdd()
{
    m_instance = this;
}

Bdd* Bdd::getBdd()
{
    if(m_instance == NULL)
    {
        Bdd();
    }

    return m_instance;
}

sql::Connection* Bdd::getBddConnection()
{
    sql::Driver *driver = get_driver_instance();
    sql::Connection* connection = driver->connect("localhost", "root", "");
    connection->setSchema("info_site_world_of_colonies");

    return connection;
}

QStringList Bdd::recupererListJoueurs()
{
    sql::Connection* connection = getBddConnection();
    sql::Statement* requete = connection->createStatement();
    sql::SQLString sqlReq = "SELECT pseudo FROM Membres";
    sql::ResultSet* reponse = requete->executeQuery(sqlReq);

    QStringList listJoueurs;

    while(reponse->next())
    {
        listJoueurs.append(QString(reponse->getString("pseudo").c_str()));
    }

    m_nbJoueurs = listJoueurs.size();

    delete requete;
    delete reponse;
    delete connection;

    return listJoueurs;
}

QString Bdd::getFichierVillageEnnemieAuPif(QString pseudo)
{
    QString pseudoEnnemie = getPseudoAuPif();
    while(pseudoEnnemie == pseudo)
    {
        pseudoEnnemie = getPseudoAuPif();
    }

    QString fichierVillageEnnemie = getFichierVillage(pseudoEnnemie);

    std::cout<<fichierVillageEnnemie.toStdString()<<"\n";

    return fichierVillageEnnemie;
}

QString Bdd::getPseudoAuPif()
{
    QString pseudoEnnemie = "";

    QStringList listJoueurs = recupererListJoueurs();
    QStringList::iterator it = listJoueurs.begin();
    int nbMystere = (rand() % (m_nbJoueurs - 0 + 1)) + 0;
    for(int i = 0; i < nbMystere; ++i)
    {
        it++;
    }

    pseudoEnnemie = *(it);

    std::cout<<pseudoEnnemie.toStdString()<<"\n";

    return pseudoEnnemie;
}

int Bdd::getNbArtilleur(QString pseudo)
{
    sql::Connection* connection = getBddConnection();
    sql::Statement* requete = connection->createStatement();
    sql::SQLString sqlReq = "SELECT nb_artilleur_dans_armee FROM Membres WHERE pseudo=\'" + pseudo.toStdString() +"\'";
    sql::ResultSet* reponse = requete->executeQuery(sqlReq);

    int nbArtilleur = 0;

    reponse->next();
    nbArtilleur = reponse->getInt("nb_artilleur_dans_armee");

    delete requete;
    delete reponse;
    delete connection;

    return nbArtilleur;
}

int Bdd::getNbTank(QString pseudo)
{
    sql::Connection* connection = getBddConnection();
    sql::Statement* requete = connection->createStatement();
    sql::SQLString sqlReq = "SELECT nb_tank_dans_armee FROM Membres WHERE pseudo=\'" + pseudo.toStdString() +"\'";
    sql::ResultSet* reponse = requete->executeQuery(sqlReq);

    int nbTank = 0;

    reponse->next();
    nbTank = reponse->getInt("nb_tank_dans_armee");

    delete requete;
    delete reponse;
    delete connection;

    return nbTank;
}

void Bdd::setNbArtilleur(QString pseudo, int nb)
{
    sql::SQLString nb_str = QString::number(nb).toStdString();

    sql::Connection* connection = getBddConnection();
    sql::Statement* requete = connection->createStatement();
    sql::SQLString sqlReq = "UPDATE Membres SET nb_artilleur_dans_armee = \'" + nb_str + "\' WHERE pseudo = \'" + pseudo.toStdString() + "\'";

    requete->executeUpdate(sqlReq);

    delete requete;
    delete connection;
}

void Bdd::setNbTank(QString pseudo, int nb)
{
    sql::SQLString nb_str = QString::number(nb).toStdString();

    sql::Connection* connection = getBddConnection();
    sql::Statement* requete = connection->createStatement();
    sql::SQLString sqlReq = "UPDATE Membres SET nb_tank_dans_armee = \'" + nb_str + "\' WHERE pseudo = \'" + pseudo.toStdString() + "\'";

    requete->executeUpdate(sqlReq);

    delete requete;
    delete connection;
}

void Bdd::setNbFantassin(QString pseudo, int nb)
{
    sql::SQLString nb_str = QString::number(nb).toStdString();

    sql::Connection* connection = getBddConnection();
    sql::Statement* requete = connection->createStatement();
    sql::SQLString sqlReq = "UPDATE Membres SET nb_fantassin_dans_armee = \'" + nb_str + "\' WHERE pseudo = \'" + pseudo.toStdString() + "\'";

    requete->executeUpdate(sqlReq);

    delete requete;
    delete connection;
}

int Bdd::getNbFantassin(QString pseudo)
{
    sql::Connection* connection = getBddConnection();
    sql::Statement* requete = connection->createStatement();
    sql::SQLString sqlReq = "SELECT nb_fantassin_dans_armee FROM Membres WHERE pseudo=\'" + pseudo.toStdString() +"\'";
    sql::ResultSet* reponse = requete->executeQuery(sqlReq);

    int nbFantassin = 0;

    reponse->next();
    nbFantassin = reponse->getInt("nb_fantassin_dans_armee");

    delete requete;
    delete reponse;
    delete connection;

    return nbFantassin;
}

void Bdd::majTimingBatiment(QString pseudo, int typeBat, int id)
{
    QString fichierTiming = getFichierTiming(pseudo);
    QStringList listInfos = fichierTiming.split('.');
    QStringList::iterator itInfos = listInfos.begin();

    for(int i = 1; i != typeBat; ++i)
    {
        itInfos++; //on arrive aux infos concernant le batiment cible
    }

    QString infosBatimentCible = (*itInfos);
    QStringList listInfosBatCible = infosBatimentCible.split(QString(";"));
    listInfosBatCible.pop_back();
    QStringList::iterator itInfosBatCible = listInfosBatCible.begin();

    for(int i = 1; i < id; i++) //on arrive a la positon du bat correspondant
    {
        itInfosBatCible++;
    }

    QString timeActu = QDateTime::currentDateTime().toString("yyyy:MM:dd:hh:mm:ss");

    (*itInfosBatCible) = timeActu;

    QString newInfosBatCible = listInfosBatCible.join(QString(";"));
    newInfosBatCible += ";";

    (*itInfos) = newInfosBatCible;

    QString fichierAJour = listInfos.join(QString("."));
    majFichierTiming(pseudo, fichierAJour);
}

void Bdd::supprimerTimingBatiment(QString pseudo, int typeBat, int id)
{
    QString fichierTiming = getFichierTiming(pseudo);
    QStringList listInfos = fichierTiming.split('.');
    QStringList::iterator itInfos = listInfos.begin();

    for(int i = 1; i != typeBat; ++i)
    {
        itInfos++; //on arrive aux infos concernant le batiment cible
    }

    QString infosBatimentCible = (*itInfos);
    QStringList listInfosBatCible = infosBatimentCible.split(QString(";"));
    listInfosBatCible.pop_back();
    QStringList::iterator itInfosBatCible = listInfosBatCible.begin();

    for(int i = 1; i < id; i++) //on arrive a la positon du bat correspondant
    {
        itInfosBatCible++;
    }

    listInfosBatCible.erase(itInfosBatCible);

    QString newInfosBatCible = listInfosBatCible.join(QString(";"));
    if(newInfosBatCible != "") newInfosBatCible += ";";

    (*itInfos) = newInfosBatCible;

    QString fichierAJour = listInfos.join(QString("."));
    majFichierTiming(pseudo, fichierAJour);
}

QString Bdd::getTimingBatiment(QString pseudo, int typeBatiment, int id)
{
    QString fichier = getFichierTiming(pseudo);
    QStringList listInfos = fichier.split('.');
    QStringList::iterator itInfos = listInfos.begin();

    for(int i = 1; i != typeBatiment; ++i)
    {
        itInfos++;
    }

    QStringList listInfosBatsCibles = (*itInfos).split(';');
    QStringList::iterator itInfosBatsCibles = listInfosBatsCibles.begin();

    for(int i = 1; i != id; ++i)
    {
        itInfosBatsCibles++;
    }

    QString timing = (*itInfosBatsCibles);

    return timing;
}

QString Bdd::getFichierTiming(QString pseudo)
{
    sql::Connection* connection = getBddConnection();
    sql::Statement* requete = connection->createStatement();
    sql::SQLString sqlReq = "SELECT fichier_village_timing FROM Membres WHERE pseudo=\'" + pseudo.toStdString() +"\'";
    sql::ResultSet* reponse = requete->executeQuery(sqlReq);

    sql::SQLString fichierTiming = "";

    reponse->next();
    fichierTiming = reponse->getString("fichier_village_timing");

    QString fichierTiming_Qt = QString(fichierTiming.c_str());

    delete requete;
    delete reponse;
    delete connection;

    return fichierTiming_Qt;
}

void Bdd::ajouterTimingBatiment(QString pseudo, int typeBatiment)
{
    //info de tout
    QString fichierTiming = getFichierTiming(pseudo);
    QStringList listInfos = fichierTiming.split('.');
    QStringList::iterator itInfos = listInfos.begin();

    for(int i = 1; i != typeBatiment; ++i)
    {
        itInfos++;
    }

    QString infosBatimentsCibles = (*itInfos);

    QDateTime dateTime = QDateTime::currentDateTime();

    QDate date = dateTime.date();
    QTime time = dateTime.time();

    QString date_str = date.toString("yyyy:MM:dd");
    date_str += ':';
    date_str += time.toString("hh:mm:ss");
    date_str += ';';

    infosBatimentsCibles += date_str;

    (*itInfos) = infosBatimentsCibles;

    QString newFichier = listInfos.join(QString('.'));

    majFichierTiming(pseudo, newFichier);
}

void Bdd::majFichierTiming(QString pseudo, QString fichier)
{
    sql::Connection* connection = getBddConnection();
    sql::Statement* requete = connection->createStatement();
    sql::SQLString sqlReq = "UPDATE Membres SET fichier_village_timing = \'" + fichier.toStdString() + "\' WHERE pseudo = \'" + pseudo.toStdString() + "\'";

    requete->executeUpdate(sqlReq);

    delete requete;
    delete connection;
}

QString Bdd::getFichierVillage(QString pseudo)
{
    sql::Connection* connection = getBddConnection();
    sql::Statement* requete = connection->createStatement();
    sql::SQLString sqlReq = "SELECT fichier_village_batiment FROM Membres WHERE pseudo=\'" + pseudo.toStdString() + "\'";
    sql::ResultSet* reponse = requete->executeQuery(sqlReq);

    sql::SQLString fichierVillage = "";

    reponse->next();
    fichierVillage = reponse->getString("fichier_village_batiment");

    QString fichierVillage_Qt = QString(fichierVillage.c_str());

    delete requete;
    delete reponse;
    delete connection;

    return fichierVillage_Qt;
}

void Bdd::majNiveau(QString pseudo, int niveau, int xp)
{
    //info de tout
    QString fichierVillage = getFichierVillage(pseudo);
    QStringList listInfos = fichierVillage.split('.');
    QStringList::iterator itInfos = listInfos.begin();

    //niveau
    QStringList listInfosNiveau = (*itInfos).split(';');
    QStringList::iterator itInfosNiveau = listInfosNiveau.begin();

    QString niveauStr = QString::number(niveau), xpStr = QString::number(xp);

    (*itInfosNiveau) = niveauStr;
    itInfosNiveau++;
    (*itInfosNiveau) = xpStr;

    QString newStat = listInfosNiveau.join(QString(";"));
    (*itInfos) = newStat;

    QString fichierAJour = listInfos.join(QString("."));

    majFichierVillage(pseudo, fichierAJour);
}

void Bdd::majRotationBatiment(QString pseudo, int typeBat, int rot, int id)
{
    QString fichierVillage = getFichierVillage(pseudo);
    QStringList listInfos = fichierVillage.split('.');
    QStringList::iterator itInfos = listInfos.begin();
    itInfos++; //on passe les infos sur concernant le niveau
    itInfos++; //on passe les infos sur le nombre de ressource

    for(int i = 0; i != typeBat; ++i)
    {
        itInfos++; //on arrive aux infos concernant le batiment cible
    }

    QString infosBatimentCible = (*itInfos);
    QStringList listInfosBatCible = infosBatimentCible.split(QString(";"));
    listInfosBatCible.pop_back();
    QStringList::iterator itInfosBatCible = listInfosBatCible.begin();

    itInfosBatCible++; //on passe le nombre de bats
    itInfosBatCible++; //on passe la premiere position

    for(int i = 1; i < id; i++) //on arrive a la rotation du bat correspondant
    {
        itInfosBatCible++;//position
        itInfosBatCible++;//rotation
    }

    QString newRot = QString::number(rot);

    (*itInfosBatCible) = newRot; //on remplace les donne

    QString newInfosBatCible = listInfosBatCible.join(QString(";"));
    newInfosBatCible += ';'; //attention

    (*itInfos) = newInfosBatCible;

    QString fichierAJour = listInfos.join(QString("."));
    majFichierVillage(pseudo, fichierAJour);
}

void Bdd::majBatiment(QString pseudo, int typeBat, irr::core::vector2di posBat, int id)
{
    QString fichierVillage = getFichierVillage(pseudo);
    QStringList listInfos = fichierVillage.split('.');
    QStringList::iterator itInfos = listInfos.begin();
    itInfos++; //on passe les infos sur concernant le niveau
    itInfos++; //on passe les infos sur le nombre de ressource

    for(int i = 0; i != typeBat; ++i)
    {
        itInfos++; //on arrive aux infos concernant le batiment cible
    }

    QString infosBatimentCible = (*itInfos);
    QStringList listInfosBatCible = infosBatimentCible.split(QString(";"));
    listInfosBatCible.pop_back();
    QStringList::iterator itInfosBatCible = listInfosBatCible.begin();

    //pas d id specifier cela veut dire que le batiment doit se rajouter
    //a la fin du fichier ( c est un nouveau batiment)
    if(id == -1)
    {
        int nbBatCible = (*itInfosBatCible).toInt();
        nbBatCible++;
        (*itInfosBatCible) = QString::number(nbBatCible);

        QString newPos = QString::number(posBat.X) + ',' +
                QString::number(posBat.Y);

        listInfosBatCible.append(newPos); //on ajoute les donne de position
        listInfosBatCible.append(QString("0")); //rotation
    }

    //un id est specifier cela veut dire que les infos sont a remplacer
    //(le batiment a bouger)
    else
    {
        itInfosBatCible++; //on passe le nombre de bats

        for(int i = 1; i < id; i++) //on arrive a la positon du bat correspondant
        {
            itInfosBatCible++;//rotation
            itInfosBatCible++;//position
        }

        QString newPos = QString::number(posBat.X) + ',' +
                QString::number(posBat.Y);

        (*itInfosBatCible) = newPos; //on remplace les donne
    }

    QString newInfosBatCible = listInfosBatCible.join(QString(";"));
    newInfosBatCible += ';'; //attention

    (*itInfos) = newInfosBatCible;

    QString fichierAJour = listInfos.join(QString("."));
    majFichierVillage(pseudo, fichierAJour);
}

void Bdd::supprimerBatiment(QString pseudo, int typeBat, int id)
{
    QString fichierVillage = getFichierVillage(pseudo);
    QStringList listInfos = fichierVillage.split('.');
    QStringList::iterator itInfos = listInfos.begin();
    itInfos++; //on passe les infos sur concernant le niveau
    itInfos++; //on passe les infos sur le nombre de ressource

    for(int i = 0; i != typeBat; ++i)
    {
        itInfos++; //on arrive aux infos concernant le batiment cible
    }

    QString infosBatimentCible = (*itInfos);
    QStringList listInfosBatCible = infosBatimentCible.split(QString(";"));
    listInfosBatCible.pop_back();
    QStringList::iterator itInfosBatCible = listInfosBatCible.begin();

    int nbBat = (*itInfosBatCible).toInt();
    nbBat--;
    (*itInfosBatCible) = QString::number(nbBat);
    itInfosBatCible++;

    for(int i = 1; i < id; i++) //on arrive a la positon du bat correspondant
    {
        itInfosBatCible++;
    }

    itInfosBatCible = listInfosBatCible.erase(itInfosBatCible);

    //itInfosBatCible++; //on arive a la rotation du bat
    listInfosBatCible.erase(itInfosBatCible);

    QString newInfosBatCible = listInfosBatCible.join(QString(";"));
    newInfosBatCible += ';'; //attention

    (*itInfos) = newInfosBatCible;

    QString fichierAJour = listInfos.join(QString("."));
    majFichierVillage(pseudo, fichierAJour);
}

void Bdd::majNbRessource(QString pseudo, int nbOr, int nbNourriture)
{
    QString fichierVillage = getFichierVillage(pseudo);
    QStringList listInfos = fichierVillage.split('.');
    QStringList::iterator itInfos = listInfos.begin();
    itInfos++; //on passe les infos sur concernant le niveau

    QString newInfos = "";
    newInfos += QString::number(nbOr) += QString(",") += QString::number(nbNourriture);
    (*itInfos) = newInfos;

    QString newFichier = listInfos.join(QString("."));
    majFichierVillage(pseudo, newFichier);

}

void Bdd::majFichierVillage(QString pseudo, QString fichier)
{
    sql::Connection* connection = getBddConnection();
    sql::Statement* requete = connection->createStatement();
    sql::SQLString sqlReq = "UPDATE Membres SET fichier_village_batiment = \'" + fichier.toStdString() + "\' WHERE pseudo = \'" + pseudo.toStdString() + "\'";

    requete->executeUpdate(sqlReq);

    delete requete;
    delete connection;
}


