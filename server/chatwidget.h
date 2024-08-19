#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include "chatprotocol.h"
namespace Ui {
class chatwidget;
}

class chatwidget : public QWidget
{
    Q_OBJECT

public:
    explicit chatwidget(QWidget *parent = nullptr);
    ~chatwidget();
    void setImage(QImage);


private:
    Ui::chatwidget *ui;

};

#endif // CHATWIDGET_H
