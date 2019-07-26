#include "tank.h"
#include "singleton/SceneManager.h"

Tank::Tank() : Soldat()
{
    m_degats = DEGAT_TANK;
    m_vitesseAttaque = VITESSE_ATTAQUE_TANK;
    m_dps = m_degats / m_vitesseAttaque;
    m_pointsVies = PV_TANK;
    m_vitesse = VITESSE_TANK;
    m_portee = PORTEE_TANK;
    m_cout.nbNourriture = COUT_NOURRITURRE_TANK;
    m_cout.nbOr = COUT_OR_TANK;
    m_cout.nbXp = XP_TANK;
    m_place = PLACE_TANK;

    m_meshSceneNode = SceneManager::getSceneManager()->addMeshSceneNode(SceneManager::getSceneManager()->getMesh("mesh/troupe/fantassin.obj"));
    m_meshSceneNode->setScale(irr::core::vector3df(10,10,10));
}

QString Tank::getInfo()
{
    QString texte = "";
    texte += "Le tank est un soldat possedants de nombreux points de vie.\n\n";
    texte += "degats par seconde : ";
    texte += QString::number(m_dps);
    texte += "\nporte : ";
    texte += QString::number(m_portee);
    texte += "\npoints de vie : ";
    texte += QString::number(m_pointsVies);
    texte += "\nvitesse : ";
    texte += QString::number(m_vitesse);
    texte += "\nnombre de places requises : ";
    texte += QString::number(m_place);
    texte += "\n\n  -cout nourriture : ";
    texte += QString::number(m_cout.nbNourriture);
    texte += "\n";
    texte += "  -cout or : ";
    texte += QString::number(m_cout.nbOr);

    return texte;
}

