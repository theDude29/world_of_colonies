#ifndef BDDCONNECTION_H
#define BDDCONNECTION_H

#include <irrlicht/irrlicht.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <QString>
#include "jeu/batiments/batiment.h"

class Bdd
{
public:
    static Bdd* getBdd();
    sql::Connection* getBddConnection();
    void extraireInfoFichierParam();

    QStringList recupererListJoueurs();
    QString getFichierVillageEnnemieAuPif(QString pseudo);
    QString getPseudoAuPif();

    int getNbArtilleur(QString pseudo);
    int getNbTank(QString pseudo);
    int getNbFantassin(QString pseudo);
    void setNbArtilleur(QString pseudo, int nb);
    void setNbTank(QString pseudo, int nb);
    void setNbFantassin(QString pseudo, int nb);

    QString getFichierVillage(QString pseudo);
    void majNiveau(QString pseudo, int niveau, int xp);
    void majBatiment(QString pseudo, int typeBat, irr::core::vector2di posBat, int id);
    void majRotationBatiment(QString pseudo, int typeBat, int rot, int id);
    void supprimerBatiment(QString pseudo, int typeBat, int id);
    void majFichierVillage(QString fichier, QString pseudo);
    void majNbRessource(QString pseudo, int nbOr, int nbNourriture);

    QString getFichierTiming(QString pseudo);
    void majFichierTiming(QString pseudo, QString fichier);
    void ajouterTimingBatiment(QString pseudo, int typeBatiment);
    void supprimerTimingBatiment(QString pseudo, int typeBat, int id);
    QString getTimingBatiment(QString pseudo, int typeBatiment, int id);
    void majTimingBatiment(QString pseudo, int typeBat, int id);

private:
    Bdd();
    static Bdd* m_instance;

    sql::Connection* m_connection;

    int m_nbJoueurs;

    static QString m_adresseBDD, m_droitBDD, m_pwdBDD, m_nomBDD;
};

#endif // BDDCONNECTION_H
