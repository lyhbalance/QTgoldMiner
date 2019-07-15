#include "drawline.h"
#include<QTimer>
#include<QPaintEvent>
#include<QPainter>
#include<QPen>
#include"mywidget.h"
#include"firstlevel.h"
#include<cmath>
const double pi=3.1415926;
drawline::drawline(QWidget *parent) : QWidget(parent)
{
    angel=0;
    flag=0;
    index=0;
    keypressed=false;
    lineTimer=new QTimer(this);
    connect(lineTimer,&QTimer::timeout,this,&drawline::drawing);
    lineTimer->start(50);
}
void drawline::drawing()
{
    if(keypressed){
        double x=20*index*0.4;

        pointx=583-x*tan(angel*pi/180.0);
        pointy=9+x;
        update();
        index++;
    }
}

void drawline::paintEvent(QPaintEvent *ev)
{
    if(keypressed){
        QPainter p(this);
        p.setRenderHint(QPainter::SmoothPixmapTransform);
        QPen pen;
        pen.setWidth(2);
        p.setPen(pen);
        p.drawLine(583,9,pointx,pointy);
    }
}

void drawline::getAngel(int a){
    angel=a;
}
