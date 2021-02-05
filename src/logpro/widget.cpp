#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect( ui->btn_debug, &QPushButton::clicked, this, &Widget::sltBtnDebug );
    connect( ui->btn_info, &QPushButton::clicked, this, &Widget::sltBtnInfo );
    connect( ui->btn_warn, &QPushButton::clicked, this, &Widget::sltBtnWarn );
    connect( ui->btn_critical, &QPushButton::clicked, this, &Widget::sltBtnCritical );
    connect( ui->btn_fatal, &QPushButton::clicked, this, &Widget::sltBtnFatal );
}

Widget::~Widget()
{
    delete ui;
}

void Widget::sltBtnDebug()
{
    qDebug()<<"log test";
}

void Widget::sltBtnInfo()
{
    qInfo()<<"log test";
}

void Widget::sltBtnWarn()
{
    qWarning()<<"log test";
}

void Widget::sltBtnCritical()
{
    qCritical()<<"log test";
}

void Widget::sltBtnFatal()
{
    qFatal("log test");
}
