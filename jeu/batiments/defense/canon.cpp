#include "canon.h"

Canon::Canon(QObject* parent) : Defense(parent, MAX_PV_CANON, QSize(TAILLE_CANON_X, TAILLE_CANON_Z), cout{COUT_CONSTRUCTION_NOURRITURE_CANON, COUT_CONSTRUCTION_OR_CANON, XP_CANON})
{
    m_typeBatiment = canon;

    m_meshBatiment = SceneManager::getSceneManager()->getMesh("mesh/batiment/defense/canon.obj");
    m_meshSceneNode = SceneManager::getSceneManager()->addMeshSceneNode(m_meshBatiment);
    m_meshSceneNode->setScale(irr::core::vector3df(10,10,10));
    m_meshSceneNode->setVisible(false);

    m_porte = PORTE_CANON;
    m_spherePorte = SceneManager::getSceneManager()->addSphereSceneNode(m_porte, 32, 0, -1, m_meshSceneNode->getPosition());
    m_spherePorte->setVisible(false);
    m_spherePorte->setMaterialType(irr::video::EMT_TRANSPARENT_VERTEX_ALPHA);
    SceneManager::getSceneManager()->getMeshManipulator()->setVertexColorAlpha(m_spherePorte->getMesh(), 50);

    m_dps = DPS_CANON;
}

QString Canon::getInfo()
{
    QString texte = "";
    texte += "Le canon est un batiment servant a vous proteger des joueurs adverses voulant vous piller.\n\n";
    texte += "porte : ";
    texte += QString::number(m_porte);
    texte += "\ndegats par seconde : ";
    texte += QString::number(m_dps);
    texte += "\npoints de vie : ";
    texte += QString::number(m_maxPV);
    texte += "\n\n  -cout nourriture : ";
    texte += QString::number(m_cout.nbNourriture);
    texte += "\n";
    texte += "  -cout or : ";
    texte += QString::number(m_cout.nbOr);

    return texte;
}
