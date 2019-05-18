#include "jeu/batiments/ressource/conteneur_nourriture.h"

Conteneur_nourriture::Conteneur_nourriture() :  Conteneur(MAX_PV_CONTENEUR_NOURRITURE, QSize(TAILLE_CONTENEUR_NOURRITURE_W, TAILLE_CONTENEUR_NOURRITURE_H), cout{COUT_CONSTRUCTION_CONTENEUR_NOURRITURE_NOURRITURE, COUT_CONSTRUCTION_CONTENEUR_NOURRITURE_OR, XP_CONTENEUR}, CONTENANCE_MAX_CONTENEUR_NOURRITURE)
{
    m_typeBatiment = conteneurNourriture;

    m_meshBatiment = SceneManager::getSceneManager()->getMesh("mesh/ressource/entrepot.obj");
    m_meshSceneNode = SceneManager::getSceneManager()->addMeshSceneNode(m_meshBatiment);
    m_meshSceneNode->setScale(irr::core::vector3df(10,10,10));
    m_meshSceneNode->setVisible(false);
}

QString Conteneur_nourriture::getInfo()
{
    QString texte = "";

    texte += "L'entrepot est un batiment servant a stocker de la nourriture.\n\n";
    texte += "contenance max : ";
    texte += QString::number(m_contenanceMax);
    texte += " nourriture";
    texte += "\npoints de vie : ";
    texte += QString::number(m_maxPV);
    texte += "\n\n  -cout nourriture : ";
    texte += QString::number(m_cout.nbNourriture);
    texte += "\n";
    texte += "  -cout or : ";
    texte += QString::number(m_cout.nbOr);

    return texte;
}

Conteneur_nourriture::~Conteneur_nourriture()
{

}

