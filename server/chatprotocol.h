#ifndef CHATPROTOCOL_H
#define CHATPROTOCOL_H

#include <QObject>
#include <QIODevice>
class chatprotocol
{
public:

    enum MessageType{
        Text,
        Message,
        SetStatus,
        NewClient,
        ClientACK,
        Image
    };
    enum Status{
        None,
        Available,
        Away,
        Busy
    };

    void loadData(QByteArray);
    QByteArray getData(MessageType,QString);
    QByteArray getStatus(Status status);
    QByteArray setMessage(QString);
    QByteArray setText(QString);
    QByteArray getClientName(QVector<QString>);
    QByteArray setClientName(QVector<QString>);
    QString getName(){
        return m_text;
    }
    QString getMessage(){
        return m_message;
    }
    Status getclientStatus(){
        return m_status;
    }
    QString getnewClient(){
        return m_clientName;
    }
    QString getClientACK(){
        return m_clientACK;
    }
    QString getFileImage(){
        return m_fileImage;
    }
    void setData(){
        m_fileImage="";
        m_message="";
    }
    MessageType type(){
        return m_type;
    }
    static chatprotocol *getInstance();

private:

    static chatprotocol *instance;
    MessageType m_type;
    Status m_status;
    QString m_message;
    QString m_text;
    QString m_clientName;
    QString m_clientACK;
    QString m_fileImage;
};

#endif // CHATPROTOCOL_H
