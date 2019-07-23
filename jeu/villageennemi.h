#ifndef VILLAGEENNEMI_H
#define VILLAGEENNEMI_H

#include <vector>
#include "jeu/batiments/batiment.h"
#include "jeu/batiments/hoteldeville.h"
#include "jeu/batiments/ressource/travailleur_or.h"
#include "jeu/batiments/ressource/travailleur_nourriture.h"
#include "jeu/batiments/ressource/conteneur_nourriture.h"
#include "jeu/batiments/ressource/conteneur_or.h"
#include "jeu/batiments/armee/campentrainement.h"
#include "jeu/batiments/armee/caserne.h"
#include "jeu/batiments/armee/portail.h"
#include "jeu/batiments/defense/canon.h"
#include "jeu/batiments/defense/tourelle.h"
#include "jeu/batiments/defense/mortier.h"

class VillageEnnemi : public QObject
{
    Q_OBJECT

public:
    VillageEnnemi(QObject* parent, QString pseudo);
    ~VillageEnnemi();
    void genererVillage(QString fichier);
    void genererTypeBatiment(typeBatiment typeBat, QString fichier);
    void detruireVillage();

private:
    QString m_pseudo;
    std::vector<Batiment*> m_listeBatiments;

public slots:
    void genererVillageAuPif();
};

#endif // VILLAGEENNEMI_H
