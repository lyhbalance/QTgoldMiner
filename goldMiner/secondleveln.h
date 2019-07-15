#ifndef SECONDLEVELN_H
#define SECONDLEVELN_H

#include <QWidget>
#include<QPaintEvent>
#include<QPainter>
#include<QTimer>
#include<QLabel>



namespace Ui {
class secondLeveln;
}

class secondLeveln : public QWidget
{
    Q_OBJECT

public:
    explicit secondLeveln(QWidget *parent = nullptr);
    ~secondLeveln();
    bool Catch(QLabel *a,QWidget *b);

    bool ifRight;


public slots:
    void judge();
    void giveindex();
    void movePig();

protected:
    void keyPressEvent(QKeyEvent *ev);

public:
    Ui::secondLeveln *ui;
    QTimer *passTimer;
    int timecounter;
    bool whetheradded;

};

#endif // SECONDLEVELN_H
