#include "secondleveln.h"
#include "ui_secondleveln.h"
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

secondLeveln::secondLeveln(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::secondLeveln)
{
    ui->setupUi(this);
    QLabel *secondGoal=new QLabel;
    secondGoal->setParent(this);
    secondGoal->setScaledContents(true);
    secondGoal->setText("");
    secondGoal->setStyleSheet("border-image:url(':/goal/photo/secondGoal.png')");
    secondGoal->setGeometry(0,0,1200,800);
    QTimer::singleShot(4000,secondGoal,&QLabel::hide);
    ui->bomb->setText(QString::number(data::bombNumber));
    whetheradded=false;
    passTimer=new QTimer(this);
    timecounter=63;

    ifRight=true;

    ui->showCurrentMoney->setText(QString::number(data::money));
    QTimer *countingTime=new QTimer(this);
    connect(countingTime,&QTimer::timeout,[=](){
        timecounter-=1;
        QString num=QString::number(timecounter);
        ui->remainingTime->setText(num);
        if(timecounter==0 && data::money>=1150){
            myWidget1 *buy=new myWidget1;

            this->close();
            buy->show();
            data::clearall();
        }
        else if (timecounter==0 && data::money<1150) {
            QLabel *fail=ui->fail;
            fail->setParent(this);
            fail->setScaledContents(true);
            fail->setText("");
            fail->setStyleSheet("border-image:url(':/fail/photo/fail.png')");
            fail->setGeometry(0,0,1200,800);
            QTimer::singleShot(3000,this,&secondLeveln::close);
        }
    });
    QTimer *pigMove=new QTimer(this);
    connect(pigMove,&QTimer::timeout,this,&secondLeveln::movePig);
    countingTime->start(1000);
    pigMove->start(25);

}

secondLeveln::~secondLeveln()
{
    delete ui;
}
void secondLeveln::keyPressEvent(QKeyEvent *ev)
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
        connect(passTimer,&QTimer::timeout,this,&secondLeveln::giveindex);
        connect(passTimer,&QTimer::timeout,this,&secondLeveln::judge);

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
        connect(passTimer,&QTimer::timeout,this,&secondLeveln::giveindex);
        passTimer->start(50);

        data::bombNumber-=1;
        ui->bomb->setText(QString::number(data::bombNumber));

        if(ui->youwangWidget->goldCatched==1){
            ui->youwangWidget->goldCatched=3;
            ui->bigGold->hide();
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

        if(ui->youwangWidget->pigCatched1==1){
            ui->youwangWidget->pigCatched1=3;
            ui->pig1->hide();
            ui->youwangWidget->catchedPageup=false;
        }
        }
    }

     QWidget::keyPressEvent(ev);
}
bool secondLeveln::Catch(QLabel *a,QWidget *b){
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
void secondLeveln::judge()
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

    //stone4
    if(ui->youwangWidget->index>0  && ui->youwangWidget->stoneCatched4==0){
        if(ui->youwangWidget->catched=Catch(ui->stone4,ui->youwangWidget))
        {
            ui->youwangWidget->stoneCatched4=1;
            ui->youwangWidget->speed=data::stoneSpeed;
            ui->youwangWidget->catchedPageup=true;
            return;
        }
    }
    else if(Catch(ui->stone4,ui->youwangWidget)){
        //qDebug()<<ui->youwangWidget->index;
        //ui->bigGold->setGeometry(ui->bigGold->geometry().x(),ui->bigGold->geometry().y(),0,0);

        if(ui->youwangWidget->index==0 && ui->youwangWidget->stoneCatched4==1)
        {
            ui->youwangWidget->stoneCatched4=2;
            ui->stone4->hide();
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

    //stone5
    if(ui->youwangWidget->index>0  && ui->youwangWidget->stoneCatched5==0){
        if(ui->youwangWidget->catched=Catch(ui->stone5,ui->youwangWidget))
        {
            ui->youwangWidget->stoneCatched5=1;
            ui->youwangWidget->speed=data::stoneSpeed;
            ui->youwangWidget->catchedPageup=true;
            return;
        }
    }
    else if(Catch(ui->stone5,ui->youwangWidget)){
        //qDebug()<<ui->youwangWidget->index;
        //ui->bigGold->setGeometry(ui->bigGold->geometry().x(),ui->bigGold->geometry().y(),0,0);

        if(ui->youwangWidget->index==0 && ui->youwangWidget->stoneCatched5==1)
        {
            ui->youwangWidget->stoneCatched5=2;
            ui->stone5->hide();
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

    //stone6
    if(ui->youwangWidget->index>0  && ui->youwangWidget->stoneCatched6==0){
        if(ui->youwangWidget->catched=Catch(ui->stone6,ui->youwangWidget))
        {
            ui->youwangWidget->stoneCatched6=1;
            ui->youwangWidget->speed=data::stoneSpeed;
            ui->youwangWidget->catchedPageup=true;
            return;
        }
    }
    else if(Catch(ui->stone6,ui->youwangWidget)){
        //qDebug()<<ui->youwangWidget->index;
        //ui->bigGold->setGeometry(ui->bigGold->geometry().x(),ui->bigGold->geometry().y(),0,0);

        if(ui->youwangWidget->index==0 && ui->youwangWidget->stoneCatched6==1)
        {
            ui->youwangWidget->stoneCatched6=2;
            ui->stone6->hide();
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

    //stone7
    if(ui->youwangWidget->index>0  && ui->youwangWidget->stoneCatched7==0){
        if(ui->youwangWidget->catched=Catch(ui->stone7,ui->youwangWidget))
        {
            ui->youwangWidget->stoneCatched7=1;
            ui->youwangWidget->speed=data::stoneSpeed;
            ui->youwangWidget->catchedPageup=true;
            return;
        }
    }
    else if(Catch(ui->stone7,ui->youwangWidget)){
        //qDebug()<<ui->youwangWidget->index;
        //ui->bigGold->setGeometry(ui->bigGold->geometry().x(),ui->bigGold->geometry().y(),0,0);

        if(ui->youwangWidget->index==0 && ui->youwangWidget->stoneCatched7==1)
        {
            ui->youwangWidget->stoneCatched7=2;
            ui->stone7->hide();
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

    //bone1
    if(ui->youwangWidget->index>0  && ui->youwangWidget->boneCatched1==0){
        if(ui->youwangWidget->catched=Catch(ui->bone1,ui->youwangWidget))
        {
            ui->youwangWidget->boneCatched1=1;
            ui->youwangWidget->speed=data::boneSpeed;
            ui->youwangWidget->catchedPageup=true;
            return;
        }
    }
    else if(Catch(ui->bone1,ui->youwangWidget)){
        //qDebug()<<ui->youwangWidget->index;
        //ui->bigGold->setGeometry(ui->bigGold->geometry().x(),ui->bigGold->geometry().y(),0,0);

        if(ui->youwangWidget->index==0 && ui->youwangWidget->boneCatched1==1)
        {
            ui->youwangWidget->boneCatched1=2;
            ui->bone1->hide();
            QString earnMoney;
            earnMoney="+$2";
            ui->addNumber->show();
            ui->addNumber->setText(earnMoney);
            if(!whetheradded){
                data::money+=2;
                whetheradded=true;
                ui->showCurrentMoney->setText("$"+QString::number(data::money));
            }
        }

    }

    //bone2
    if(ui->youwangWidget->index>0  && ui->youwangWidget->boneCatched2==0){
        if(ui->youwangWidget->catched=Catch(ui->bone2,ui->youwangWidget))
        {
            ui->youwangWidget->boneCatched2=1;
            ui->youwangWidget->speed=data::boneSpeed;
            ui->youwangWidget->catchedPageup=true;
            return;
        }
    }
    else if(Catch(ui->bone2,ui->youwangWidget)){
        //qDebug()<<ui->youwangWidget->index;
        //ui->bigGold->setGeometry(ui->bigGold->geometry().x(),ui->bigGold->geometry().y(),0,0);

        if(ui->youwangWidget->index==0 && ui->youwangWidget->boneCatched2==1)
        {
            ui->youwangWidget->boneCatched2=2;
            ui->bone2->hide();
            QString earnMoney;
            earnMoney="+$2";
            ui->addNumber->show();
            ui->addNumber->setText(earnMoney);
            if(!whetheradded){
                data::money+=2;
                whetheradded=true;
                ui->showCurrentMoney->setText("$"+QString::number(data::money));
            }
        }

    }


    //diamond1
    if(ui->youwangWidget->index>0  && ui->youwangWidget->diamondCatched1==0){
        if(ui->youwangWidget->catched=Catch(ui->diamond1,ui->youwangWidget))
        {
            ui->youwangWidget->diamondCatched1=1;
            ui->youwangWidget->speed=data::diamondSpeed;
            ui->youwangWidget->catchedPageup=true;
            return;
        }
    }
    else if(Catch(ui->diamond1,ui->youwangWidget)){
        //qDebug()<<ui->youwangWidget->index;
        //ui->bigGold->setGeometry(ui->bigGold->geometry().x(),ui->bigGold->geometry().y(),0,0);

        if(ui->youwangWidget->index==0 && ui->youwangWidget->diamondCatched1==1)
        {
            ui->youwangWidget->diamondCatched1=2;
            ui->diamond1->hide();
            QString earnMoney;
            if(data::diamondAddMoney==0)
                 earnMoney="+$600";
            else
                 earnMoney="+$800";
            ui->addNumber->show();
            ui->addNumber->setText(earnMoney);
            if(!whetheradded){
                data::money+=600;
                data::money+=data::diamondAddMoney;
                whetheradded=true;
                ui->showCurrentMoney->setText("$"+QString::number(data::money));
            }
        }

    }

    //diamond2
    if(ui->youwangWidget->index>0  && ui->youwangWidget->diamondCatched2==0){
        if(ui->youwangWidget->catched=Catch(ui->diamond2,ui->youwangWidget))
        {
            ui->youwangWidget->diamondCatched2=1;
            ui->youwangWidget->speed=data::diamondSpeed;
            ui->youwangWidget->catchedPageup=true;
            return;
        }
    }
    else if(Catch(ui->diamond2,ui->youwangWidget)){
        //qDebug()<<ui->youwangWidget->index;
        //ui->bigGold->setGeometry(ui->bigGold->geometry().x(),ui->bigGold->geometry().y(),0,0);

        if(ui->youwangWidget->index==0 && ui->youwangWidget->diamondCatched2==1)
        {
            ui->youwangWidget->diamondCatched2=2;
            ui->diamond2->hide();
            QString earnMoney;
            if(data::diamondAddMoney==0)
                 earnMoney="+$600";
            else
                 earnMoney="+$800";
            ui->addNumber->show();
            ui->addNumber->setText(earnMoney);
            if(!whetheradded){
                data::money+=600;
                data::money+=data::diamondAddMoney;
                whetheradded=true;
                ui->showCurrentMoney->setText("$"+QString::number(data::money));
            }
        }

    }

    //pig1
    if(ui->youwangWidget->index>0  && ui->youwangWidget->pigCatched1==0){
        if(ui->youwangWidget->catched=Catch(ui->pig1,ui->youwangWidget))
        {
            ui->youwangWidget->pigCatched1=1;
            ui->youwangWidget->speed=data::pigSpeed;
            ui->youwangWidget->catchedPageup=true;
            return;
        }
    }
    else if(Catch(ui->pig1,ui->youwangWidget)){
        //qDebug()<<ui->youwangWidget->index;
        //ui->bigGold->setGeometry(ui->bigGold->geometry().x(),ui->bigGold->geometry().y(),0,0);

        if(ui->youwangWidget->index==0 && ui->youwangWidget->pigCatched1==1)
        {
            ui->youwangWidget->pigCatched1=2;
            ui->pig1->hide();
            QString earnMoney;
            earnMoney="+$5";
            ui->addNumber->show();
            ui->addNumber->setText(earnMoney);
            if(!whetheradded){
                data::money+=5;
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

void secondLeveln::giveindex()
{
    ui->invisibleListWidget->index=ui->youwangWidget->index;
}

void secondLeveln::movePig(){
    if(ifRight==true){
        int x=ui->pig1->geometry().x()+3;
        int y=ui->pig1->geometry().y();
        ui->pig1->setGeometry(x,y,ui->pig1->geometry().width(),ui->pig1->geometry().height());
        if(x>=1100){
            ifRight=false;
            ui->pig1->setStyleSheet("border-image:url('://GoldenMiner/photo/pig2.png')");
        }
    }
    else {
        int x=ui->pig1->geometry().x()-3;
        int y=ui->pig1->geometry().y();
        ui->pig1->setGeometry(x,y,ui->pig1->geometry().width(),ui->pig1->geometry().height());
        if(x<=100){
            ifRight=true;
            ui->pig1->setStyleSheet("border-image:url('://GoldenMiner/photo/pig.png')");
        }
    }
}
