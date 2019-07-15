#include "beginmainwindow.h"
#include "ui_beginmainwindow.h"
#include"firstlevel.h"
#include<QTimer>

beginMainWindow::beginMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::beginMainWindow)
{
    ui->setupUi(this);
}

beginMainWindow::~beginMainWindow()
{
    delete ui;
}

void beginMainWindow::on_btnBegin_clicked()
{
    this->close();
    firstLevel *firLevel=new firstLevel;
    firLevel->show();
    //QTimer::singleShot(3000,firLevel,&firstLevel::changeimage);

}
