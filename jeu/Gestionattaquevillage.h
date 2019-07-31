#ifndef GESTIONATTAQUEVILLAGE_H
#define GESTIONATTAQUEVILLAGE_H

#include <QObject>
#include <vector>
#include "jeu/armee.h"
#include "jeu/batiments/batiment.h"
#include "jeu/batiments/defense/defense.h"
#include <QLabel>

enum typeItem
{
    batiment,
    soldat
};

class GestionAttaqueVillage : public QObject
{
    Q_OBJECT
public:
    explicit GestionAttaqueVillage(QObject *parent, QLabel* textVictoire);

    void majSoldat();
    void majDefense();

    void ajouterTroupe(int typeDuSoldat, irr::core::vector3df pos);
    void setListeBatiment(std::vector<Batiment*> listeBats);

    std::vector<Item*> convertBatimentToItem();
    std::vector<Item*> convertSoldatToItem();
    irr::core::vector3df getItemLePlusPres(irr::core::vector3df pos, int typeItem);

    void detruireTroupe();

protected:
    QLabel* m_textVictoire;
    std::vector<Soldat*> m_listeSoldats;
    std::vector<Batiment*> m_listeBatiments;
    std::vector<Defense*> m_listeDefense;

signals:

public slots:
        void maj();
};

#endif // GESTIONATTAQUEVILLAGE_H
