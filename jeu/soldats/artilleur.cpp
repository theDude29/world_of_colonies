#include "artilleur.h"

Artilleur::Artilleur()
{
    m_degats = DEGAT_ARTILLEUR;
    m_vitesseAttaque = VITESSE_ATTAQUE_ARTILLEUR;
    m_dps = m_degats / m_vitesseAttaque;
    m_pointsVies = PV_ARTILLEUR;
    m_vitesse = VITESSE_ARTILLEUR;
    m_portee = PORTEE_ARTILLEUR;
    m_cout.nbNourriture = COUT_NOURRITURRE_ARTILLEUR;
    m_cout.nbOr = COUT_OR_ARTILLEUR;
    m_cout.nbXp = XP_ARTILLEUR;
    m_place = PLACE_ARTILLEUR;
}

QString Artilleur::getInfo()
{
    QString texte = "";
    texte += "L'artilleur est un soldat infligeant des gros degats et possedants une grande portee.\n\n";
    texte += "degats par seconde : ";
    texte += QString::number(m_dps);
    texte += "\nporte : ";
    texte += QString::number(m_portee);
    texte += "\npoints de vie : ";
    texte += QString::number(m_pointsVies);
    texte += "\nvitesse : ";
    texte += QString::number(m_vitesse);
    texte += "\n\n  -cout nourriture : ";
    texte += QString::number(m_cout.nbNourriture);
    texte += "\n";
    texte += "  -cout or : ";
    texte += QString::number(m_cout.nbOr);

    return texte;
}

