#ifndef ARMEE_H
#define ARMEE_H

#include <QObject>
#include "jeu/soldats/artilleur.h"
#include "jeu/soldats/tank.h"
#include "jeu/soldats/fantassin.h"

class Armee : public QObject
{
    Q_OBJECT

public:
    Armee();

    int getNbArtilleur();
    int getNbTank();
    int getNbFantassin();

    void majPlaceMax(int nbCaserne);
    int getNbPlaceMax();
    int getNbPlaceOccupe();

private:
    int m_nbPlaceMax, m_nbPlaceOccupee;
    int m_nbArtilleur, m_nbTank, m_nbFantassin;

public slots:
    void ajouterArtilleur();
    void ajouterTank();
    void ajouterFantassin();

};

#endif // ARMEE_H
