#ifndef CHATPROTOCOL_H
#define CHATPROTOCOL_H

#include <QObject>
#include <QIODevice>
class Chatprotocol
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
    explicit Chatprotocol();
    QByteArray setNameMessage(QString);
    QByteArray setMessage(QString);
    QByteArray setStatus(Status);
    QByteArray setClient(QString);
    QByteArray setClientACK(QString);
    void loadData(QByteArray);
    QString getName();
    QString getMessage();
    QVector<QString> getClientName();
    QByteArray setImage(QString);
    MessageType type();
    QString getFileNameImage(){
        return m_fileNameImage;
    }
signals:



private:
    QByteArray getData(MessageType ,QString);
    QByteArray getStatus(Status);
    QByteArray getImage(QString);
    MessageType m_type;
    Status m_status;
    QString m_name;
    QString m_messgage;
    QString m_fileNameImage;
    QVector<QString> m_clientName;
};

#endif // CHATPROTOCOL_H
