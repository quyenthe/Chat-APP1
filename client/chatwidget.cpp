#include "chatwidget.h"
#include "ui_chatwidget.h"

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidget)
{
    ui->setupUi(this);
}

ChatWidget::~ChatWidget()
{
    delete ui;
}
void ChatWidget::setMessage(QString message){

    ui->label_3->hide();
    ui->label_4->hide();
    ui->label->setText(message);
    ui->label_2->setText(QDateTime::currentDateTime().toString("HH:mm"));
}
void ChatWidget::setMessage1(QString message){

    ui->label_3->hide();
    ui->label_4->hide();
    ui->label->setAlignment(Qt::AlignRight);
    ui->label->setText(message);
    ui->label_2->setText(QDateTime::currentDateTime().toString("HH:mm"));
}
void ChatWidget::setImage(QImage image){

    ui->label->hide();
    ui->label_2->hide();
    QPixmap pixmap = QPixmap::fromImage(image);
    ui->label_3->setAlignment(Qt::AlignCenter);
    // Điều chỉnh kích thước hình ảnh để vừa với QLabel, giữ nguyên tỷ lệ
    pixmap = pixmap.scaled(ui->label_3->size(), Qt::KeepAspectRatio);

    // Đặt QPixmap lên QLabel
    ui->label_3->setPixmap(pixmap);
    ui->label_4->setText(QDateTime::currentDateTime().toString("HH:mm"));
}
