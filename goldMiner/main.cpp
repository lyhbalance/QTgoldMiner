#include "beginmainwindow.h"
#include <QApplication>
#include<time.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    time_t t;
    srand((unsigned)time(&t));
    beginMainWindow w;
    w.show();

    return a.exec();
}
