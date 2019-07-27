#include "jeu/batiments/batiment.h"
#include "mainwindow.h"

Batiment::Batiment(int maxPV, QSize taille, cout coutDeConstruction) : Item(), m_maxPV(maxPV), m_taille(taille)
{
    m_sceneCollisionManager = SceneManager::getSceneManager()->getSceneCollisionManager();
    m_id = -1;
    m_idFichierVillage = -1;
    m_meshSceneNode = NULL;
    m_meshBatiment = NULL;
    m_cout = coutDeConstruction;
}

void Batiment::kill()
{
    m_meshSceneNode->setVisible(false);
}

irr::core::vector3df Batiment::getPosition()
{
    return m_meshSceneNode->getPosition();
}

void Batiment::setRotation(irr::core::vector3df rot)
{
    m_meshSceneNode->setRotation(rot);
}

irr::core::vector3df Batiment::getRotation()
{
    return m_meshSceneNode->getRotation();
}

void Batiment::setPseudo(QString pseudo)
{
    m_pseudo = pseudo;
}

void Batiment::setPosition(irr::core::vector3df pos)
{
    m_meshSceneNode->setPosition(pos);
}

void Batiment::setIdFichierVillage(int id)
{
    m_idFichierVillage = id;
}

bool Batiment::isVisible()
{
    return m_meshSceneNode->isVisible();
}

int Batiment::getIdFichierVillage()
{
    return m_idFichierVillage;
}

int Batiment::getType()
{
    return m_typeBatiment;
}

irr::video::ITexture* Batiment::getTexture()
{
    return m_texture;
}

int Batiment::getId()
{
    return m_id;
}

void Batiment::setId(int id)
{
    m_id = id;
}

void Batiment::afficherBatimentConstruit()
{
    m_meshSceneNode->setMaterialTexture(0, m_texture);
    m_meshSceneNode->setVisible(true);
}

void Batiment::estVise()
{

}

void Batiment::estPlusVise()
{

}

Batiment::~Batiment()
{

}
