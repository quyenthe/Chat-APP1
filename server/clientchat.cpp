#include "clientchat.h"
#include "ui_clientchat.h"
clientChat::clientChat(QTcpSocket *client,QWidget *parent) :
    QWidget(parent),
    m_client(client),
    ui(new Ui::clientChat)

{
    ui->setupUi(this);
    connect(m_client,&QTcpSocket::readyRead,this,&clientChat::dataReceive);
    connect(m_client,QTcpSocket::disconnected,this,&clientChat::clientDisconnected);
}

clientChat::~clientChat()
{
    delete ui;
}
void clientChat::dataReceive()
{
    auto data=m_client->readAll();
    CHATPROTOCOL->loadData(data);

    if((CHATPROTOCOL)->getMessage()!=""){
        ui->listWidget->addItem(CHATPROTOCOL->getMessage());
    }
    //
    if(CHATPROTOCOL->getFileImage()!=""){

        displayImage(CHATPROTOCOL->getFileImage());
    }
    //
    switch(CHATPROTOCOL->type()){
    case chatprotocol::Text:
        emit name(CHATPROTOCOL->getName());
        break;
    case chatprotocol::SetStatus:
        emit status(CHATPROTOCOL->getclientStatus());
        break;
    case chatprotocol::ClientACK:
        clientName=CHATPROTOCOL->getClientACK();
        break;
    case chatprotocol::Message:
        emit textMessageReceive(CHATPROTOCOL->getMessage(),CHATPROTOCOL->getFileImage(),clientName);
        break;
    case chatprotocol::Image:
        emit textMessageReceive(CHATPROTOCOL->getMessage(),CHATPROTOCOL->getFileImage(),clientName);
        break;
    }
    CHATPROTOCOL->setData();
}
void clientChat::displayImage(QString fileName){
    auto chatwgt=new chatwidget();
    QImage image(fileName);
    chatwgt->setImage(image);
    auto listWidget=new QListWidgetItem();
    listWidget->setSizeHint(QSize(0,150));
    ui->listWidget->addItem(listWidget);
    ui->listWidget->setItemWidget(listWidget,chatwgt);
}
void clientChat::on_pushButton_clicked()
{
    m_client->write(chatprotocol::getInstance()->setMessage(ui->lineEdit->text()));
    ui->lineEdit->setText("");
}
void clientChat::clientDisconnected(){
}

