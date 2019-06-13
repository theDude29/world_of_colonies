#include "caserne.h"

Caserne::Caserne() : Batiment(MAX_PV_CASERNE, QSize(TAILLE_CASERNE_X, TAILLE_CASERNE_Z), cout{COUT_CONSTRUCTION_NOURRITURE_CASERNE, COUT_CONSTRUCTION_OR_CASERNE, XP_CASERNE})
{
    m_typeBatiment = caserne;

    m_texture = Driver::getDriver()->getTexture("mesh/texture/texture_armee.png");
    m_meshBatiment = SceneManager::getSceneManager()->getMesh("mesh/batiment/armee/caserne.obj");
    m_meshSceneNode = SceneManager::getSceneManager()->addMeshSceneNode(m_meshBatiment);
    m_meshSceneNode->setScale(irr::core::vector3df(10,10,10));
    m_meshSceneNode->setVisible(false);
}

QString Caserne::getInfo()
{
    QString texte = "";
    texte += "La caserne est un batiment servant a loger les troupes, sans elles vous ne pourrez pas former de troupes.\n\n";
    texte += "points de vie : ";
    texte += QString::number(m_maxPV);
    texte += "\n\n  -cout nourriture : ";
    texte += QString::number(m_cout.nbNourriture);
    texte += "\n";
    texte += "  -cout or : ";
    texte += QString::number(m_cout.nbOr);

    return texte;
}

