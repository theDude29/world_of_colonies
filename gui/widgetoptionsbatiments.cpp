#include "widgetoptionsbatiments.h"
#include "ui_widgetoptionsbatiments.h"
#include "utilitaire/getcss.h"

WidgetOptionsBatiments::WidgetOptionsBatiments(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::WidgetOptionsBatiments)
{
    ui->setupUi(this);

    setFixedSize(200,150);

    ui->label_pivoter->setVisible(false);
    ui->pushButton_droite->setVisible(false);
    ui->pushButton_gauche->setVisible(false);
    ui->pushButton_confirmer->setVisible(false);

    ui->pushButton_deplacer->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/gui/image/icon/cross-arrows.png"));
    ui->pushButton_vendre->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/gui/image/icon/money.png"));
    ui->pushButton_retour->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/gui/image/icon/back-arrow.png"));
    ui->pushButton_pivoter->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/gui/image/icon/circle-arrows.png"));
    ui->pushButton_droite->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/gui/image/icon/arrow-right.png"));
    ui->pushButton_gauche->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/gui/image/icon/arrow-left.png"));

    connect(ui->pushButton_retour, SIGNAL(clicked(bool)), this, SLOT(setVisible(bool)));
    connect(ui->pushButton_deplacer, SIGNAL(clicked(bool)), this, SLOT(setVisible(bool)));
    connect(ui->pushButton_pivoter, SIGNAL(clicked(bool)), this, SLOT(afficherBoutonsPivoter()));
    connect(ui->pushButton_vendre, SIGNAL(clicked(bool)), this, SLOT(setVisible(bool)));
    connect(ui->pushButton_confirmer, SIGNAL(clicked(bool)), this, SLOT(cacherBoutonsPivoter()));
}

QPushButton* WidgetOptionsBatiments::getBoutonDeplacer()
{
    return ui->pushButton_deplacer;
}

QPushButton* WidgetOptionsBatiments::getBoutonVendre()
{
    return ui->pushButton_vendre;
}

QPushButton* WidgetOptionsBatiments::getBoutonDroite()
{
    return ui->pushButton_droite;
}

QPushButton* WidgetOptionsBatiments::getBoutonGauche()
{
    return ui->pushButton_gauche;
}

QPushButton* WidgetOptionsBatiments::getBoutonRetour()
{
    return ui->pushButton_retour;
}

void WidgetOptionsBatiments::afficherBoutonsPivoter()
{
    setFixedSize(120,100);

    ui->label_pivoter->setVisible(true);
    ui->pushButton_droite->setVisible(true);
    ui->pushButton_gauche->setVisible(true);
    ui->pushButton_confirmer->setVisible(true);

    ui->label_decription->setVisible(false);
    ui->pushButton_deplacer->setVisible(false);
    ui->pushButton_pivoter->setVisible(false);
    ui->pushButton_retour->setVisible(false);
    ui->pushButton_vendre->setVisible(false);
}

void WidgetOptionsBatiments::cacherBoutonsPivoter()
{
    setVisible(false);

    setFixedSize(200, 150);

    ui->label_pivoter->setVisible(false);
    ui->pushButton_droite->setVisible(false);
    ui->pushButton_gauche->setVisible(false);
    ui->pushButton_confirmer->setVisible(false);

    ui->label_decription->setVisible(true);
    ui->pushButton_deplacer->setVisible(true);
    ui->pushButton_pivoter->setVisible(true);
    ui->pushButton_retour->setVisible(true);
    ui->pushButton_vendre->setVisible(true);
}

WidgetOptionsBatiments::~WidgetOptionsBatiments()
{
    delete ui;
}
