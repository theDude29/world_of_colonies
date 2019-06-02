#include "widgetarmee.h"
#include "ui_widgetarmee.h"
#include "utilitaire/getcss.h"
#include "jeu/soldats/artilleur/artilleur.h"

widgetArmee::widgetArmee(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::widgetArmee)
{
    ui->setupUi(this);

    //FINITONS
    setStyleSheet(getCSS("gui/css/style_menuConstruire.css"));
    ui->pushButton_retour->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/gui/image/icon/back-arrow.png"));

    QPixmap pm(QCoreApplication::applicationDirPath() + "/gui/image/image/imageArtilleur.png");

    ui->image1->setPixmap(pm);

    Artilleur artilleur;
    ui->label_1->setText(artilleur.getInfo());

    connect(ui->pushButton_retour, SIGNAL(clicked(bool)), this, SLOT(cacherMenuArmee()));
}

void widgetArmee::afficherMenuArmee()
{
    setVisible(true);

    emit affichage();
}

void widgetArmee::cacherMenuArmee()
{
    setVisible(false);

    emit cachage();
}

widgetArmee::~widgetArmee()
{
    delete ui;
}
