#include "widgetconnexion.h"
#include "ui_widgetconnexion.h"
#include "utilitaire/getcss.h"
#include <QFontDatabase>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include "bdd/bdd.h"
#include <utilitaire/sha1.h>

WidgetConnexion::WidgetConnexion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetConnexion)
{
    ui->setupUi(this);

    //FINITIONS
    setMinimumSize(QSize(800,600));

    setStyleSheet(getCSS("gui/css/style_widgetConnexion.css"));

    QFontDatabase fontdtb;
    fontdtb.addApplicationFont(QCoreApplication::applicationDirPath() + "/galaxieLointaine.ttf");

    QPixmap bkgnd(QCoreApplication::applicationDirPath() + "/gui/image/image/fondEtoile.png");
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    parent->setPalette(palette);

    //nom utilisateur retenue
    QFile fichier(QString("parametre/pseudo.txt"));
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&fichier);
    QString nomUtilisateurRetenu = flux.readAll();
    if(nomUtilisateurRetenu != "")
    {
        ui->checkBox_souvenireNomUtilisateur->setChecked(true);
    }
    ui->lineEdit_nomUtilisateur->setText(nomUtilisateurRetenu);

    //password(lettre cache)
    ui->lineEdit_mdp->setEchoMode(QLineEdit::Password);

    connect(ui->pushButton_jouer, SIGNAL(clicked(bool)), this, SLOT(connexion()));
}

bool WidgetConnexion::connexion()
{
    Bdd* bdd;
    sql::Connection* connection;
    sql::Statement* requete;
    sql::ResultSet* reponse;

    bdd = Bdd::getBdd();
    connection = bdd->getBddConnection();
    requete = connection->createStatement();

    reponse = requete->executeQuery("SELECT * FROM Membres");

    std::string pseudoUtilisateur = ui->lineEdit_nomUtilisateur->text().toStdString();
    std::string mdpUtilisateur = ui->lineEdit_mdp->text().toStdString();
    std::string mdpUtilisateurHash = sha1(mdpUtilisateur);

    if(ui->lineEdit_nomUtilisateur->text() != "")
    {
        if(ui->lineEdit_mdp->text() != "")
        {
            bool pseudoEstFaut = false, mdpEstFaut = false;
            while(reponse->next())
            {
                std::string pseudo = reponse->getString("pseudo").asStdString();
                if(pseudo == pseudoUtilisateur)
                {
                    std::string mdp = reponse->getString("password").asStdString();
                    if(mdp == mdpUtilisateurHash)
                    {
                        m_pseudo = QString(pseudoUtilisateur.c_str());
                        retenirNomUtilisateur(QString(pseudoUtilisateur.c_str()), ui->checkBox_souvenireNomUtilisateur->isChecked());
                        emit connecte();
                    }

                    else
                    {
                        mdpEstFaut = true;
                    }
                }

                else
                {
                    pseudoEstFaut = true;
                }
            }

            if(pseudoEstFaut)
            {
                ui->label_erreur->setText(QString("Il n'y a aucun compte appelle \"" + QString(pseudoUtilisateur.c_str()) + QString("\"")));
            }

            if(mdpEstFaut)
            {
                ui->label_erreur->setText(QString("Le mot de passe est faut."));
            }
        }

        else
        {
            ui->label_erreur->setText(QString("Veuillez entrer votre mot de passe."));
        }
    }

    else
    {
        ui->label_erreur->setText(QString("Veuillez entrer votre nom d'utilisateur."));
    }

    delete connection;
    delete requete;
    delete reponse;

    return false;
}

QString WidgetConnexion::getPseudo()
{
    return m_pseudo;
}

void WidgetConnexion::retenirNomUtilisateur(QString pseudo, bool vraiment)
{
    QFile file("parametre/pseudo.txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream flux(&file);
    flux.setCodec("UTF-8");

    if(vraiment)
    {
         flux<<pseudo;
    }

    else
    {
        flux<<"";
    }

    file.close();
}

WidgetConnexion::~WidgetConnexion()
{
    delete ui;
}
