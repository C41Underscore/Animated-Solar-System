#include "mainwindow.h"

#include <QApplication>

// TODO - Making the sun 'emit' light i.e. make it look like it is
// TODO - Add textures
// TODO - Add some sort of comet thing, maybe click a button and one flies across the screen
// TODO - Add a stary background
// TODO - Allow the user to change sizes i.e. normalise against, or have sizes based on order

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(1000, 1000);
    w.show();
    return a.exec();
}
