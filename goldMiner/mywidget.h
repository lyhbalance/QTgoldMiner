#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include<QLabel>

class QTimer;

class myWidget : public QWidget
{
    Q_OBJECT

public:
    explicit myWidget(QWidget *parent = nullptr);
    ~myWidget();
    int hook_nAngle;

    void startRotate();

    bool keypressed;


    bool catched;
    bool catchedPageup;

    int goldCatched;
    int goldCatched2;

    int smallGoldCatched1;
    int smallGoldCatched2;
    int smallGoldCatched3;
    int smallGoldCatched4;

    int stoneCatched1;
    int stoneCatched2;
    int stoneCatched3;
    int stoneCatched4;
    int stoneCatched5;
    int stoneCatched6;
    int stoneCatched7;

    int boneCatched1;
    int boneCatched2;

    int pigCatched1;
    int pigCatched2;
    int pigWithDiamondCatched1;

    int diamondCatched1;
    int diamondCatched2;
    int luckBagcatched1;
    int luckBagcatched2;


    double speed;

    double index;

    bool Catch(QLabel *a,QWidget *b);
protected:
    void paintEvent(QPaintEvent *ev);

public slots:
    void onTimeout();
    void changePosition();

private:
    QImage hook_bg;
    QTimer *hook_pCiecleTimer;
    int hook_Time;
    bool hook_bCircle;

    bool Clockwise;

    bool blankHook;


};

#endif // MYWIDGET_H

