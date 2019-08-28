#ifndef WIDGETOPTIONSBATIMENTS_H
#define WIDGETOPTIONSBATIMENTS_H

#include <QFrame>
#include <QPushButton>

namespace Ui {
class WidgetOptionsBatiments;
}

class WidgetOptionsBatiments : public QFrame
{
    Q_OBJECT

public:
    explicit WidgetOptionsBatiments(QWidget *parent = 0);
    ~WidgetOptionsBatiments();

    QPushButton* getBoutonDeplacer();
    QPushButton* getBoutonVendre();
    QPushButton* getBoutonDroite();
    QPushButton* getBoutonGauche();
    QPushButton* getBoutonRetour();

private:
    Ui::WidgetOptionsBatiments *ui;

public slots:
    void afficherBoutonsPivoter();
    void cacherBoutonsPivoter();
};

#endif // WIDGETOPTIONSBATIMENTS_H
