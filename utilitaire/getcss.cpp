#include "utilitaire/getcss.h"
#include <QFile>
#include <iostream>
const QString getCSS(const QString chemin)
{
    QFile file(chemin);
    QString texte = "";

    if(file.open(QIODevice::ReadOnly))
    {
        texte = file.readAll();
        file.close();
    }

    else
    {
        std::cout<<"le fichier "<<chemin.toStdString()<<"n'a pas pu etre ouvert"<<std::endl;
    }

    return texte;
}
