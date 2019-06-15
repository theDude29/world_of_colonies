#include "widgetarmee.h"
#include "ui_widgetarmee.h"
#include "utilitaire/getcss.h"

widgetArmee::widgetArmee(QWidget *parent, Village *village) :
    QFrame(parent),
    ui(new Ui::widgetArmee)
{
    ui->setupUi(this);

    m_village = village;

    m_armee = new Armee();

    //FINITONS
    setStyleSheet(getCSS("gui/css/style_menuConstruire.css"));
    ui->pushButton_retour->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/gui/image/icon/back-arrow.png"));

    QPixmap pm(QCoreApplication::applicationDirPath() + "/gui/image/image/imageArtilleur.png"),
            pm2(QCoreApplication::applicationDirPath() + "/gui/image/image/imageTank.png"),
            pm3(QCoreApplication::applicationDirPath() + "/gui/image/image/imageFantassin.png");

    ui->image1->setPixmap(pm);
    ui->image2->setPixmap(pm2);
    ui->image3->setPixmap(pm3);

    ui->label_1->setText(m_artilleur.getInfo());
    ui->label_2->setText(m_tank.getInfo());
    ui->label_3->setText(m_fantassin.getInfo());

    connect(ui->pushButton_retour, SIGNAL(clicked(bool)), this, SLOT(cacherMenuArmee()));

    connect(ui->pushButton_1, SIGNAL(clicked(bool)), this, SLOT(bouttonArtilleurClique()));
}

void widgetArmee::majTexteStatsArmee()
{
    QString text = "Nombre de places occupes : ";
    text += QString::number(m_armee->getNbPlaceOccupe());
    text += "/";
    text += QString::number(m_armee->getNbPlaceMax());
    ui->label_statArmee->setText(text);
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

void widgetArmee::bouttonArtilleurClique()
{
    if(m_village->getNbOr() >= m_artilleur.getCout().nbOr &&
            m_village->getNbNourriture() >= m_artilleur.getCout().nbNourriture)
    {
        m_village->perdreRessource(m_artilleur.getCout());
        m_armee->ajouterArtilleur();
        majTexteStatsArmee();
        std::cout<<"ssssssinge"<<std::endl;
    }

    else
    {
        QMessageBox::critical(this, "Erreur", "Vous ne possedez pas les materiaux"
        " necessaires a la formation de ce soldat");
    }
}

widgetArmee::~widgetArmee()
{
    delete ui;

    delete m_armee;
}
