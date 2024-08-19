#ifndef CLIENTCHAT_H
#define CLIENTCHAT_H

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
#include "chatprotocol.h"
#include "chatwidget.h"
#define CHATPROTOCOL chatprotocol::getInstance()
namespace Ui {
class clientChat;
}

class clientChat : public QWidget
{
    Q_OBJECT

public:
    explicit clientChat(QTcpSocket *client,QWidget *parent = nullptr );

    ~clientChat();

private:
    Ui::clientChat *ui;
    QTcpSocket *m_client;
    chatprotocol m_protocol;
    QString clientName;

signals:
    void name(QString);
    void status(chatprotocol::Status);
    void textMessageReceive(QString,QString,QString);

public slots:
    void dataReceive();
    void clientDisconnected();
    void displayImage(QString);
private slots:
    void on_pushButton_clicked();
};

#endif // CLIENTCHAT_H
