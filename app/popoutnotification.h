#ifndef POPOUTNOTIFICATION_H
#define POPOUTNOTIFICATION_H

#include "ui_popoutnotification.h"

#include <QDialog>

namespace Ui {
class PopoutNotification;
}

class PopoutNotification : public QDialog
{
    Q_OBJECT

public:
    explicit PopoutNotification(QWidget *parent = nullptr);
    ~PopoutNotification();
    void hideButton() { ui->buttonBox->hide(); }
    void showButton() { ui->buttonBox->show(); }
    void updateMessage(QString mes) { ui->message->setText(mes); }

private:
    Ui::PopoutNotification *ui;
};

#endif // POPOUTNOTIFICATION_H
