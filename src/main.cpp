#include "mainwindow.h"
#include "generator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    generator g;

    g.helloWorld();

    return 0;   //a.exec();
}
