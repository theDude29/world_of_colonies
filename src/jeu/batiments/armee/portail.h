#ifndef PORTAIL_H
#define PORTAIL_H

#include "../batiment.h"

#define MAX_PV_PORTAIL 200
#define TAILLE_PORTAIL_X 16
#define TAILLE_PORTAIL_Z 16
#define COUT_CONSTRUCTION_OR_PORTAIL 800
#define COUT_CONSTRUCTION_NOURRITURE_PORTAIL 200
#define XP_PORTAIL 500

class Portail : public Batiment
{
public:
    Portail(QObject* parent);
    virtual QString getInfo();
};

#endif // PORTAIL_H
