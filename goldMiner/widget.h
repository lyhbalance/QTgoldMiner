#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPaintEvent>
#include<QPainter>
#include<QTimer>
#include<QLabel>



namespace Ui {
class widget;
}

class widget : public QWidget
{
    Q_OBJECT

public:
    explicit widget(QWidget *parent = nullptr);
    ~widget();
    bool Catch(QLabel *a,QWidget *b);

    bool ifRight;
    bool ifRight2;
    bool ifRight3;


public slots:
    void judge();
    void giveindex();
    void movePig();
    void movePig2();
    void movePigWithDiamond();

protected:
    void keyPressEvent(QKeyEvent *ev);

public:
    Ui::widget *ui;
    QTimer *passTimer;
    int timecounter;
    bool whetheradded;

};

#endif // WIDGET_H
