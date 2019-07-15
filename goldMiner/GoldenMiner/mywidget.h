#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <ctime>
#include <QtGlobal>
#include <QString>
#include <QImage>
#include <QPixmap>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QEasingCurve>

namespace Ui {
    class myWidget;
}

class myWidget : public QWidget
{
    Q_OBJECT

public:
    explicit myWidget(QWidget *parent = nullptr);
    ~myWidget();

private slots:
    void on_pushButton_clicked();
    void on_bomb_clicked(bool checked);
    void on_strongdrug_clicked(bool checked);
    void on_threeleaves_clicked(bool checked);
    void on_stonebook_clicked(bool checked);
    void on_luckdog_clicked(bool checked);

    void on_next_clicked(bool checked);

private:
 //数据成员部分
    Ui::myWidget *ui;
    bool Bought;
//    //全局变量
//    int Bomb;       //炸弹
//    int Luckdog;    //钻石加钱
//    int Threeleaves;  //三叶草
//    int Strongdrug;   //大力药水
//    int Stonebook;    //石头书

 //函数部分
    void useall();
    int bomb_price_appear();
    int luckdog_price_appear();
    int strongdrug_price_appear();
    int threeleaves_price_appear();
    int stonebook_price_appear();

};

#endif // MYWIDGET_H
