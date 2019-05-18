#include "jeu/batiments/ressource/travailleur_or.h"

Travailleur_Or::Travailleur_Or(bool active)
    : Travailleur(MAX_PV_TRAVAILLEUR_OR, QSize(TAILLE_TRAVAILLEUR_OR_W, TAILLE_TRAVAILLEUR_OR_H), cout{COUT_CONSTRUCTION_TRAVAILLEUR_OR_NOURRITURE, COUT_CONSTRUCTION_TRAVAILLEUR_OR_OR, XP_TRAVAILLEUR}, CONTENANCE_MAX_TRAVAILLEUR_OR, PRODUCTIVITE_TRAVAILLEUR_OR, active)
{
    m_typeBatiment = travailleurOr;

    m_meshBatiment = SceneManager::getSceneManager()->getMesh("mesh/ressource/usine.obj");
    m_meshSceneNode = SceneManager::getSceneManager()->addMeshSceneNode(m_meshBatiment);
    m_meshSceneNode->setScale(irr::core::vector3df(10,10,10));
    m_meshSceneNode->setVisible(false);

    if(active)
    m_boutonCollecte->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/gui/image/image/or.png"));
}

QString Travailleur_Or::getInfo()
{
    QString texte = "";

    texte += "L'usine est un batiment servant a produire de l'or.\n\n";
    texte += "productivite : ";
    texte += QString::number(m_productivite);
    texte += " or/heure\ncontenance max : ";
    texte += QString::number(m_contenanceMax);
    texte += " or";
    texte += "\npoints de vie : ";
    texte += QString::number(m_maxPV);
    texte += "\n\n  -cout nourriture : ";
    texte += QString::number(m_cout.nbNourriture);
    texte += "\n  -cout or : ";
    texte += QString::number(m_cout.nbOr);

    return texte;
}

Travailleur_Or::~Travailleur_Or()
{

}
