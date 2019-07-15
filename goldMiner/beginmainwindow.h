#ifndef BEGINMAINWINDOW_H
#define BEGINMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class beginMainWindow;
}

class beginMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit beginMainWindow(QWidget *parent = nullptr);
    ~beginMainWindow();

private slots:

    void on_btnBegin_clicked();

private:
    Ui::beginMainWindow *ui;
};

#endif // BEGINMAINWINDOW_H
