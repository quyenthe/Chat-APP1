#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QDateTime>
namespace Ui {
class ChatWidget;
}

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWidget(QWidget *parent = nullptr);
    ~ChatWidget();
    void setMessage(QString message);
    void setMessage1(QString message);
    void setImage(QImage);
private:
    Ui::ChatWidget *ui;
};

#endif // CHATWIDGET_H
