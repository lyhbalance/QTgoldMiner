#include "firstlevel.h"
#include "ui_firstlevel.h"
#include<QPushButton>
#include<QLabel>
#include<QTimer>
#include<QPainter>
#include<QString>
#include<QListWidget>
#include "drawline.h"
#include"mywidget.h"
#include<QDebug>
#include<QRect>
#include"GoldenMiner1/mywidget1.h"
#include"data.h"
#include<ctime>

firstLevel::firstLevel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::firstLevel)
{
    ui->setupUi(this);
    QLabel *firstGoal=new QLabel;
    firstGoal->setParent(this);
    firstGoal->setScaledContents(true);
    firstGoal->setText("");
    firstGoal->setStyleSheet("border-image:url(':/new/firstLevel/photo/firstGoal.jpg')");
    firstGoal->setGeometry(0,0,1200,800);
    QTimer::singleShot(3000,firstGoal,&QLabel::hide);
    ui->bomb->setText(QString::number(data::bombNumber));
    whetheradded=false;
    passTimer=new QTimer(this);
    timecounter=63;
    QTimer *countingTime=new QTimer(this);
    connect(countingTime,&QTimer::timeout,[=](){
        timecounter-=1;
        QString num=QString::number(timecounter);
        ui->remainingTime->setText(num);
        if(timecounter==0 && data::money>=650){
            myWidget1 *buy=new myWidget1;

            this->close();
            buy->show();
            data::clearall();

        }
        else if (timecounter==0 && data::money<650) {
            QLabel *fail=ui->fail;
            fail->setParent(this);
            fail->setScaledContents(true);
            fail->setText("");
            fail->setStyleSheet("border-image:url(':/fail/photo/fail.png')");
            fail->setGeometry(0,0,1200,800);
            QTimer::singleShot(3000,this,&firstLevel::close);
        }
    });
    countingTime->start(1000);
}

firstLevel::~firstLevel()
{
    delete ui;
}
void firstLevel::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_PageDown)
    {
        whetheradded=false;
        ui->addNumber->hide();

        ui->youwangWidget->keypressed=true;
        ui->invisibleListWidget->keypressed=true;
        ui->youwangWidget->catched=false;

        ui->invisibleListWidget->getAngel(ui->youwangWidget->hook_nAngle);
        delete passTimer;
        passTimer=new QTimer(this);
        connect(passTimer,&QTimer::timeout,ui->youwangWidget,&myWidget::changePosition);
        connect(passTimer,&QTimer::timeout,this,&firstLevel::giveindex);
        connect(passTimer,&QTimer::timeout,this,&firstLevel::judge);
        passTimer->start(50);

        //return;
    }
    if (ev->key()==Qt::Key_PageUp) {
        if(ui->youwangWidget->catchedPageup==true){
        qDebug()<<"1";
        if(data::bombNumber==0)return;
        delete passTimer;
        passTimer=new QTimer(this);
        ui->youwangWidget->index=0;
        connect(passTimer,&QTimer::timeout,ui->youwangWidget,&myWidget::changePosition);
        connect(passTimer,&QTimer::timeout,this,&firstLevel::giveindex);
        passTimer->start(50);

        data::bombNumber-=1;
        ui->bomb->setText(QString::number(data::bombNumber));

        if(ui->youwangWidget->goldCatched==1){
            ui->youwangWidget->goldCatched=3;
            ui->bigGold->hide();
            ui->youwangWidget->catchedPageup=false;
        }

        if(ui->youwangWidget->goldCatched2==1){
            ui->youwangWidget->goldCatched2=3;
            ui->bigGold2->hide();
            ui->youwangWidget->catchedPageup=false;
        }

        if(ui->youwangWidget->smallGoldCatched1==1){
            ui->youwangWidget->smallGoldCatched1=3;
            ui->smallGold1->hide();
            ui->youwangWidget->catchedPageup=false;
        }

        if(ui->youwangWidget->smallGoldCatched2==1){
            ui->youwangWidget->smallGoldCatched2=3;
            ui->smallGold2->hide();
            ui->youwangWidget->catchedPageup=false;
        }

        if(ui->youwangWidget->smallGoldCatched3==1){
            ui->youwangWidget->smallGoldCatched3=3;
            ui->smallGold3->hide();
            ui->youwangWidget->catchedPageup=false;
        }

        if(ui->youwangWidget->stoneCatched1==1){
            ui->youwangWidget->stoneCatched1=3;
            ui->stone1->hide();
            ui->youwangWidget->catchedPageup=false;
        }

        if(ui->youwangWidget->stoneCatched2==1){
            ui->youwangWidget->stoneCatched2=3;
            ui->stone2->hide();
            ui->youwangWidget->catchedPageup=false;
        }

        if(ui->youwangWidget->stoneCatched3==1){
            ui->youwangWidget->stoneCatched3=3;
            ui->stone3->hide();
            ui->youwangWidget->catchedPageup=false;
        }

        if(ui->youwangWidget->luckBagcatched1==1){
            ui->youwangWidget->luckBagcatched1=3;
            ui->luckBag1->hide();
            ui->youwangWidget->catchedPageup=false;
        }
        }
    }

     QWidget::keyPressEvent(ev);
}
bool firstLevel::Catch(QLabel *a,QWidget *b){
    int HookX=b->geometry().x()+73;
    int HookY=b->geometry().y()+34;

    QPoint lefttop(a->geometry().left(),a->geometry().top());
    QPoint rightbottom(a->geometry().right(),a->geometry().bottom());

    QRect CatchJudge(lefttop,rightbottom);
    if(CatchJudge.contains(HookX,HookY)){
        a->setGeometry(HookX-0.5*(a->geometry().width()),HookY-0.5*(a->geometry().height()),a->geometry().width(),a->geometry().height());
        return true;
    }
    else return false;
}
void firstLevel::judge()
{
//biggold

    if(ui->youwangWidget->index>0  && ui->youwangWidget->goldCatched==0){
        if(ui->youwangWidget->catched=Catch(ui->bigGold,ui->youwangWidget))
        {
            ui->youwangWidget->goldCatched=1;
            ui->youwangWidget->speed=data::bigGoldSpeed;
            ui->youwangWidget->catchedPageup=true;
            return;
        }
    }
    else if(Catch(ui->bigGold,ui->youwangWidget)){
        //qDebug()<<ui->youwangWidget->index;
        //ui->bigGold->setGeometry(ui->bigGold->geometry().x(),ui->bigGold->geometry().y(),0,0);
        //qDebug()<<ui->youwangWidget->catched;
        if(ui->youwangWidget->index==0 && ui->youwangWidget->goldCatched==1)
        {
            ui->youwangWidget->goldCatched=2;
            ui->bigGold->hide();
            QString earnMoney="+$500";
            ui->addNumber->show();
            ui->addNumber->setText(earnMoney);
            if(!whetheradded){
                data::money+=500;
                whetheradded=true;
                ui->showCurrentMoney->setText("$"+QString::number(data::money));
            }
        }

    }

 //biggold2

    if(ui->youwangWidget->index>0  && ui->youwangWidget->goldCatched2==0){
        if(ui->youwangWidget->catched=Catch(ui->bigGold2,ui->youwangWidget))
        {
            ui->youwangWidget->goldCatched2=1;
            ui->youwangWidget->speed=data::bigGoldSpeed;
            ui->youwangWidget->catchedPageup=true;
            return;
        }
    }
    else if(Catch(ui->bigGold2,ui->youwangWidget)){
        //qDebug()<<ui->youwangWidget->index;
        //ui->bigGold->setGeometry(ui->bigGold->geometry().x(),ui->bigGold->geometry().y(),0,0);

        if(ui->youwangWidget->index==0 && ui->youwangWidget->goldCatched2==1)
        {
            ui->youwangWidget->goldCatched2=2;
            ui->bigGold2->hide();
            QString earnMoney="+$500";
            ui->addNumber->show();
            ui->addNumber->setText(earnMoney);
            if(!whetheradded){
                data::money+=500;
                whetheradded=true;
                ui->showCurrentMoney->setText("$"+QString::number(data::money));
            }
        }

    }

 // smallgold
    if(ui->youwangWidget->index>0  && ui->youwangWidget->smallGoldCatched1==0){
        if(ui->youwangWidget->catched=Catch(ui->smallGold1,ui->youwangWidget))
        {
            ui->youwangWidget->smallGoldCatched1=1;
            ui->youwangWidget->speed=data::smallGoldSpeed;
            ui->youwangWidget->catchedPageup=true;
            return;
        }
    }
    else if(Catch(ui->smallGold1,ui->youwangWidget)){
        //qDebug()<<ui->youwangWidget->index;
        //ui->bigGold->setGeometry(ui->bigGold->geometry().x(),ui->bigGold->geometry().y(),0,0);

        if(ui->youwangWidget->index==0 && ui->youwangWidget->smallGoldCatched1==1)
        {
            ui->youwangWidget->smallGoldCatched1=2;
            ui->smallGold1->hide();
            QString earnMoney="+$100";
            ui->addNumber->show();
            ui->addNumber->setText(earnMoney);
            if(!whetheradded){
                data::money+=100;
                whetheradded=true;
                ui->showCurrentMoney->setText("$"+QString::number(data::money));
            }
        }

    }

    //smallgold2
    if(ui->youwangWidget->index>0  && ui->youwangWidget->smallGoldCatched2==0){
        if(ui->youwangWidget->catched=Catch(ui->smallGold2,ui->youwangWidget))
        {
            ui->youwangWidget->smallGoldCatched2=1;
            ui->youwangWidget->speed=data::smallGoldSpeed;
            ui->youwangWidget->catchedPageup=true;
            return;
        }
    }
    else if(Catch(ui->smallGold2,ui->youwangWidget)){
        //qDebug()<<ui->youwangWidget->index;
        //ui->bigGold->setGeometry(ui->bigGold->geometry().x(),ui->bigGold->geometry().y(),0,0);

        if(ui->youwangWidget->index==0 && ui->youwangWidget->smallGoldCatched2==1)
        {
            ui->youwangWidget->smallGoldCatched2=2;
            ui->smallGold2->hide();
            QString earnMoney="+$100";
            ui->addNumber->show();
            ui->addNumber->setText(earnMoney);
            if(!whetheradded){
                data::money+=100;
                whetheradded=true;
                ui->showCurrentMoney->setText("$"+QString::number(data::money));
            }
        }

    }
    //smallgold3
    if(ui->youwangWidget->index>0  && ui->youwangWidget->smallGoldCatched3==0){
        if(ui->youwangWidget->catched=Catch(ui->smallGold3,ui->youwangWidget))
        {
            ui->youwangWidget->smallGoldCatched3=1;
            ui->youwangWidget->speed=data::smallGoldSpeed;
            ui->youwangWidget->catchedPageup=true;
            return;
        }
    }
    else if(Catch(ui->smallGold3,ui->youwangWidget)){
        //qDebug()<<ui->youwangWidget->index;
        //ui->bigGold->setGeometry(ui->bigGold->geometry().x(),ui->bigGold->geometry().y(),0,0);

        if(ui->youwangWidget->index==0 && ui->youwangWidget->smallGoldCatched3==1)
        {
            ui->youwangWidget->smallGoldCatched3=2;
            ui->smallGold3->hide();
            QString earnMoney="+$100";
            ui->addNumber->show();
            ui->addNumber->setText(earnMoney);
            if(!whetheradded){
                data::money+=100;
                whetheradded=true;
                ui->showCurrentMoney->setText("$"+QString::number(data::money));
            }
        }

    }
    //stone1
    if(ui->youwangWidget->index>0  && ui->youwangWidget->stoneCatched1==0){
        if(ui->youwangWidget->catched=Catch(ui->stone1,ui->youwangWidget))
        {
            ui->youwangWidget->stoneCatched1=1;
            ui->youwangWidget->speed=data::stoneSpeed;
            ui->youwangWidget->catchedPageup=true;
            return;
        }
    }
    else if(Catch(ui->stone1,ui->youwangWidget)){
        //qDebug()<<ui->youwangWidget->index;
        //ui->bigGold->setGeometry(ui->bigGold->geometry().x(),ui->bigGold->geometry().y(),0,0);

        if(ui->youwangWidget->index==0 && ui->youwangWidget->stoneCatched1==1)
        {
            ui->youwangWidget->stoneCatched1=2;
            ui->stone1->hide();
            QString earnMoney;
            if(data::stoneBookMoney==0)
                 earnMoney="+$20";
            else
                 earnMoney="+$70";
            ui->addNumber->show();
            ui->addNumber->setText(earnMoney);
            if(!whetheradded){
                data::money+=20;
                data::money+=data::stoneBookMoney;
                whetheradded=true;
                ui->showCurrentMoney->setText("$"+QString::number(data::money));
            }
        }

    }
    //stone2
    if(ui->youwangWidget->index>0  && ui->youwangWidget->stoneCatched2==0){
        if(ui->youwangWidget->catched=Catch(ui->stone2,ui->youwangWidget))
        {
            ui->youwangWidget->stoneCatched2=1;
            ui->youwangWidget->speed=data::stoneSpeed;
            ui->youwangWidget->catchedPageup=true;
            return;
        }
    }
    else if(Catch(ui->stone2,ui->youwangWidget)){
        //qDebug()<<ui->youwangWidget->index;
        //ui->bigGold->setGeometry(ui->bigGold->geometry().x(),ui->bigGold->geometry().y(),0,0);

        if(ui->youwangWidget->index==0 && ui->youwangWidget->stoneCatched2==1)
        {
            ui->youwangWidget->stoneCatched2=2;
            ui->stone2->hide();
            QString earnMoney;
            if(data::stoneBookMoney==0)
                 earnMoney="+$20";
            else
                 earnMoney="+$70";
            ui->addNumber->show();
            ui->addNumber->setText(earnMoney);
            if(!whetheradded){
                data::money+=20;
                data::money+=data::stoneBookMoney;
                whetheradded=true;
                ui->showCurrentMoney->setText("$"+QString::number(data::money));
            }
        }

    }
    //stone3
    if(ui->youwangWidget->index>0  && ui->youwangWidget->stoneCatched3==0){
        if(ui->youwangWidget->catched=Catch(ui->stone3,ui->youwangWidget))
        {
            ui->youwangWidget->stoneCatched3=1;
            ui->youwangWidget->speed=data::stoneSpeed;
            ui->youwangWidget->catchedPageup=true;
            return;
        }
    }
    else if(Catch(ui->stone3,ui->youwangWidget)){
        //qDebug()<<ui->youwangWidget->index;
        //ui->bigGold->setGeometry(ui->bigGold->geometry().x(),ui->bigGold->geometry().y(),0,0);

        if(ui->youwangWidget->index==0 && ui->youwangWidget->stoneCatched3==1)
        {
            ui->youwangWidget->stoneCatched3=2;
            ui->stone3->hide();
            QString earnMoney;
            if(data::stoneBookMoney==0)
                 earnMoney="+$20";
            else
                 earnMoney="+$70";
            ui->addNumber->show();
            ui->addNumber->setText(earnMoney);
            if(!whetheradded){
                data::money+=20;
                data::money+=data::stoneBookMoney;
                whetheradded=true;
                ui->showCurrentMoney->setText("$"+QString::number(data::money));
            }
        }

    }
    //luckBag1
    if(ui->youwangWidget->index>0  && ui->youwangWidget->luckBagcatched1==0){
        if(ui->youwangWidget->catched=Catch(ui->luckBag1,ui->youwangWidget))
        {            
            ui->youwangWidget->luckBagcatched1=1;
            qsrand(time(NULL));
            double ssspeeed=qrand()%5+5;
            ssspeeed=ssspeeed/10;
            ui->youwangWidget->speed=ssspeeed;
            ui->youwangWidget->catchedPageup=true;
            return;
        }
    }
    else if(Catch(ui->luckBag1,ui->youwangWidget)){
        //qDebug()<<ui->youwangWidget->index;
        //ui->bigGold->setGeometry(ui->bigGold->geometry().x(),ui->bigGold->geometry().y(),0,0);

        if(ui->youwangWidget->index==0 && ui->youwangWidget->luckBagcatched1==1)
        {
            ui->youwangWidget->luckBagcatched1=2;
            ui->luckBag1->hide();
            qsrand(time(NULL));
            int thingsTypes=qrand()%4;
            int finnalyMoney;
            if(thingsTypes!=1){
                if(data::IfThreeleaves==false)
                        finnalyMoney=qrand()%650+50;
                else
                        finnalyMoney=qrand()%600+200;
                ui->addNumber->show();
                ui->addNumber->setText("+$"+QString::number(finnalyMoney));
                if(!whetheradded){
                    data::money+=finnalyMoney;
                    whetheradded=true;
                    ui->showCurrentMoney->setText("$"+QString::number(data::money));
                }

            }
            else{
                data::strength=4;
                if(!whetheradded){
                    ui->addNumber->show();
                    whetheradded=true;
                    ui->addNumber->setText("Strong!!!");
                }
            }
        }

    }
}

void firstLevel::giveindex()
{
    ui->invisibleListWidget->index=ui->youwangWidget->index;
}
