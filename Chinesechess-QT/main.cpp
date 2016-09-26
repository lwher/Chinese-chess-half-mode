#include "classes.h"
#include "mainwindow.h"
#include <QApplication>
#include <ctime>

int main(int argc, char *argv[]){
    srand(time(NULL));
    mode = false;
    QApplication a(argc, argv);
    inPro = &a;
    MainWindow w;
    w.show();
    return a.exec();
}
