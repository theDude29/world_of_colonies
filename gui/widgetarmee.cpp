#include "widgetarmee.h"
#include "ui_widgetarmee.h"
#include "utilitaire/getcss.h"
#include <iostream>

widgetArmee::widgetArmee(QWidget *parent, Village *village, QString pseudo) :
    QFrame(parent),
    ui(new Ui::widgetArmee)
{
    ui->setupUi(this);

    m_village = village;

    m_armee = new Armee(pseudo);

    m_village->setArmee(m_armee);

    m_pseudo = pseudo;

    //FINITONS
    setStyleSheet(getCSS("gui/css/style_menuConstruireEtArmee.css"));
    ui->pushButton_retour->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/gui/image/icon/back-arrow.png"));

    QPixmap pm(QCoreApplication::applicationDirPath() + "/gui/image/image/imageArtilleur.png"),
            pm2(QCoreApplication::applicationDirPath() + "/gui/image/image/imageTank.png"),
            pm3(QCoreApplication::applicationDirPath() + "/gui/image/image/imageFantassin.png");

    ui->image1->setPixmap(pm);
    ui->image2->setPixmap(pm2);
    ui->image3->setPixmap(pm3);

    ui->label_1->setText(Artilleur::getInfo());
    ui->label_2->setText(Tank::getInfo());
    ui->label_3->setText(Fantassin::getInfo());

    connect(ui->pushButton_retour, SIGNAL(clicked(bool)), this, SLOT(cacherMenuArmee()));

    connect(ui->pushButton_1, SIGNAL(clicked(bool)), this, SLOT(bouttonArtilleurClique()));
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(bouttonTankClique()));
    connect(ui->pushButton_3, SIGNAL(clicked(bool)), this, SLOT(bouttonFantassinClique()));
}

Armee* widgetArmee::getArmee()
{
    return m_armee;
}

void widgetArmee::majTexteStatsArmee()
{
    QString text = "Nombre de places occupes : ";
    text += QString::number(m_armee->getNbPlaceOccupe());
    text += "/";
    text += QString::number(m_armee->getNbPlaceMax());
    ui->label_statArmee->setText(text);

    text = "Actuellement ";
    text += QString::number(m_armee->getNbArtilleur());
    text += " dans l'armee.";
    ui->label_infoTroupe1->setText(text);

    text = "Actuellement ";
    text += QString::number(m_armee->getNbTank());
    text += " dans l'armee.";
    ui->label_infoTroupe2->setText(text);

    text = "Actuellement ";
    text += QString::number(m_armee->getNbFantassin());
    text += " dans l'armee.";
    ui->label_infoTroupe3->setText(text);
}

void widgetArmee::afficherMenuArmee()
{
    setVisible(true);

    majTexteStatsArmee();

    emit affichage();
}

void widgetArmee::cacherMenuArmee()
{
    setVisible(false);

    emit cachage();
}

void widgetArmee::bouttonArtilleurClique()
{
    if(m_village->campEntrainementDansLeVillage())
    {
        if(m_village->getNbOr() >= COUT_OR_ARTILLEUR &&
                m_village->getNbNourriture() >= COUT_NOURRITURRE_ARTILLEUR)
        {
            if(m_armee->getNbPlaceMax() >= (m_armee->getNbPlaceOccupe() + PLACE_ARTILLEUR))
            {
                m_village->perdreRessource(cout{COUT_NOURRITURRE_ARTILLEUR, COUT_OR_ARTILLEUR, XP_ARTILLEUR});
                m_armee->ajouterArtilleur();
                majTexteStatsArmee();
            }

            else
            {
                QMessageBox::critical(this, "Erreur", "Vous n'avez pas assez de place dans votre caserne"
                " pour engager ce soldat. Construisez une caserne pour gagner 50 places de plus.");
            }
        }

        else
        {
            QMessageBox::critical(this, "Erreur", "Vous ne possedez pas les materiaux"
            " necessaires a la formation de ce soldat");
        }
    }

    else
    {
        QMessageBox::critical(this, "Erreur", "Vous devez construire un camp d'entrainement afin de former des troupes.");
    }
}

void widgetArmee::bouttonTankClique()
{
    if(m_village->campEntrainementDansLeVillage())
    {
        if(m_village->getNbOr() >= COUT_OR_TANK &&
                m_village->getNbNourriture() >= COUT_NOURRITURRE_TANK)
        {
            if(m_armee->getNbPlaceMax() > (m_armee->getNbPlaceOccupe() + PLACE_TANK))
            {
                m_village->perdreRessource(cout{COUT_NOURRITURRE_TANK, COUT_OR_TANK, XP_TANK});
                m_armee->ajouterTank();
                majTexteStatsArmee();
            }

            else
            {
                QMessageBox::critical(this, "Erreur", "Vous n'avez pas assez de place dans votre caserne"
                " pour engager ce soldat. Construisez une caserne pour gagner 50 places de plus.");
            }
        }

        else
        {
            QMessageBox::critical(this, "Erreur", "Vous ne possedez pas les materiaux"
            " necessaires a la formation de ce soldat");
        }
    }

    else
    {
        QMessageBox::critical(this, "Erreur", "Vous devez construire un camp d'entrainement afin de former des troupes.");
    }
}

void widgetArmee::bouttonFantassinClique()
{
    if(m_village->campEntrainementDansLeVillage())
    {
        if(m_village->getNbOr() >= COUT_OR_FANTASSIN &&
                m_village->getNbNourriture() >= COUT_NOURRITURRE_FANTASSIN)
        {
            if(m_armee->getNbPlaceMax() > (m_armee->getNbPlaceOccupe() + PLACE_FANTASSIN))
            {
                m_village->perdreRessource(cout{COUT_NOURRITURRE_FANTASSIN, COUT_OR_FANTASSIN, XP_FANTASSIN});
                m_armee->ajouterFantassin();
                majTexteStatsArmee();
            }

            else
            {
                QMessageBox::critical(this, "Erreur", "Vous n'avez pas assez de place dans votre caserne"
                " pour engager ce soldat. Construisez une caserne pour gagner 50 places de plus.");
            }
        }

        else
        {
            QMessageBox::critical(this, "Erreur", "Vous ne possedez pas les materiaux"
            " necessaires a la formation de ce soldat");
        }
    }

    else
    {
        QMessageBox::critical(this, "Erreur", "Vous devez construire un camp d'entrainement afin de former des troupes.");
    }
}

widgetArmee::~widgetArmee()
{
    delete ui;

    delete m_armee;
}
