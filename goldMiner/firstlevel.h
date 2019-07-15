#ifndef FIRSTLEVEL_H
#define FIRSTLEVEL_H

#include <QWidget>
#include<QPaintEvent>
#include<QPainter>
#include<QTimer>
#include<QLabel>


namespace Ui {
class firstLevel;
}

class firstLevel : public QWidget
{
    Q_OBJECT

public:
    explicit firstLevel(QWidget *parent = nullptr);
    ~firstLevel();
    bool Catch(QLabel *a,QWidget *b);

public slots:
    void judge();
    void giveindex();

protected:
    void keyPressEvent(QKeyEvent *ev);

public:
    Ui::firstLevel *ui;
    QTimer *passTimer;
    int timecounter;
    bool whetheradded;

};

#endif // FIRSTLEVEL_H
