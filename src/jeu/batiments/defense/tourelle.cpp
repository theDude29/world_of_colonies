#include "tourelle.h"

Tourelle::Tourelle(QObject* parent) : Defense(parent, MAX_PV_TOURELLE, QSize(TAILLE_TOURELLE_X, TAILLE_TOURELLE_Z), cout{COUT_CONSTRUCTION_NOURRITURE_TOURELLE, COUT_CONSTRUCTION_OR_TOURELLE, XP_TOURELLE})
{
    m_typeBatiment = tourelle;

    m_meshBatiment = SceneManager::getSceneManager()->getMesh("mesh/batiment/defense/tourelle.obj");
    m_meshSceneNode = SceneManager::getSceneManager()->addMeshSceneNode(m_meshBatiment);
    m_meshSceneNode->setScale(irr::core::vector3df(10,10,10));
    m_meshSceneNode->setVisible(false);

    m_porte = PORTE_TOURELLE;
    m_spherePorte = SceneManager::getSceneManager()->addSphereSceneNode(m_porte, 32, 0, -1, m_meshSceneNode->getPosition());
    m_spherePorte->setVisible(false);
    m_spherePorte->setMaterialType(irr::video::EMT_TRANSPARENT_VERTEX_ALPHA);
    SceneManager::getSceneManager()->getMeshManipulator()->setVertexColorAlpha(m_spherePorte->getMesh(), 50);

    m_dps = DEGAT_TOURELLE / VITESSE_ATTAQUE_TOURELLE;
    m_vitesseAttaque = VITESSE_ATTAQUE_TOURELLE;
    m_degat = DEGAT_TOURELLE;
    m_tailleProjectile = 6;
}

QString Tourelle::getInfo()
{
    QString texte = "";
    texte += "La tourelle est un puissant batiment servant a vous proteger des joueurs adverses voulant vous piller.\n\n";
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
