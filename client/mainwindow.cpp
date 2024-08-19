#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    m_socket=new QTcpSocket();
    ui->setupUi(this);
    ui->centralwidget->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_actionconnect_triggered()
{
    client=new clientManager();
    connect(client,&clientManager::connected,[this]{
        ui->centralwidget->setEnabled(true);
    });

    connect(client,&clientManager::disconnected,[this]{
        ui->centralwidget->setEnabled(false);
    });
    connect(client,&clientManager::messageReceive,this,&MainWindow::messageReceive);
    connect(client,&clientManager::textReceive,this,&MainWindow::textReceive);
    connect(client,&clientManager::newclientName,this,&MainWindow::newclientName);
    connect(client,&clientManager::imageReceive,this,&MainWindow::imageReceive);
    client->connectToServer();

}
void MainWindow::messageReceive(QString message){
    if(message!=""){
        auto chatwidget=new ChatWidget();
        chatwidget->setMessage(message);
        auto listWidget=new QListWidgetItem();
        listWidget->setSizeHint(QSize(0,65));
        ui->listWidget->addItem(listWidget);
        listWidget->setBackground(QColor(100,255,100));
        ui->listWidget->setItemWidget(listWidget,chatwidget);
    }
}
void MainWindow::imageReceive(QString fileNameImage){

    qDebug()<<fileNameImage;
    if(fileNameImage!=""){
        QImage image(fileName);
        auto chatwidget=new ChatWidget();
        chatwidget->setImage(image);
        auto listWidget=new QListWidgetItem();
        listWidget->setSizeHint(QSize(0,150));
        ui->listWidget->addItem(listWidget);
        ui->listWidget->setItemWidget(listWidget,chatwidget);
    }

}
void MainWindow::on_pushButton_clicked()
{
    auto message=ui->lineEdit->text().trimmed();
    client->sendMessage(message);
    auto chatwidget=new ChatWidget();
    chatwidget->setMessage1(message);
    auto listWidget=new QListWidgetItem();
    listWidget->setSizeHint(QSize(0,65));
    ui->listWidget->addItem(listWidget);
    listWidget->setBackground(QColor(167,255,137));
    ui->listWidget->setItemWidget(listWidget,chatwidget);
    ui->lineEdit->setText("");

}
void MainWindow::on_lineEdit_2_editingFinished()
{
    auto name=ui->lineEdit_2->text().trimmed();
    client->sendName(name);

}
void MainWindow::textReceive(QString name){

}
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    auto status=(Chatprotocol::Status)index;
    client->sendStatus(status);
}
void MainWindow::newclientName(QVector<QString> clientName){
    ui->comboBox_2->clear();
    ui->comboBox_2->addItem("All");
    for(int i=0;i<clientName.size();i++){
        ui->comboBox_2->addItem(clientName[i]);
    }
}
void MainWindow::on_lineEdit_editingFinished()
{
    m_onclientACK=ui->comboBox_2->currentText();
    client->sendClientACK(m_onclientACK);
}

void MainWindow::on_pushButton_2_clicked()
{

    fileName=QFileDialog::getOpenFileName(this,tr("abc")," ",tr("image file(*.png *.jpg *.bmp)"));
    if(!fileName.isEmpty()){
        QImage image(fileName);
        auto chatwidget=new ChatWidget();
        chatwidget->setImage(image);
        auto listWidget=new QListWidgetItem();
        listWidget->setSizeHint(QSize(0,150));
        ui->listWidget->addItem(listWidget);
        ui->listWidget->setItemWidget(listWidget,chatwidget);
        client->sendImage(fileName);
    }
}

