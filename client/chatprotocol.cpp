#include "chatprotocol.h"
#include <QDebug>
Chatprotocol::Chatprotocol()
{

}
void Chatprotocol::loadData(QByteArray data){
    QDataStream in(&data,QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_6_0);
    in>>m_type;
    switch(m_type){
    case Message:
        in>>m_messgage;
        break;
    case Text:
        in>>m_name;
        break;
    case SetStatus:
        in>>m_status;
        break;
    case NewClient:
        in>>m_clientName;
        break;
    case Image:
        in>>m_fileNameImage;
        break;
    }

}
QByteArray Chatprotocol::setNameMessage(QString name){
    return getData(Text,name);
}
QByteArray Chatprotocol::setMessage(QString message){
    return getData(Message,message);
}
QByteArray Chatprotocol::setStatus(Status status){
    return getStatus(status);
}
QByteArray Chatprotocol::getData(MessageType type, QString data){
    QByteArray ba;
    QDataStream out(&ba,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out<<type<<data;
    return ba;
}
QByteArray Chatprotocol::getStatus(Status status){
    QByteArray ba;
    QDataStream out(&ba,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out<<SetStatus<<status;
    return ba;
}
QByteArray Chatprotocol::setClient(QString clientName){
    QByteArray ba;
    QDataStream out(&ba,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out<<NewClient<<clientName;
    return ba;
}
QByteArray Chatprotocol::setClientACK(QString clientNameACK){
    QByteArray ba;
    QDataStream out(&ba,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out<<ClientACK<<clientNameACK;
    return ba;
}
QByteArray Chatprotocol::getImage( QString fileImage){
    QByteArray ba;
    QDataStream out(&ba,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out<<Image<<fileImage;
    return ba;
}
QByteArray Chatprotocol::setImage(QString fileImage){
    return getImage(fileImage);
}
QString Chatprotocol::getMessage(){
    return m_messgage;
}
QString Chatprotocol::getName(){
    return m_name;
}
Chatprotocol::MessageType Chatprotocol::type(){
    return m_type;
}
QVector<QString> Chatprotocol::getClientName(){
    return m_clientName;
}
