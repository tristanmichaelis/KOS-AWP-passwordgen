#include "mainwindow.h"
#include <QApplication>
#include "lfsr_generator.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
    /*
    lfsr_generator lfsr;
    lfsr.generateSinglePassword();
    return 0;
    */
}
