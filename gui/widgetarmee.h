#ifndef WIDGETARMEE_H
#define WIDGETARMEE_H

#include <QFrame>

namespace Ui {
class widgetArmee;
}

class widgetArmee : public QFrame
{
    Q_OBJECT

public:
    explicit widgetArmee(QWidget *parent = 0);
    ~widgetArmee();

public slots:
    void afficherMenuArmee();
    void cacherMenuArmee();

private:
    Ui::widgetArmee *ui;

signals:
    void affichage();
    void cachage();
};

#endif // WIDGETARMEE_H
