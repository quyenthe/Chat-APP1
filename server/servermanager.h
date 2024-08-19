#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
class ServerManager : public QObject
{
    Q_OBJECT
public:
    explicit ServerManager(int port=4500,QObject *parent = nullptr);
    void setupServer(int port);

public slots:

signals:
    void newClientConnected(QTcpSocket *,QString);
    void clientDisconnected(QTcpSocket *);

private slots:
    void newClientConnectionReceived();
    void onClientDisConnected();

private:
    QTcpServer *m_server;
    QList <QTcpSocket*> m_client;
    QVector<QString> m_listclientName;
    QMap<QString,QTcpSocket*> m_listclient;
    QString current;
};

#endif // SERVERMANAGER_H
