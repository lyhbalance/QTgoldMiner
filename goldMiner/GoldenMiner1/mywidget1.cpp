#include "GoldenMiner1/mywidget1.h"
#include "ui_mywidget.h"
#include "data.h"
#include <QTimer>
#include "secondleveln.h"
#include"widget.h"

myWidget1::myWidget1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myWidget1)
{

    Bought=false;
    ui->setupUi(this);
    ui->boss2->hide();
    ui->gold1->hide();
    ui->gold2->hide();
    ui->bomb_3->hide();
    ui->luckdog_3->hide();
    ui->stonebook_3->hide();
    ui->strongdrug_3->hide();
    ui->threeleaves_3->hide();
    useall();
}

myWidget1::~myWidget1()
{
    delete ui;
}

//boss切换效果
void myWidget1::on_pushButton_clicked()
{
    if(Bought==false) {
        ui->boss->hide();
        ui->boss2->show();
    }
}


//物件对应的槽函数 即对应产生的效果
void myWidget1::on_bomb_clicked(bool checked)
{
//    Bomb+=1;
    Bought=true;
    data::money-=bomb_price_appear();
    data::bombNumber+=1;
    ui->bomb->hide();
    ui->bomb_2->hide();
    ui->bomb_3->hide();
}

void myWidget1::on_strongdrug_clicked(bool checked)
{
//     Strongdrug+=200;
    Bought=true;
    data::money-=strongdrug_price_appear();
    data::strength=1.5;
    ui->strongdrug->hide();
    ui->strongdrug_2->hide();
    ui->strongdrug_3->hide();
}

void myWidget1::on_threeleaves_clicked(bool checked)
{
//   Threeleaves+=200;
    Bought=true;
    data::money-=threeleaves_price_appear();
    data::IfThreeleaves=true;
    ui->threeleaves->hide();
    ui->threeleaves_2->hide();
    ui->threeleaves_3->hide();
}

void myWidget1::on_stonebook_clicked(bool checked)
{
//     Stonebook+=100;
    Bought=true;
    data::money-=stonebook_price_appear();
    data::stoneBookMoney=20;
    ui->stonebook->hide();
    ui->stonebook_2->hide();
    ui->stonebook_3->hide();
}

void myWidget1::on_luckdog_clicked(bool checked)
{
//     Luckdog+=100;
    Bought=true;
    data::money-=luckdog_price_appear();
    data::diamondAddMoney+=200;
    ui->luckdog->hide();
    ui->luckdog_2->hide();
    ui->luckdog_3->hide();
}


//以下是各种物品出现的价格和几率
int myWidget1::luckdog_price_appear(){
    qsrand(time(NULL));
    int n = qrand() % 4;
    int price=0;
    if(n==1) {
        ui->luckdog->show();
        price=qrand()%450;
        QString finnal="$"+QString::number(price);
        ui->luckdog_2->setText(finnal);
        ui->luckdog_3->show();
    }
    else ui->luckdog->hide();
    return price;
}

int myWidget1::bomb_price_appear(){
    qsrand(time(NULL));
    int n = qrand() % 4;
    int price=0;
    if(n!=1) {
        ui->bomb->show();
        price=qrand()%200;
        QString finnal="$"+QString::number(price);
        ui->bomb_2->setText(finnal);
        ui->bomb_3->show();
    }
    else ui->bomb->hide();
    return price;
}

int myWidget1::threeleaves_price_appear(){
    qsrand(time(NULL));
    int n = qrand() % 3;
    int price=0;
    if(n==1) {
        ui->threeleaves->show();
        price=qrand()%200;
        QString finnal="$"+QString::number(price);
        ui->threeleaves_2->setText(finnal);
        ui->threeleaves_3->show();
    }
    else ui->threeleaves->hide();
    return price;
}

int myWidget1::strongdrug_price_appear(){
    qsrand(time(NULL));
    int n = qrand() % 5;
    int price=0;
    if(n==1) {
        ui->strongdrug->show();
        price=qrand()%350;
        QString finnal="$"+QString::number(price);
        ui->strongdrug_2->setText(finnal);
        ui->strongdrug_3->show();
    }
    else ui->strongdrug->hide();
    return price;
}

int myWidget1::stonebook_price_appear(){
    qsrand(time(NULL));
    int n = qrand() % 4;
    int price=0;
    if(n==1) {
        ui->stonebook->show();
        price=qrand()%300;
        QString finnal="$"+QString::number(price);
        ui->stonebook_2->setText(finnal);
        ui->stonebook_3->show();
    }
    else ui->stonebook->hide();
    return price;
}

//调用各个物件的函数 为了让构造函数更好看一点
void myWidget1::useall(){
    luckdog_price_appear();
    bomb_price_appear();
    threeleaves_price_appear();
    strongdrug_price_appear();
    stonebook_price_appear();
}

//购买完后 下一关按键触发效果
void myWidget1::on_next_clicked(bool checked)
{
    ui->bomb->hide();
    ui->luckdog->hide();
    ui->stonebook->hide();
    ui->strongdrug->hide();
    ui->threeleaves->hide();
    ui->bomb_2->hide();
    ui->luckdog_2->hide();
    ui->stonebook_2->hide();
    ui->strongdrug_2->hide();
    ui->threeleaves_2->hide();
    ui->bomb_3->hide();
    ui->luckdog_3->hide();
    ui->stonebook_3->hide();
    ui->strongdrug_3->hide();
    ui->threeleaves_3->hide();
    ui->words->hide();
    if(Bought==false) {
        ui->boss->hide();
        ui->boss2->show();
    }
    else{
        ui->gold1->show();
        ui->gold2->show();
        QPropertyAnimation *pPosAnimation1 = new QPropertyAnimation(ui->gold1, "pos");
            pPosAnimation1->setDuration(1500);
            pPosAnimation1->setKeyValueAt(0,QPoint(90, 360));
            pPosAnimation1->setKeyValueAt(0.3,QPoint(270, 380));
            pPosAnimation1->setKeyValueAt(0.7,QPoint(270, 450));
            pPosAnimation1->setKeyValueAt(0.9,QPoint(360, 500));
            pPosAnimation1->setKeyValueAt(1,QPoint(360, 530));
            pPosAnimation1->setEasingCurve(QEasingCurve::OutBounce);

            QPropertyAnimation *pPosAnimation2 = new QPropertyAnimation(ui->gold2, "pos");
            pPosAnimation2->setDuration(1500);
            pPosAnimation2->setKeyValueAt(0,QPoint(50, 360));
            pPosAnimation2->setKeyValueAt(0.3,QPoint(230, 380));
            pPosAnimation2->setKeyValueAt(0.7,QPoint(230, 450));
            pPosAnimation2->setKeyValueAt(0.9,QPoint(320, 500));
            pPosAnimation2->setKeyValueAt(1,QPoint(320, 530));
            pPosAnimation2->setEasingCurve(QEasingCurve::OutBounce);

            pPosAnimation1->start();
            pPosAnimation2->start();
    }
    QTimer::singleShot(2000,this,&myWidget1::close);
    //data::clearall();
    if(data::gameNumber==2){
        secondLeveln *w=new secondLeveln;
        QTimer::singleShot(1900,w,&QWidget::show);
        data::gameNumber+=1;
    }
    else if(data::gameNumber==3){
        widget *w=new widget;
        QTimer::singleShot(1900,w,&QWidget::show);
    }
}
