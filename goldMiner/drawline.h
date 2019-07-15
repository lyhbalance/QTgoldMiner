#ifndef DRAWLINE_H
#define DRAWLINE_H

#include <QWidget>
#include<QTimer>
#include<QPaintEvent>

class drawline : public QWidget
{
    Q_OBJECT
public:
    explicit drawline(QWidget *parent = nullptr);
    bool keypressed;
    void getAngel(int);
    double index;
public slots:
    void drawing();

private:
    QTimer *lineTimer;
    double pointx;
    double pointy;
    int flag;

    int angel;


protected:
    void paintEvent(QPaintEvent *ev);
};

#endif // DRAWLINE_H
