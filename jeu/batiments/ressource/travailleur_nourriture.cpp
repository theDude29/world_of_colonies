#include "jeu/batiments/ressource/travailleur_nourriture.h"

Travailleur_Nourriture::Travailleur_Nourriture(bool active) : Travailleur(MAX_PV_TRAVAILLEUR_NOURRITURE, QSize(TAILLE_TRAVAILLEUR_NOURRITURE_W, TAILLE_TRAVAILLEUR_NOURRITURE_H), cout{COUT_CONSTRUCTION_TRAVAILLEUR_NOURRITURE_NOURRITURE, COUT_CONSTRUCTION_TRAVAILLEUR_NOURRITURE_OR, XP_TRAVAILLEUR}, CONTENANCE_MAX_TRAVAILLEUR_NOURRITURE, PRODUCTIVITE_TRAVAILLEUR_NOURRITURE, active)
{
    m_typeBatiment = travailleurNourriture;

    m_meshBatiment = SceneManager::getSceneManager()->getMesh("mesh/batiment/ressource/maison.obj");
    m_meshSceneNode = SceneManager::getSceneManager()->addMeshSceneNode(m_meshBatiment);
    m_meshSceneNode->setScale(irr::core::vector3df(10,10,10));
    m_meshSceneNode->setVisible(false);

    if(active)
    m_boutonCollecte->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/gui/image/image/corn.png"));
}

QString Travailleur_Nourriture::getInfo()
{
    QString texte = "";

    texte += "La maison est un batiment servant a produire de la nourriture.\n\n";
    texte += "productivite : ";
    texte += QString::number(m_productivite);
    texte += " nourriture/heure\ncontenance max : ";
    texte += QString::number(m_contenanceMax);
    texte += " nourriture";
    texte += "\npoints de vie : ";
    texte += QString::number(m_maxPV);
    texte += "\n\n  -cout nourriture : ";
    texte += QString::number(m_cout.nbNourriture);
    texte += "\n  -cout or : ";
    texte += QString::number(m_cout.nbOr);

    return texte;
}

Travailleur_Nourriture::~Travailleur_Nourriture()
{

}
