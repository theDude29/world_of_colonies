#ifndef HOTELDEVILLE_H
#define HOTELDEVILLE_H

#include "jeu/batiments/ressource/conteneur.h"

#define MAX_PV_HDV 500
#define TAILLE_HDV_W 15
#define TAILLE_HDV_H 15
#define CONTENANCE_MAX_HDV 200

class HotelDeVille : public Conteneur
{
public:
    HotelDeVille(QObject* parent);
    virtual ~HotelDeVille();
    virtual QString getInfo();
};

#endif // HOTELDEVILLE_H
