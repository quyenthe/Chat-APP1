#include "chatprotocol.h"
chatprotocol* chatprotocol::instance=NULL;
chatprotocol* chatprotocol::getInstance(){
    if(instance==NULL){
        instance=new chatprotocol();
        return instance;
    }
    return instance;
}
QByteArray chatprotocol::getData(MessageType type, QString data){
    QByteArray ba;
    QDataStream out(&ba,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out<<type<<data;
    return ba;
}
QByteArray chatprotocol::getStatus(Status status){
    QByteArray ba;
    QDataStream out(&ba,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out<<SetStatus<<status;
    return ba;
}
QByteArray chatprotocol::getClientName(QVector<QString> clientName){
    QByteArray ba;
    QDataStream out(&ba,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out<<NewClient<<clientName;
    return ba;
}
QByteArray chatprotocol::setMessage(QString message){
    return getData(Message,message);
}
QByteArray chatprotocol::setText(QString text){
    return getData(Text,text);
}
QByteArray chatprotocol::setClientName(QVector<QString> clientName){
    return getClientName(clientName);
}
void chatprotocol::loadData(QByteArray data){
    QDataStream in(&data,QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_6_0);
    in>>m_type;
    switch(m_type){
    case Text:
        in>>m_text;
        break;
    case Message:
        in>>m_message;
        break;
    case SetStatus:
        in>>m_status;
        break;
    case NewClient:
        in>>m_clientName;
        break;
    case ClientACK:
        in>>m_clientACK;
        break;
    case Image:
        in>>m_fileImage;
        break;
    }
}
