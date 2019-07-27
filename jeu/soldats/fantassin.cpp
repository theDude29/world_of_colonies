#include "fantassin.h"
#include "singleton/SceneManager.h"

Fantassin::Fantassin() : Soldat()
{
    m_degats = DEGAT_FANTASSIN;
    m_vitesseAttaque = VITESSE_ATTAQUE_FANTASSIN;
    m_dps = m_degats / m_vitesseAttaque;
    m_pointsVies = PV_FANTASSIN;
    m_vitesse = VITESSE_FANTASSIN;
    m_portee = PORTEE_FANTASSIN;
    m_cout.nbNourriture = COUT_NOURRITURRE_FANTASSIN;
    m_cout.nbOr = COUT_OR_FANTASSIN;
    m_cout.nbXp = XP_FANTASSIN;
    m_place = PLACE_FANTASSIN;

    m_meshSceneNode = SceneManager::getSceneManager()->addMeshSceneNode(SceneManager::getSceneManager()->getMesh("mesh/troupe/fantassin.obj"));
    m_meshSceneNode->setScale(irr::core::vector3df(10,10,10));
    m_meshSceneNode->setRotation(irr::core::vector3df(0,90,0));
    m_meshSceneNode->setMaterialTexture(0, m_texture);
}

QString Fantassin::getInfo()
{
    QString texte = "";
    texte += "Le fantassin est un soldat polyvalant ayant une bonne sante et de bon degat mais une faible portee.\n\n";
    texte += "degats par seconde : ";
    texte += QString::number(DEGAT_FANTASSIN / VITESSE_ATTAQUE_FANTASSIN);
    texte += "\nporte : ";
    texte += QString::number(PORTEE_FANTASSIN);
    texte += "\npoints de vie : ";
    texte += QString::number(PV_FANTASSIN);
    texte += "\nvitesse : ";
    texte += QString::number(VITESSE_FANTASSIN);
    texte += "\nnombre de places requises : ";
    texte += QString::number(PLACE_FANTASSIN);
    texte += "\n\n  -cout nourriture : ";
    texte += QString::number(COUT_NOURRITURRE_FANTASSIN);
    texte += "\n";
    texte += "  -cout or : ";
    texte += QString::number(COUT_OR_FANTASSIN);

    return texte;
}
