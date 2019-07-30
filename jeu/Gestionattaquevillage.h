#ifndef GESTIONATTAQUEVILLAGE_H
#define GESTIONATTAQUEVILLAGE_H

#include <QObject>
#include <vector>
#include "jeu/armee.h"
#include "jeu/batiments/batiment.h"
#include <QLabel>

class GestionAttaqueVillage : public QObject
{
    Q_OBJECT
public:
    explicit GestionAttaqueVillage(QObject *parent, QLabel* textVictoire);

    void ajouterTroupe(int typeDuSoldat, irr::core::vector3df pos);
    void setListeBatiment(std::vector<Batiment*> listeBats);

    irr::core::vector3df getBatLePlusPres(irr::core::vector3df posSoldat);

    void detruireTroupe();

protected:
    QLabel* m_textVictoire;
    std::vector<Soldat*> m_listeSoldats;
    std::vector<Batiment*> m_listeBatiments;

signals:

public slots:
        void maj();
};

#endif // GESTIONATTAQUEVILLAGE_H
