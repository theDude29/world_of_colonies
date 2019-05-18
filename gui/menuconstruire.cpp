#include "menuconstruire.h"
#include "ui_menuconstruire.h"
#include <QCoreApplication>
#include <QMessageBox>
#include <utilitaire/getcss.h>

#include <iostream>

MenuConstruire::MenuConstruire(QWidget *parent, Village* village) :
    QFrame(parent),
    ui(new Ui::MenuConstruire)
{
    ui->setupUi(this);

    m_village = village;

    //FINITONS
    setStyleSheet(getCSS("gui/css/style_menuConstruire.css"));

    QPixmap pm(QCoreApplication::applicationDirPath() + "/gui/image/image/imageMaison.png"),
            pm2(QCoreApplication::applicationDirPath() + "/gui/image/image/imageUsine.png"),
            pm3(QCoreApplication::applicationDirPath() + "/gui/image/image/imageStockageMaison.png"),
            pm4(QCoreApplication::applicationDirPath() + "/gui/image/image/imageStockageUsine.png"),
            pm5(QCoreApplication::applicationDirPath() + "/gui/image/image/imageCampEntrainement.png"),
            pm6(QCoreApplication::applicationDirPath() + "/gui/image/image/imageCaserne.png"),
            pm7(QCoreApplication::applicationDirPath() + "/gui/image/image/imagePortail.png"),
            pm8(QCoreApplication::applicationDirPath() + "/gui/image/image/imageCanon.png"),
            pm9(QCoreApplication::applicationDirPath() + "/gui/image/image/imageTourelle.png"),
            pm10(QCoreApplication::applicationDirPath() + "/gui/image/image/imageMortier.png");

    ui->image_1->setPixmap(pm);
    ui->image_2->setPixmap(pm2);
    ui->image_3->setPixmap(pm3);
    ui->image_4->setPixmap(pm4);
    ui->image_bat_armee1->setPixmap(pm5);
    ui->image_bat_armee_2->setPixmap(pm6);
    ui->image_bat_arme3->setPixmap(pm7);
    ui->image_defense1->setPixmap(pm8);
    ui->image_defense2->setPixmap(pm9);
    ui->image_defense3->setPixmap(pm10);

    Conteneur_Or ctnOr;
    ui->label_ressource3->setText(ctnOr.getInfo());
    Conteneur_nourriture ctnNour;
    ui->label_ressource4->setText(ctnNour.getInfo());
    Travailleur_Or trvOr(false);
    ui->label_descriptionRessource2->setText(trvOr.getInfo());
    Travailleur_Nourriture trvNour(false);
    ui->label_DescriptionRessource1->setText(trvNour.getInfo());
    CampEntrainement camp;
    ui->label_armee1->setText(camp.getInfo());
    Caserne caserne;
    ui->label_armee2->setText(caserne.getInfo());
    Portail portail;
    ui->label_armee3->setText(portail.getInfo());
    Canon canon;
    ui->label_defense1->setText(canon.getInfo());
    Tourelle tourelle;
    ui->label_defense2->setText(tourelle.getInfo());
    Mortier mortier;
    ui->label_defense3->setText(mortier.getInfo());

    ui->pushButton_retour->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/gui/image/icon/back-arrow.png"));

    connect(ui->pushButton_retour, SIGNAL(clicked(bool)), this, SLOT(cacherMenuConstuire()));

    connect(ui->pushButton_construireRessource1, SIGNAL(clicked(bool)), this, SLOT(bouttonRc1Clique()));
    connect(ui->pushButton_construireRessource2, SIGNAL(clicked(bool)), this, SLOT(bouttonRc2Clique()));
    connect(ui->pushButton_construireRessource3, SIGNAL(clicked(bool)), this, SLOT(bouttonRc3Clique()));
    connect(ui->pushButton_constuireRessource4, SIGNAL(clicked(bool)), this, SLOT(bouttonRc4Clique()));
    connect(ui->pushButton_construireArmee1, SIGNAL(clicked(bool)), this, SLOT(bouttonArmee1Clique()));
    connect(ui->pushButton_construireArmee2, SIGNAL(clicked(bool)), this, SLOT(bouttonArmee2Clique()));
    connect(ui->pushButton_construireArmee3, SIGNAL(clicked(bool)), this, SLOT(bouttonArmee3Clique()));
    connect(ui->pushButton_construire_defense1, SIGNAL(clicked(bool)), this, SLOT(bouttonDefense1Clique()));
    connect(ui->pushButton_defense2, SIGNAL(clicked(bool)), this, SLOT(bouttonDefense2Clique()));
    connect(ui->pushButton_defense3, SIGNAL(clicked(bool)), this, SLOT(bouttonDefense3Clique()));
}

void MenuConstruire::cacherMenuConstuire()
{
    setVisible(false);

    emit cachage();
}

void MenuConstruire::afficherMenuConstruire()
{
    setVisible(true);

    emit affichage();
}

void MenuConstruire::bouttonRc1Clique()
{
    if(m_village->essayerConstruireBatiment(new Travailleur_Nourriture))
    {
        cacherMenuConstuire();
    }

    else
    {
        QMessageBox::critical(this, "Erreur", "Vous ne possedez pas les materiaux"
        " necessaires a la construction de ce batiment");
    }
}

void MenuConstruire::bouttonRc2Clique()
{
    if(m_village->essayerConstruireBatiment(new Travailleur_Or))
    {
        cacherMenuConstuire();
    }

    else
    {
        QMessageBox::critical(this, "Erreur", "Vous ne possedez pas les materiaux"
        " necessaires a la construction de ce batiment");
    }
}

void MenuConstruire::bouttonRc3Clique()
{
    if(m_village->essayerConstruireBatiment(new Conteneur_Or()))
    {
        cacherMenuConstuire();
    }

    else
    {
        QMessageBox::critical(this, "Erreur", "Vous ne possedez pas les materiaux"
        " necessaires a la construction de ce batiment");
    }
}

void MenuConstruire::bouttonRc4Clique()
{
    if(m_village->essayerConstruireBatiment(new Conteneur_nourriture()))
    {
        cacherMenuConstuire();
    }

    else
    {
        QMessageBox::critical(this, "Erreur", "Vous ne possedez pas les materiaux"
        " necessaires a la construction de ce batiment");
    }
}

void MenuConstruire::bouttonArmee1Clique()
{
    if(m_village->essayerConstruireBatiment(new CampEntrainement()))
    {
        cacherMenuConstuire();
    }

    else
    {
        QMessageBox::critical(this, "Erreur", "Vous ne possedez pas les materiaux"
        " necessaires a la construction de ce batiment");
    }
}

void MenuConstruire::bouttonArmee2Clique()
{
    if(m_village->essayerConstruireBatiment(new Caserne()))
    {
        cacherMenuConstuire();
    }

    else
    {
        QMessageBox::critical(this, "Erreur", "Vous ne possedez pas les materiaux"
        " necessaires a la construction de ce batiment");
    }
}

void MenuConstruire::bouttonArmee3Clique()
{
    if(m_village->essayerConstruireBatiment(new Portail()))
    {
        cacherMenuConstuire();
    }

    else
    {
        QMessageBox::critical(this, "Erreur", "Vous ne possedez pas les materiaux"
        " necessaires a la construction de ce batiment");
    }
}

void MenuConstruire::bouttonDefense1Clique()
{
    if(m_village->essayerConstruireBatiment(new Canon()))
    {
        cacherMenuConstuire();
    }

    else
    {
        QMessageBox::critical(this, "Erreur", "Vous ne possedez pas les materiaux"
        " necessaires a la construction de ce batiment");
    }
}

void MenuConstruire::bouttonDefense2Clique()
{
    if(m_village->essayerConstruireBatiment(new Tourelle()))
    {
        cacherMenuConstuire();
    }

    else
    {
        QMessageBox::critical(this, "Erreur", "Vous ne possedez pas les materiaux"
        " necessaires a la construction de ce batiment");
    }
}

void MenuConstruire::bouttonDefense3Clique()
{
    if(m_village->essayerConstruireBatiment(new Mortier))
    {
        cacherMenuConstuire();
    }

    else
    {
        QMessageBox::critical(this, "Erreur", "Vous ne possedez pas les materiaux"
        " necessaires a la construction de ce batiment");
    }
}

MenuConstruire::~MenuConstruire()
{
    delete ui;
}
