#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clientmanager.h"
#include "chatwidget.h"
#include <QVector>
#include "chatprotocol.h"
#include <QFileDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_actionconnect_triggered();
    void messageReceive(QString);
    void textReceive(QString);
    void newclientName(QVector<QString>);

    void on_pushButton_clicked();
    void on_lineEdit_2_editingFinished();

    void on_comboBox_currentIndexChanged(int index);

    void imageReceive(QString);

    void on_lineEdit_editingFinished();

    void on_pushButton_2_clicked();

public slots:

private:
    Ui::MainWindow *ui;
    clientManager *client;
    QVector<QString> listName;
    QTcpSocket *m_socket;
    QString m_onclientACK;
    Chatprotocol m_protocol;
    QImage m_image;
    QString fileName;
};
#endif // MAINWINDOW_H
