#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "servermanager.h"
#include <QString>
#include "clientchat.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void getName(QString);
    void getListName();
    void setClientStatus(chatprotocol::Status);
    void sendNameClientChange();
private:
    Ui::MainWindow *ui;
    ServerManager *m_server;
    chatprotocol m_protocol;
    QString name;
    QVector<QString> listNameClient;
    QVector<QTcpSocket*> listClientSocket;
    QMap<QString,QTcpSocket*> mapClientSocket;
    void setupServer();

private slots:
    void newClientConnected(QTcpSocket*,QString);
    void clientDisconnected(QTcpSocket*);
    void onTextForOtherClients(QString,QString,QString);
};
#endif // MAINWINDOW_H
