#ifndef ARMEE_H
#define ARMEE_H

#include <QObject>
#include "soldats/artilleur.h"
#include "soldats/tank.h"
#include "soldats/fantassin.h"

class Armee : public QObject
{
    Q_OBJECT

public:
    Armee(QString pseudo);

    int getNbArtilleur();
    int getNbTank();
    int getNbFantassin();

    int getNbPlaceMax();
    int getNbPlaceOccupe();

private:
    QString m_pseudo;
    int m_nbPlaceMax, m_nbPlaceOccupee;
    int m_nbArtilleur, m_nbTank, m_nbFantassin;

public slots:
    void majPlaceMax(int nbCaserne);

    void ajouterArtilleur();
    void ajouterTank();
    void ajouterFantassin();

};

#endif // ARMEE_H
