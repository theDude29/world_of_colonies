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

private:
    Ui::WidgetConnexion *ui;
};

#endif // WIDGETCONNEXION_H
