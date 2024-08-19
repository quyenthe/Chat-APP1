#include "clientmanager.h"

clientManager::clientManager(QHostAddress ip,int  port,  QObject *parent)
    : QObject{parent},
    m_ip(ip),
    port(port)
{
    m_socket= new QTcpSocket();
    connect(m_socket,& QTcpSocket::connected,this,&clientManager::connected);
    connect(m_socket,& QTcpSocket::disconnected,this,&clientManager::disconnected);
    connect(m_socket,& QTcpSocket::readyRead,this,&clientManager::readyRead);

}
void clientManager::readyRead(){
    auto data=m_socket->readAll();
    m_protocol.loadData(data);
    switch(m_protocol.type()){
    case Chatprotocol::Message:
        emit messageReceive(m_protocol.getMessage());
        break;
    case Chatprotocol::Text:
        emit textReceive(m_protocol.getName());
        break;
    case Chatprotocol::NewClient:
        emit newclientName(m_protocol.getClientName());
        break;
    case Chatprotocol::Image:
        emit imageReceive(m_protocol.getFileNameImage());
        break;
    }
}
void clientManager::connectToServer(){
    m_socket->connectToHost(m_ip,port);
}
void clientManager::sendMessage(QString message){
    m_socket->write(m_protocol.setMessage(message));
}
void clientManager::sendName(QString name){
    m_socket->write(m_protocol.setNameMessage(name));
}
void clientManager::sendStatus(Chatprotocol::Status status){
    m_socket->write(m_protocol.setStatus(status));
}
void clientManager::sendClientACK(QString clientName){
    m_socket->write(m_protocol.setClientACK(clientName));
}
void clientManager::sendImage(QString fileImage){
    m_socket->write(m_protocol.setImage(fileImage));
}
