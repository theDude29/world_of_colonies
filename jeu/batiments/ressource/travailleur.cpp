#include "jeu/batiments/ressource/travailleur.h"
#include "mainwindow.h"
#include <QGraphicsOpacityEffect>
#include <QDateTime>
#include <QTimer>

Travailleur::Travailleur(QObject* parent, int maxPV, QSize taille, cout coutDeConstruction, int contenanceMax, int productivite, bool active)
    : Conteneur(parent, maxPV, taille, coutDeConstruction, contenanceMax)
{
    m_productivite = productivite;
    m_tempsDeConstruction = TEMPS_CONSTRUCTION_TRAVAILLEUR;

    m_boutonCollecte = new QPushButton(MainWindow::getMainWindow());
    m_boutonCollecte->setVisible(false);
    if(active)
    {
        connect(m_boutonCollecte, SIGNAL(clicked(bool)), this, SLOT(recolterRessource()));

        QTimer* timer = new QTimer(MainWindow::getMainWindow());
        timer->setInterval(1000 * 60);
        timer->start();
        connect(timer, SIGNAL(timeout()), this, SLOT(verifierTiming()));
    }
}

void Travailleur::verifierTiming()
{
    QString timing = Bdd::getBdd()->getTimingBatiment(m_pseudo, m_typeBatiment, m_idFichierVillage);
    QDateTime derniereRecolte = QDateTime::fromString(timing, "yyyy:MM:dd:hh:mm:ss");

    QDateTime maintenant = QDateTime::currentDateTime();
    qint64 nbSecs = derniereRecolte.secsTo(maintenant);
    qint64 nbHeures = nbSecs/3600;

    m_contenance = nbHeures * m_productivite;
    if(m_contenance > m_contenanceMax) m_contenance = m_contenanceMax;

    if(m_contenance > 0)
    {
        m_boutonCollecte->setVisible(true);
    }
}

void Travailleur::majPosBoutonCollecte(int hauteur)
{
    hauteur = 1200 - hauteur;

    //taille (proportionnalite pour trouver les dimension
    QSize newTaille(40*hauteur/800, 45*hauteur/800);

    m_boutonCollecte->setIconSize(newTaille);
    m_boutonCollecte->setGeometry(QRect(m_boutonCollecte->pos(), newTaille));

    //position
    irr::core::vector2di pos2d = m_sceneCollisionManager->getScreenCoordinatesFrom3DPosition(m_meshSceneNode->getPosition());
    m_boutonCollecte->move(QPoint(pos2d.X + 5, pos2d.Y));
}

void Travailleur::kill()
{
    m_meshSceneNode->setVisible(false);
    cacherBoutonCollecte();
}

void Travailleur::recolterRessource()
{
    emit gagneDesRessources(m_contenance);
    m_contenance = 0;
    cacherBoutonCollecte();
    Bdd::getBdd()->majTimingBatiment(m_pseudo, m_typeBatiment, m_idFichierVillage);
}

void Travailleur::cacherBoutonCollecte()
{
    m_boutonCollecte->setVisible(false);
}

