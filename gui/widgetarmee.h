#ifndef WIDGETARMEE_H
#define WIDGETARMEE_H

#include <QFrame>
#include "jeu/soldats/artilleur.h"
#include "jeu/soldats/tank.h"
#include "jeu/soldats/fantassin.h"
#include "jeu/village.h"
#include "jeu/armee.h"

namespace Ui {
class widgetArmee;
}

class widgetArmee : public QFrame
{
    Q_OBJECT

public:
    widgetArmee(QWidget *parent, Village* village);
    ~widgetArmee();

    void majTexteStatsArmee();

public slots:
    void afficherMenuArmee();
    void cacherMenuArmee();

    void bouttonArtilleurClique();

private:
    Ui::widgetArmee *ui;
    Village* m_village;
    Armee* m_armee;
    Artilleur m_artilleur;
    Tank m_tank;
    Fantassin m_fantassin;


signals:
    void affichage();
    void cachage();
};

#endif // WIDGETARMEE_H
