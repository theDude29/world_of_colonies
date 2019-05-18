#include "widgetconnexion.h"
#include "ui_widgetconnexion.h"

WidgetConnexion::WidgetConnexion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetConnexion)
{
    ui->setupUi(this);
}

WidgetConnexion::~WidgetConnexion()
{
    delete ui;
}
