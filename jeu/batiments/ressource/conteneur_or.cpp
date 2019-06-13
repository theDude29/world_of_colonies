#include "jeu/batiments/ressource/conteneur_or.h"

Conteneur_Or::Conteneur_Or() : Conteneur(MAX_PV_CONTENEUR_OR, QSize(TAILLE_CONTENEUR_OR_W, TAILLE_CONTENEUR_OR_H), cout{COUT_CONSTRUCTION_CONTENEUR_OR_NOURRITURE, COUT_CONSTRUCTION_CONTENEUR_OR_OR, XP_CONTENEUR}, CONTENANCE_MAX_CONTENEUR_OR)
{
    m_typeBatiment = conteneurOr;

    m_meshBatiment = SceneManager::getSceneManager()->getMesh("mesh/batiment/ressource/banque.obj");
    m_meshSceneNode = SceneManager::getSceneManager()->addMeshSceneNode(m_meshBatiment);
    m_meshSceneNode->setScale(irr::core::vector3df(10,10,10));
    m_meshSceneNode->setVisible(false);
}

QString Conteneur_Or::getInfo()
{
    QString texte = "";

    texte += "La banque est un batiment servant a stocker de l'or.\n\n";
    texte += "contenance max : ";
    texte += QString::number(m_contenanceMax);
    texte += " or";
    texte += "\npoints de vie : ";
    texte += QString::number(m_maxPV);
    texte += "\n\n  -cout nourriture : ";
    texte += QString::number(m_cout.nbNourriture);
    texte += "\n";
    texte += "  -cout or : ";
    texte += QString::number(m_cout.nbOr);

    return texte;
}

Conteneur_Or::~Conteneur_Or()
{

}

