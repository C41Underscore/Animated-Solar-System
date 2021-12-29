#include "mainwindow.h"

#include <QApplication>

// TODO - Add textures
// TODO - Add some sort of comet thing, maybe click a button and one flies across the screen
// TODO - Add a stary background
// TODO - Allow for staillites (Moons, Artifical). This is our hierarchial modelling
// TODO - Have satillite orbit at different angles.  Look into 3D polar coordinates

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(750, 750);
    w.show();
    return a.exec();
}
