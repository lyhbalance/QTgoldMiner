#include "mywidget.h"
#include <QPainter>
#include <QTimer>
#include<cmath>
#include<QLabel>
#include"data.h"

const double pi=3.1415926;
myWidget::myWidget(QWidget *parent) :
    QWidget(parent)
{
    hook_pCiecleTimer=Q_NULLPTR;
    hook_Time=0;
    hook_bCircle=false;
    hook_nAngle=0;
    Clockwise=true;
    keypressed=false;
    hook_bg=QImage(":/hook/photo/hook.png");

    index=0;
    speed=1.4;

    blankHook=false;
    catched=0;
    catchedPageup=false;

    goldCatched=0;

    goldCatched2=0;
    smallGoldCatched1=0;
    smallGoldCatched2=0;
    smallGoldCatched3=0;
    smallGoldCatched4=0;
    stoneCatched1=0;
    stoneCatched2=0;
    stoneCatched3=0;
    stoneCatched4=0;
    stoneCatched5=0;
    stoneCatched6=0;
    stoneCatched7=0;
    boneCatched1=0;
    boneCatched2=0;
    pigCatched1=0;
    pigCatched2=0;
    pigWithDiamondCatched1=0;
    diamondCatched1=0;
    diamondCatched2=0;
    luckBagcatched1=0;
    luckBagcatched2=0;

    hook_pCiecleTimer=new QTimer(this);
    hook_pCiecleTimer->setInterval(18);
    startRotate();
    connect(hook_pCiecleTimer,&QTimer::timeout,this,&myWidget::onTimeout);
}

void myWidget::startRotate(){
    hook_pCiecleTimer->start();
    hook_bCircle=true;
}

void myWidget::paintEvent(QPaintEvent *ev){
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::NoBrush);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    if(hook_bCircle){
        painter.translate(this->width()/2,0);
        painter.rotate(hook_nAngle);
        painter.translate(-(this->width()/2),0);
    }
    painter.drawImage(51,0,hook_bg);

    QWidget::paintEvent(ev);
}

void myWidget::onTimeout(){
    ++hook_Time;
    if(keypressed==false){
    if(hook_nAngle<75 && Clockwise==true){
        hook_nAngle+=1;
        if(hook_nAngle==70)
            Clockwise=false;
    }
    else if(hook_nAngle>-75 && Clockwise==false){
        hook_nAngle-=1;
        if(hook_nAngle==-70)
            Clockwise=true;
    }
    }


    if(hook_Time==33333){
        hook_pCiecleTimer->stop();
        hook_bCircle=false;
        hook_Time=0;
    }
    update();
}

void myWidget::changePosition()
{
    double x=20*index*0.4;
    setGeometry(508-x*tan(hook_nAngle*pi/180.0),108+x,146,91);

    if(!catched && sqrt(x*x+x*tan(hook_nAngle*pi/180.0)*x*tan(hook_nAngle*pi/180.0))<=600 && !blankHook)
        index++;
    else {
        blankHook=true;
       if(index==0){
           keypressed=false;
           blankHook=false;
           catched=true;
           speed=1.4;
       }
       else {
           index-=speed*data::strength;
           if(index<0)
               index=0;
       }
    }
}

myWidget::~myWidget()
{

}

