#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "bdd/widgetconnexion.h"
#include "jeu/irrlichtwidget.h"
#include "jeu/village.h"
#include "gui/menuconstruire.h"
#include "gui/widgetarmee.h"
#include "jeu/villageennemi.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static MainWindow* getMainWindow();
    Village* getVillage();

private:
    Ui::MainWindow *ui;

    static MainWindow* m_this;

    //widget connection
    WidgetConnexion* m_widgetConnexion;

    //irrlicht
    IrrlichtWidget* m_irrlichtWidget;

    //menu construction de batiment
    MenuConstruire* m_menuConstruire;

    //menu armee
    widgetArmee* m_menuArmee;

    //village
    Village* m_village;

    //village ennemi
    VillageEnnemi* m_villageEnnemie;

public slots:
    void initVillage();

    void drawIrrlichtScene();

    void passerEnGuiAssault();
    void passerEnGuiMonVillage();

    void cacherBoutons();
    void afficherBoutons();
    void cacherWidgetsEnfants();
    void afficherWidgetsEnfants();
};

#endif // MAINWINDOW_H
