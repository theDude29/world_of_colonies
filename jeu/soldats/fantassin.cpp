#include "fantassin.h"

Fantassin::Fantassin()
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
}

QString Fantassin::getInfo()
{
    QString texte = "";
    texte += "Le fantassin est un soldat polyvalant ayant une bonne sante et de bon degat mais une faible portee.\n\n";
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
