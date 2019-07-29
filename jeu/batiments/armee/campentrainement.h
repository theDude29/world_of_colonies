#ifndef CAMP
#define CAMP

#include "jeu/batiments/batiment.h"

#define MAX_PV_CAMP_ENTRAINEMENT 100
#define TAILLE_CAMP_ENTRAINEMENT_X 10
#define TAILLE_CAMP_ENTRAINEMENT_Z 10
#define COUT_CONSTRUCTION_OR_CAMP_ENTRAINEMENT 300
#define COUT_CONSTRUCTION_NOURRITURE_CAMP_ENTRAINEMENT 150
#define XP_CAMP_ENTRAINEMENT 300

class CampEntrainement : public Batiment
{
public:
    CampEntrainement(QObject* parent);
    virtual QString getInfo();

private:

};

#endif
