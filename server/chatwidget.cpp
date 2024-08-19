#include "chatwidget.h"
#include "ui_chatwidget.h"

chatwidget::chatwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chatwidget)
{
    ui->setupUi(this);
}

chatwidget::~chatwidget()
{
    delete ui;
}
void chatwidget::setImage(QImage image){

    QPixmap pixmap =QPixmap::fromImage(image);
    ui->label->setAlignment(Qt::AlignLeft);
    // Điều chỉnh kích thước hình ảnh để vừa với QLabel, giữ nguyên tỷ lệ
    pixmap = pixmap.scaled(ui->label->size(), Qt::KeepAspectRatio);

    // Đặt QPixmap lên QLabel
    ui->label->setPixmap(pixmap);

}
