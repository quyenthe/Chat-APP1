#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupServer();

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setupServer(){
    m_server=new ServerManager();
    connect(m_server,&ServerManager::newClientConnected,this,&MainWindow::newClientConnected);
    connect(m_server,&ServerManager::clientDisconnected,this,&MainWindow::clientDisconnected);

}
void MainWindow::newClientConnected(QTcpSocket * client,QString clientName){
    auto id=client->property("id").toInt();
    ui->listWidget->addItem(QString("new client: %1").arg(id));
    auto chat=new clientChat(client);
    ui->tabWidget->addTab(chat,QString("client %1").arg(id));
    listClientSocket.push_back(client);
    listNameClient.push_back(clientName);
    mapClientSocket.insert(QString("client %1").arg(id),client);
    sendNameClientChange();
    connect(chat,&clientChat::name,this,&MainWindow::getName);
    connect(chat,&clientChat::status,this,&MainWindow::setClientStatus);
    connect(chat,&clientChat::textMessageReceive,this,&MainWindow::onTextForOtherClients);
}
void MainWindow::clientDisconnected(QTcpSocket *client){
    auto id=client->property("id").toInt();
    ui->listWidget->addItem(QString("client disconnected id : %1").arg(id));
    int currentIndex=ui->tabWidget->currentIndex();
    ui->tabWidget->removeTab(currentIndex);
    for(auto i=mapClientSocket.begin();i!=mapClientSocket.end();i++){
        if(mapClientSocket[i.key()]==client){
            mapClientSocket.remove(i.key());
            listNameClient.removeOne(i.key());
            break;
        }
    }
    listClientSocket.removeOne(client);
    sendNameClientChange();
}
void MainWindow::onTextForOtherClients(QString message,QString fileNameImage, QString receiver){
    if(message!=""){
        auto msg=chatprotocol::getInstance()->getData(chatprotocol::Message,message);
        if(receiver=="All"){
            for(auto i=mapClientSocket.begin();i!=mapClientSocket.end();i++){
                mapClientSocket[i.key()]->write(msg);
            }

            return;
        }
        mapClientSocket[receiver]->write(msg);

    }
    if(fileNameImage!=""){

        qDebug()<<fileNameImage<<receiver;
        auto msg=chatprotocol::getInstance()->getData(chatprotocol::Image,fileNameImage);
        if(receiver=="All"){
            for(auto i=mapClientSocket.begin();i!=mapClientSocket.end();i++){
                mapClientSocket[i.key()]->write(msg);
            }

            return;
        }
        mapClientSocket[receiver]->write(msg);
    }
}
void MainWindow::getName(QString name){
    auto widget = qobject_cast<QWidget *>(sender());
    auto index = ui->tabWidget->indexOf(widget);
    auto nameclient=ui->tabWidget->tabText(index);
    ui->tabWidget->setTabText(index,name);
    QTcpSocket *client=mapClientSocket.value(nameclient);
    mapClientSocket.remove(nameclient);
    mapClientSocket.insert(name,client);
    //
    getListName();
    sendNameClientChange();
}
void MainWindow::getListName(){

    for(int i=0;i<ui->tabWidget->count();i++){
        listNameClient[i]=ui->tabWidget->tabText(i);
    }
}
void MainWindow::sendNameClientChange(){
    for(int i=0;i<ui->tabWidget->count();i++){
        for(auto j=mapClientSocket.begin();j!=mapClientSocket.end();j++){
            if(listClientSocket[i]==mapClientSocket[j.key()]){
                listNameClient.removeOne(j.key());
                listClientSocket[i]->write(chatprotocol::getInstance()->getClientName(listNameClient));
                listNameClient.push_back(j.key());
                break;
            }
        }
    }
}
void MainWindow::setClientStatus(chatprotocol::Status status){
    auto widget=qobject_cast<QWidget*>(sender());
    auto index=ui->tabWidget->indexOf(widget);
    QString iconName;
    switch(status){
    case chatprotocol::Available:
        iconName=":/icons/available.png";
        break;
    case chatprotocol::Busy:
        iconName=":/icons/busy.png";
        break;
    case chatprotocol::Away:
        iconName=":/icons/away.png";
        break;
    case chatprotocol::None:
        iconName=":/icons/none.png";
        break;
    }
    auto icon = QIcon(iconName);
    ui->tabWidget->setTabIcon(index, icon);
}
