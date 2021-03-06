#include "tank.h"

Tank::Tank(QObject *parent) : Soldat(parent, PV_TANK)
{
    m_type = tank;

    m_degats = DEGAT_TANK;
    m_vitesseAttaque = VITESSE_ATTAQUE_TANK;
    m_dps = m_degats / m_vitesseAttaque;
    m_vitesse = VITESSE_TANK;
    m_portee = PORTEE_TANK;
    m_cout.nbNourriture = COUT_NOURRITURRE_TANK;
    m_cout.nbOr = COUT_OR_TANK;
    m_cout.nbXp = XP_TANK;
    m_place = PLACE_TANK;
    m_tailleProjectile = 10;

    m_meshSceneNode = SceneManager::getSceneManager()->addMeshSceneNode(SceneManager::getSceneManager()->getMesh("mesh/troupe/tank.obj"));
    m_meshSceneNode->setScale(irr::core::vector3df(10,10,10));
    m_meshSceneNode->setMaterialTexture(0, m_texture);
    m_meshSceneNode->setPosition(irr::core::vector3df(-10000000,0,0)); //on ecarte pour le style
}

QString Tank::getInfo()
{
    QString texte = "";
    texte += "Le tank est un soldat possedants de nombreux points de vie.\n\n";
    texte += "degats par seconde : ";
    texte += QString::number(DEGAT_TANK / VITESSE_ATTAQUE_TANK);
    texte += "\nporte : ";
    texte += QString::number(PORTEE_TANK);
    texte += "\npoints de vie : ";
    texte += QString::number(PV_TANK);
    texte += "\nvitesse : ";
    texte += QString::number(VITESSE_TANK);
    texte += "\nnombre de places requises : ";
    texte += QString::number(PLACE_TANK);
    texte += "\n\n  -cout nourriture : ";
    texte += QString::number(COUT_NOURRITURRE_TANK);
    texte += "\n";
    texte += "  -cout or : ";
    texte += QString::number(COUT_OR_TANK);

    return texte;
}

