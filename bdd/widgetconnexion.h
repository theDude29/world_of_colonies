#ifndef WIDGETCONNEXION_H
#define WIDGETCONNEXION_H

#include <QWidget>

namespace Ui {
class WidgetConnexion;
}

class WidgetConnexion : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetConnexion(QWidget *parent = 0);
    ~WidgetConnexion();

    QString getPseudo();

    void retenirNomUtilisateur(QString pseudo, bool vraiment);

public slots:
    bool connexion();

private:
    Ui::WidgetConnexion *ui;

    QString m_pseudo;

signals:
    void connecte();
};

#endif // WIDGETCONNEXION_H
