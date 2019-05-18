#ifndef MENUCONSTRUIRE_H
#define MENUCONSTRUIRE_H

#include <QFrame>
#include "jeu/village.h"
#include "jeu/batiments/ressource/conteneur_or.h"
#include "jeu/batiments/ressource/conteneur_nourriture.h"
#include "jeu/batiments/ressource/travailleur_or.h"
#include "jeu/batiments/ressource/travailleur_nourriture.h"
#include "jeu/batiments/armee/campentrainement.h"
#include "jeu/batiments/armee/caserne.h"
#include "jeu/batiments/armee/portail.h"
#include "jeu/batiments/defense/canon.h"
#include "jeu/batiments/defense/tourelle.h"
#include "jeu/batiments/defense/mortier.h"

namespace Ui {
class MenuConstruire;
}

class MenuConstruire : public QFrame
{
    Q_OBJECT

public:
    MenuConstruire(QWidget *parent = 0, Village* village = 0);
    ~MenuConstruire();

private:
    Ui::MenuConstruire *ui;

    Village* m_village;

public slots:
    void cacherMenuConstuire();
    void afficherMenuConstruire();

    void bouttonRc1Clique();
    void bouttonRc2Clique();
    void bouttonRc3Clique();
    void bouttonRc4Clique();
    void bouttonArmee1Clique();
    void bouttonArmee2Clique();
    void bouttonArmee3Clique();
    void bouttonDefense1Clique();
    void bouttonDefense2Clique();
    void bouttonDefense3Clique();

signals:
    void affichage();
    void cachage();
};

#endif // MENUCONSTRUIRE_H
