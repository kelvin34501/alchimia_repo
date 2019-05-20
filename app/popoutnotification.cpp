#include "popoutnotification.h"
#include "ui_popoutnotification.h"

PopoutNotification::PopoutNotification(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PopoutNotification)
{
    ui->setupUi(this);
}

PopoutNotification::~PopoutNotification()
{
    delete ui;
}
