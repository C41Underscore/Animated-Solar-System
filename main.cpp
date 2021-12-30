#include "mainwindow.h"

#include <QApplication>

// TODO - Add textures
// TODO - Add a spaceship, which flies across the screen when a button is pushed, this can also our convex model with normals.
// TODO - Add a stary background
// TODO - Space items out a bit better, so it looks a bit nicer
// TODO - Maybe allow for the user to move around and zoom using arrow keys (simple translations really) - implemented but bugged, COMBOBOX!

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(750, 750);
    w.show();
    return a.exec();
}
