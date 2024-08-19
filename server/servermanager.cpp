#include "servermanager.h"
#include "chatprotocol.h"
ServerManager::ServerManager(int port,QObject *parent)
    : QObject{parent}
{
    setupServer(port);
}
void ServerManager::setupServer(int port){
    m_server=new QTcpServer();
    connect(m_server,&QTcpServer::newConnection,this,&ServerManager::newClientConnectionReceived);
    m_server->listen(QHostAddress::Any,port);

}
void ServerManager::newClientConnectionReceived(){
    auto client=m_server->nextPendingConnection();
    m_client<<client;
    auto id=m_client.length();
    client->setProperty("id",id);
    connect(client,&QTcpSocket::disconnected,this,&ServerManager::onClientDisConnected);
    auto clientName=QString("client %1").arg(id);
    emit newClientConnected(client,clientName);

    m_listclientName.push_back(clientName);
    m_listclient.insert(clientName,client);
    for(int i=0;i<m_client.size();i++){
        m_listclientName.remove(i);
        m_client[i]->write(chatprotocol::getInstance()->setClientName(m_listclientName));
        m_listclientName.insert(i,QString("client %1").arg(i+1));
    }
}

void ServerManager::onClientDisConnected(){
    auto client=(QTcpSocket *)sender();
    emit clientDisconnected(client);
}
