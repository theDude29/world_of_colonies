#ifndef GESTIONATTAQUEVILLAGE_H
#define GESTIONATTAQUEVILLAGE_H

#include <QObject>
#include <irrlicht/irrlicht.h>
#include <vector>
#include "jeu/armee.h"

class GestionAttaqueVillage : public QObject
{
    Q_OBJECT
public:
    explicit GestionAttaqueVillage(QObject *parent = 0);
    void ajouterTroupe(int typeDuSoldat, irr::core::vector3df pos);

    void detruireTroupe();

protected:
    std::vector<Soldat*> m_listeSoldats;

signals:

public slots:
};

#endif // GESTIONATTAQUEVILLAGE_H
