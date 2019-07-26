#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>
#include <QTimer>
#include <QIcon>
#include <QFontDatabase>
#include <QPicture>

#include "utilitaire/getcss.h"

MainWindow* MainWindow::m_this = NULL;

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMouseTracking(true);

    QFontDatabase fontdtb;
    fontdtb.addApplicationFont(QCoreApplication::applicationDirPath() + "/gui/css/font/galaxieLointaine.ttf");

    m_this = this;

    //FINITION DE LA FENETRE
    setMinimumSize(900,700);
    ui->bouton_assault->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/gui/image/icon/sword.png"));
    ui->bouton_menuArmee->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/gui/image/icon/helmet.png"));
    ui->bouton_menuConstruire->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/gui/image/icon/marteau.png"));

    setStyleSheet(getCSS("gui/css/style_mainwindow.css"));

    cacherWidgetsEnfants();

    //widget connection
    m_widgetConnexion = new WidgetConnexion(this);
    ui->gridLayout->addWidget(m_widgetConnexion);

    connect(m_widgetConnexion, SIGNAL(connecte()), this, SLOT(initVillage()));

    m_village = NULL;
}

MainWindow *MainWindow::getMainWindow()
{
    return m_this;
}

Village* MainWindow::getVillage()
{
    return m_village;
}

void MainWindow::initVillage()
{
    m_widgetConnexion->setVisible(false);
    QPalette p;
    this->setPalette(p);
    afficherWidgetsEnfants();
    cacherBoutonsAssault();

    //irrlicht
    m_irrlichtWidget = new IrrlichtWidget(this);
    this->installEventFilter(m_irrlichtWidget);
    //timer pour maj irrlicht
    QTimer* timer = new QTimer(this);
    timer->setInterval(1);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(drawIrrlichtScene()));//ici la merde
    //ce qui a un rapport avec irrlicht (comme le gestionnair de village
    //doit etre initilaliser apres le irrlicht widget  IMPORTANT

    //gestionnaire village
    m_village = new Village(this, m_widgetConnexion->getPseudo(), ui->progressBar_niveau, ui->label_niveau, ui->progressBar_ressource1, ui->progressBar_ressource2);
    this->installEventFilter(m_village);

    //menu construire
    m_menuConstruire = new MenuConstruire(this, m_village);
    ui->gridLayout->addWidget(m_menuConstruire, 1, 0);
    m_menuConstruire->cacherMenuConstuire();

    //menu armee
    m_menuArmee = new widgetArmee(this, m_village, m_widgetConnexion->getPseudo());
    ui->gridLayout->addWidget(m_menuArmee, 1, 0);
    m_menuArmee->cacherMenuArmee();

    //village ennemie
    m_villageEnnemie = new VillageEnnemi(this, m_widgetConnexion->getPseudo(), m_menuArmee->getArmee(), ui->label_pseudo_ennemi, ui->pushButton_choixArtilleur, ui->pushButton_choixFantassin, ui->pushButton_choixTank);

    //CONNECTIONS
    connect(ui->bouton_menuConstruire, SIGNAL(clicked(bool)), m_menuConstruire, SLOT(afficherMenuConstruire()));
    connect(ui->bouton_menuArmee, SIGNAL(clicked(bool)), m_menuArmee, SLOT(afficherMenuArmee()));
    connect(ui->bouton_assault, SIGNAL(clicked(bool)), m_villageEnnemie, SLOT(genererVillageAuPif()));
    connect(ui->bouton_assault, SIGNAL(clicked(bool)), this, SLOT(passerEnGuiAssault()));

    connect(m_menuConstruire, SIGNAL(affichage()), this, SLOT(cacherBoutons()));
    connect(m_menuConstruire, SIGNAL(cachage()), this, SLOT(afficherBoutons()));

    connect(m_menuArmee, SIGNAL(affichage()), this, SLOT(cacherBoutons()));
    connect(m_menuArmee, SIGNAL(cachage()), this, SLOT(afficherBoutons()));

    //
    connect(m_village, SIGNAL(onPlaceBatiment()), this, SLOT(cacherBoutons()));
    connect(m_village, SIGNAL(onArretePlacerBatiment()), this, SLOT(afficherBoutons()));
}

void MainWindow::passerEnGuiAssault()
{
    m_village->cacherBatiments();
    afficherBoutonAssault();

    disconnect(ui->bouton_menuConstruire, SIGNAL(clicked(bool)), m_menuConstruire, SLOT(afficherMenuConstruire()));
    disconnect(ui->bouton_menuArmee, SIGNAL(clicked(bool)), m_menuArmee, SLOT(afficherMenuArmee()));
    disconnect(ui->bouton_assault, SIGNAL(clicked(bool)), this, SLOT(passerEnGuiAssault()));

    connect(ui->bouton_menuConstruire, SIGNAL(clicked(bool)), this, SLOT(passerEnGuiMonVillage()));

    ui->bouton_menuConstruire->setText(QString(" Revenir au village"));
    ui->bouton_menuConstruire->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/gui/image/icon/back-arrow.png"));
    //
    ui->bouton_menuArmee->setText(QString(" Attaquer"));
    ui->bouton_menuArmee->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/gui/image/icon/sword.png"));
    //
    ui->bouton_assault->setText(QString("Village suivant (200 or)"));
    ui->bouton_assault->setIcon(QIcon("pas d'iconne ( j'ai pas trouvé moyen de faire ca proprement !! )"));
}

void MainWindow::passerEnGuiMonVillage()
{
    m_villageEnnemie->detruireVillage();
    cacherBoutonsAssault();

    m_village->afficherBatiments();

    //disconnect(ui->bouton_menuConstruire, SIGNAL(clicked(bool)), m_menuConstruire, SLOT(afficherMenuConstruire()));
    //disconnect(ui->bouton_menuArmee, SIGNAL(clicked(bool)), m_menuArmee, SLOT(afficherMenuArmee()));
    disconnect(ui->bouton_menuConstruire, SIGNAL(clicked(bool)), this, SLOT(passerEnGuiMonVillage()));

    connect(ui->bouton_menuConstruire, SIGNAL(clicked(bool)), m_menuConstruire, SLOT(afficherMenuConstruire()));
    connect(ui->bouton_menuArmee, SIGNAL(clicked(bool)), m_menuArmee, SLOT(afficherMenuArmee()));
    connect(ui->bouton_assault, SIGNAL(clicked(bool)), this, SLOT(passerEnGuiAssault()));

    ui->bouton_menuConstruire->setText(QString(" Construire"));
    ui->bouton_menuArmee->setText(QString(" Armee"));
    ui->bouton_assault->setText(QString(" Assault"));

    ui->bouton_assault->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/gui/image/icon/sword.png"));
    ui->bouton_menuArmee->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/gui/image/icon/helmet.png"));
    ui->bouton_menuConstruire->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/gui/image/icon/marteau.png"));
}

void MainWindow::drawIrrlichtScene()
{
    m_irrlichtWidget->drawScene();
}

void MainWindow::cacherBoutons()
{
    ui->bouton_assault->setVisible(false);
    ui->bouton_menuArmee->setVisible(false);
    ui->bouton_menuConstruire->setVisible(false);
}

void MainWindow::afficherBoutons()
{
    ui->bouton_assault->setVisible(true);
    ui->bouton_menuArmee->setVisible(true);
    ui->bouton_menuConstruire->setVisible(true);
}

void MainWindow::cacherWidgetsEnfants()
{
    cacherBoutonsAssault();
    cacherBoutons();
    ui->progressBar_niveau->setVisible(false);
    ui->progressBar_ressource1->setVisible(false);
    ui->progressBar_ressource2->setVisible(false);
    ui->label_niveau->setVisible(false);
    ui->label_pseudo->setVisible(false);
    ui->label_ressource1->setVisible(false);
    ui->label_ressource2->setVisible(false);
}

void MainWindow::afficherWidgetsEnfants()
{
    afficherBoutonAssault();
    afficherBoutons();
    ui->progressBar_niveau->setVisible(true);
    ui->progressBar_ressource1->setVisible(true);
    ui->progressBar_ressource2->setVisible(true);
    ui->label_niveau->setVisible(true);
    ui->label_pseudo->setText(m_widgetConnexion->getPseudo());
    ui->label_pseudo->setVisible(true);
    ui->label_ressource1->setVisible(true);
    ui->label_ressource2->setVisible(true);
}

void MainWindow::afficherBoutonAssault()
{
    ui->frame_boutonAssault->setVisible(true);

    ui->label_pseudo_ennemi->setVisible(true);
}

void MainWindow::cacherBoutonsAssault()
{
    ui->frame_boutonAssault->setVisible(false);

    ui->label_pseudo_ennemi->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete m_irrlichtWidget;
    delete m_village;
    delete ui;
}
