#include "mainwindow.h"

#include <QApplication>

// TODO - Making the sun 'emit' light i.e. make it look like it is
// TODO - Add textures
// TODO - Add some sort of comet thing, maybe click a button and one flies across the screen
// TODO - Add a stary background
// TODO - Allow the user to focus on different objects (requires a zoom and modifications to Model/View matrix)
// TODO - Allow for staillites (Moons, Artifical). This is our hierarchial modelling

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(750, 750);
    w.show();
    return a.exec();
}
