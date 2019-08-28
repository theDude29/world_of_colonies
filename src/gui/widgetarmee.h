#ifndef WIDGETARMEE_H
#define WIDGETARMEE_H

#include <QFrame>
#include "../jeu/soldats/artilleur.h"
#include "../jeu/soldats/tank.h"
#include "../jeu/soldats/fantassin.h"
#include "../jeu/village.h"
#include "../jeu/armee.h"

namespace Ui {
class widgetArmee;
}

class widgetArmee : public QFrame
{
    Q_OBJECT

public:
    widgetArmee(QWidget *parent, Village* village, QString pseudo);
    ~widgetArmee();

    void majTexteStatsArmee();

    Armee* getArmee();

public slots:
    void afficherMenuArmee();
    void cacherMenuArmee();

    void bouttonArtilleurClique();
    void bouttonTankClique();
    void bouttonFantassinClique();

private:
    Ui::widgetArmee *ui;
    Village* m_village;
    QString m_pseudo;
    Armee* m_armee;

signals:
    void affichage();
    void cachage();
};

#endif // WIDGETARMEE_H
