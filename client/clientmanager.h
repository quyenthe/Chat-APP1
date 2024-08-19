#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include "chatprotocol.h"
class clientManager : public QObject
{
    Q_OBJECT
public:
    explicit clientManager(QHostAddress ip=QHostAddress::LocalHost,int port=4500, QObject *parent = nullptr);
    void sendMessage(QString);
    void sendName(QString);
    void sendStatus(Chatprotocol::Status);
    void connectToServer();
    void sendClientACK(QString);
    void sendImage(QString);

signals:
    void connected();
    void disconnected();
    void messageReceive(QString);
    void textReceive(QString);
    void imageReceive(QString);
    void newclientName(QVector<QString>);
public slots:
    void readyRead();

private:
    QTcpSocket *m_socket;
    QHostAddress m_ip;
    int port;
    Chatprotocol m_protocol;

};

#endif // CLIENTMANAGER_H
