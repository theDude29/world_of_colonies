#include "portail.h"

Portail::Portail() : Batiment(MAX_PV_PORTAIL, QSize(TAILLE_PORTAIL_X, TAILLE_PORTAIL_Z), cout{COUT_CONSTRUCTION_NOURRITURE_PORTAIL, COUT_CONSTRUCTION_OR_PORTAIL, XP_PORTAIL})
{
    m_typeBatiment = portail;

    m_texture = Driver::getDriver()->getTexture("mesh/texture/texture_armee.png");
    m_meshBatiment = SceneManager::getSceneManager()->getMesh("mesh/batiment/armee/portail.obj");
    m_meshSceneNode = SceneManager::getSceneManager()->addMeshSceneNode(m_meshBatiment);
    m_meshSceneNode->setScale(irr::core::vector3df(10,10,10));
    m_meshSceneNode->setVisible(false);
}

QString Portail::getInfo()
{
    QString texte = "";
    texte += "Le portail est un batiment servant a teleporter vos troupes dans les villages adverses, sans lui vous ne pourrez pas piller les villages adverses.\n\n";
    texte += "points de vie : ";
    texte += QString::number(m_maxPV);
    texte += "\n\n  -cout nourriture : ";
    texte += QString::number(m_cout.nbNourriture);
    texte += "\n";
    texte += "  -cout or : ";
    texte += QString::number(m_cout.nbOr);

    return texte;
}

