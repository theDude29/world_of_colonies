#include "campentrainement.h"

CampEntrainement::CampEntrainement(QObject* parent) : Batiment(parent, MAX_PV_CAMP_ENTRAINEMENT, QSize(TAILLE_CAMP_ENTRAINEMENT_X, TAILLE_CAMP_ENTRAINEMENT_Z), cout{COUT_CONSTRUCTION_NOURRITURE_CAMP_ENTRAINEMENT, COUT_CONSTRUCTION_OR_CAMP_ENTRAINEMENT, XP_CAMP_ENTRAINEMENT})
{
    m_typeBatiment = campEntrainement;

    m_texture = Driver::getDriver()->getTexture("mesh/texture/texture_armee.png");
    m_meshBatiment = SceneManager::getSceneManager()->getMesh("mesh/batiment/armee/campEntrainement.obj");
    m_meshSceneNode = SceneManager::getSceneManager()->addMeshSceneNode(m_meshBatiment);
    m_meshSceneNode->setScale(irr::core::vector3df(10,10,10));
    m_meshSceneNode->setVisible(false);
}

QString CampEntrainement::getInfo()
{
    QString texte = "";
    texte += "Le camp d'entrainement est un batiment servant a former des troupes pour piller les villages des autres joueurs.\n\n";
    texte += "points de vie : ";
    texte += QString::number(m_maxPV);
    texte += "\n\n  -cout nourriture : ";
    texte += QString::number(m_cout.nbNourriture);
    texte += "\n";
    texte += "  -cout or : ";
    texte += QString::number(m_cout.nbOr);

    return texte;
}
