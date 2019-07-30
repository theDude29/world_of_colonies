#include "jeu/batiments/batiment.h"
#include "mainwindow.h"

Batiment::Batiment(QObject *parent, int maxPV, QSize taille, cout coutDeConstruction) : Item(parent, maxPV), m_taille(taille)
{
    m_id = -1;
    m_idFichierVillage = -1;
    m_meshSceneNode = NULL;
    m_meshBatiment = NULL;
    m_cout = coutDeConstruction;
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
